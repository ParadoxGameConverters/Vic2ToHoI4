#include "UnitNamesFactory.h"
#include "ParserHelpers.h"



Vic2::UnitNamesFactory::UnitNamesFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unitType, std::istream& theStream) {
		const auto newNames = commonItems::stringList{theStream}.getStrings();
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