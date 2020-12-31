#include "CultureGroupsFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"



Vic2::CultureGroups::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& groupName, std::istream& theStream) {
		for (const auto& culture: cultureGroupFactory.getCultureGroup(theStream))
		{
			cultureGroups->mappings.insert(make_pair(culture, groupName));
		}
	});
}


std::unique_ptr<Vic2::CultureGroups> Vic2::CultureGroups::Factory::getCultureGroups(
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "Determining culture groups";

	cultureGroups = std::make_unique<CultureGroups>();

	parseFile(theConfiguration.getVic2Path() + "/common/cultures.txt");
	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		if (commonItems::DoesFileExist(
				  theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt"))
		{
			Log(LogLevel::Info) << "\tReading mod cultures from " << mod.getName();
			cultureGroups->mappings.clear();
			parseFile(theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt");
		}
	}

	return std::move(cultureGroups);
}