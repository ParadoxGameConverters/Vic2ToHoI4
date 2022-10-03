#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PlaneDesign::PlaneDesign(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& lambdaStream) {
		name = commonItems::singleString(lambdaStream).getString();
	});
	registerKeyword("type", [this](std::istream& lambdaStream) {
		type = commonItems::singleString(lambdaStream).getString();
	});
	registerKeyword("modules", [this](std::istream& lambdaStream) {
		modules = std::make_unique<PlaneModules>(lambdaStream);
	});
	registerKeyword("icon", [this](std::istream& lambdaStream) {
		icon = commonItems::singleString(lambdaStream).getString();
	});
	registerKeyword("obsolete", [this](std::istream& lambdaStream) {
		const commonItems::singleString obsoleteString(lambdaStream);
		obsolete = obsoleteString.getString() == "yes";
	});
	registerKeyword("required_techs", [this](std::istream& lambdaStream) {
		for (const auto& requiredTech: commonItems::stringList(lambdaStream).getStrings())
		{
			requiredTechnologies.insert(requiredTech);
		}
	});
	registerKeyword("blocking_techs", [this](std::istream& lambdaStream) {
		for (const auto& blockingTech: commonItems::stringList(lambdaStream).getStrings())
		{
			blockingTechnologies.insert(blockingTech);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


HoI4::PlaneDesign& HoI4::PlaneDesign::operator=(const PlaneDesign& rhs)
{
	name = rhs.name;
	type = rhs.type;
	modules = std::make_unique<PlaneModules>(*rhs.modules);
	icon = rhs.icon;
	obsolete = rhs.obsolete;
	requiredTechnologies = rhs.requiredTechnologies;
	blockingTechnologies = rhs.blockingTechnologies;

	return *this;
}


bool HoI4::PlaneDesign::isValidDesign(const technologies& ownedTechs) const
{
	if (!std::ranges::all_of(requiredTechnologies.begin(),
			  requiredTechnologies.end(),
			  [ownedTechs](const std::string& technology) {
				  return ownedTechs.hasTechnology(technology);
			  }))
	{
		return false;
	}

	return std::ranges::none_of(blockingTechnologies.begin(),
		 blockingTechnologies.end(),
		 [ownedTechs](const std::string& technology) {
			 return ownedTechs.hasTechnology(technology);
		 });
}