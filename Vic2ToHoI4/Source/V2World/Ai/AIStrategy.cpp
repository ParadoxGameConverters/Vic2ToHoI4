#include "AIStrategy.h"
#include "ParserHelpers.h"



Vic2::AIStrategy::AIStrategy(const std::string& strategyType, std::istream& theStream): type(strategyType)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream) {
		if (type == "conquer_prov")
		{
			commonItems::singleInt provinceID(theStream);
			provID = provinceID.getInt();
		}
		else
		{
			commonItems::singleString tag(theStream);
			id = tag.getString();
		}
	});
	registerKeyword("value", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt valueInt(theStream);
		value = valueInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}