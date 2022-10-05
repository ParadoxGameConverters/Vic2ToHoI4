#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PlaneDesign::PlaneDesign(std::istream& the_stream)
{
	registerKeyword("name", [this](std::istream& lambda_stream) {
		name_ = commonItems::singleString(lambda_stream).getString();
	});
	registerKeyword("type", [this](std::istream& lambda_stream) {
		type_ = commonItems::singleString(lambda_stream).getString();
	});
	registerKeyword("modules", [this](std::istream& lambda_stream) {
		modules_ = std::make_unique<PlaneModules>(lambda_stream);
	});
	registerKeyword("icon", [this](std::istream& lambda_stream) {
		icon_ = commonItems::singleString(lambda_stream).getString();
	});
	registerKeyword("obsolete", [this](std::istream& lambda_stream) {
		obsolete_ = commonItems::getString(lambda_stream) == "yes";
	});
	registerKeyword("required_techs", [this](std::istream& lambda_stream) {
		for (const auto& required_tech: commonItems::getStrings(lambda_stream))
		{
			required_technologies_.insert(required_tech);
		}
	});
	registerKeyword("blocking_techs", [this](std::istream& lambda_stream) {
		for (const auto& blocking_tech: commonItems::getStrings(lambda_stream))
		{
			blocking_technologies_.insert(blocking_tech);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(the_stream);
	clearRegisteredKeywords();

	if (name_.empty())
	{
		throw std::runtime_error("Plane design missing name");
	}
	if (type_.empty())
	{
		throw std::runtime_error("Plane design missing type");
	}
}


HoI4::PlaneDesign& HoI4::PlaneDesign::operator=(const PlaneDesign& rhs)
{
	name_ = rhs.name_;
	type_ = rhs.type_;
	modules_ = std::make_unique<PlaneModules>(*rhs.modules_);
	icon_ = rhs.icon_;
	obsolete_ = rhs.obsolete_;
	required_technologies_ = rhs.required_technologies_;
	blocking_technologies_ = rhs.blocking_technologies_;

	return *this;
}


bool HoI4::PlaneDesign::IsValidDesign(const technologies& owned_techs) const
{
	for (const auto& technology: required_technologies_)
	{
		if (!owned_techs.hasTechnology(technology))
		{
			return false;
		}
	}

	for (const auto& technology: blocking_technologies_)
	{
		if (owned_techs.hasTechnology(technology))
		{
			return false;
		}
	}

	return true;
}