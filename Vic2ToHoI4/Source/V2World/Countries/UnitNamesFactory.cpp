#include "UnitNamesFactory.h"
#include "CommonRegexes.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



Vic2::UnitNamesFactory::UnitNamesFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unitType, std::istream& theStream) {
		std::vector<std::string> newNames;
		for (const auto& name: commonItems::stringList{theStream}.getStrings())
		{
			newNames.push_back(commonItems::convertWin1252ToUTF8(name));
		}
		auto [names, inserted] = unitNames.insert(std::make_pair(unitType, newNames));
		if (!inserted)
		{
			for (const auto& name: newNames)
			{
				names->second.push_back(name);
			}
		}
	});
}


std::map<std::string, std::vector<std::string>> Vic2::UnitNamesFactory::importUnitNames(std::istream& theStream)
{
	unitNames.clear();
	parseStream(theStream);
	return std::move(unitNames);
}