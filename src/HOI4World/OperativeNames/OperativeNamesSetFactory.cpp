#include "src/HOI4World/OperativeNames/OperativeNamesSetFactory.h"
#include "external/common_items/CommonFunctions.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::OperativeNamesSet::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& wrapper, std::istream& theStream) {
		operativeNamesSet = operativeNamesSetDetails.getOperativeNamesSet(theStream);
		operativeNamesSet->wrapper = wrapper;
	});
}



std::unique_ptr<HoI4::OperativeNamesSet> HoI4::OperativeNamesSet::Factory::getOperativeNamesSetFromFile(
	 const std::string& filename)
{
	parseFile(filename);
	if (!operativeNamesSet)
	{
		operativeNamesSet = std::make_unique<OperativeNamesSet>();
	}
	operativeNamesSet->filename = trimPath(filename);
	return std::move(operativeNamesSet);
}