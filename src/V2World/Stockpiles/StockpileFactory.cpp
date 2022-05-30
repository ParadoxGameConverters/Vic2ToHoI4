#include "StockpileFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::StockpileFactory::StockpileFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& itemType, std::istream& theStream) {
		stockpile.emplace(itemType, static_cast<float>(commonItems::getDouble(theStream)));
	});
}


std::map<std::string, float> Vic2::StockpileFactory::importStockpile(std::istream& theStream)
{
	stockpile.clear();
	parseStream(theStream);
	return stockpile;
}
