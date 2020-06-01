#include "OccupationLawFactory.h"
#include "ParserHelpers.h"



HoI4::OccupationLaw::Factory::Factory()
{
	
}


std::unique_ptr<HoI4::OccupationLaw> HoI4::OccupationLaw::Factory::getOccupationLaw(const std::string& name, std::istream& theStream)
{
	occupationLaw = std::make_unique<OccupationLaw>();
	occupationLaw->setName(name);

	parseStream(theStream);

	return std::move(occupationLaw);
}