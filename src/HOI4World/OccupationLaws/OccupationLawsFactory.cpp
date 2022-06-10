#include "src/HOI4World/OccupationLaws/OccupationLawsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/OccupationLaws/OccupationLawFactory.h"



std::unique_ptr<HoI4::OccupationLaws> HoI4::OccupationLaws::Factory::getOccupationLaws(
	 const Configuration& configuration)
{
	auto occupationLaws = std::make_unique<OccupationLaws>();
	OccupationLaw::Factory lawFactory;

	registerRegex(commonItems::catchallRegex,
		 [&occupationLaws, &lawFactory](const std::string& name, std::istream& theStream) {
			 const auto occupationLaw = lawFactory.getOccupationLaw(name, theStream);
			 occupationLaws->giveOccupationLaw(std::move(*occupationLaw));
		 });

	parseFile(configuration.getHoI4Path() + "/common/occupation_laws/occupation_laws.txt");
	return occupationLaws;
}