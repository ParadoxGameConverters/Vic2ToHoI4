#include "OperativeNamesMappingFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::OperativeNamesMappingFactory::OperativeNamesMappingFactory()
{
	registerKeyword("codenames", [this](std::istream& theStream) {
		codenames = commonItems::singleString(theStream).getString();
	});
	registerKeyword("culture", [this](std::istream& theStream) {
		cultures.push_back(commonItems::singleString(theStream).getString());
	});
	registerKeyword(commonItems::catchallRegex, commonItems::ignoreItem);
}



HoI4::RawOperativeNamesMappings HoI4::OperativeNamesMappingFactory::getMappings(std::istream& theStream)
{
	codenames.clear();
	cultures.clear();
	parseStream(theStream);

	RawOperativeNamesMappings operativeNamesMappings;
	if (codenames.empty())
	{
		return operativeNamesMappings;
	}
	for (const auto& culture: cultures)
	{
		operativeNamesMappings.insert(std::make_pair(culture, codenames));
	}
	return operativeNamesMappings;
}