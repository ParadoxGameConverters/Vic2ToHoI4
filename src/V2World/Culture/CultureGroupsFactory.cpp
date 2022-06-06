#include "CultureGroupsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"



Vic2::CultureGroups::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& groupName, std::istream& theStream) {
		for (const auto& culture: cultureGroupFactory.getCultureGroup(theStream))
		{
			// Fix HPM grouping all natives under one culture group
			if (groupName == "native_american")
			{
				// North Americans
				if (culture == "central_algonquian" || culture == "cherokee" || culture == "cree" || culture == "dakota" ||
					 culture == "eastern_algonquian" || culture == "eskaleut" || culture == "inuit" ||
					 culture == "iroquoian" || culture == "metis" || culture == "navajo" || culture == "penutian" ||
					 culture == "plains_algonquian" || culture == "pueblo" || culture == "siouan" ||
					 culture == "native_american_minor")
					cultureGroups->mappings.insert(make_pair(culture, "native_north_american"));
				// Central Americans
				else if (culture == "chibchan" || culture == "mayan" || culture == "nahua" || culture == "sonoran" ||
							culture == "tarascan" || culture == "zapotec")
					cultureGroups->mappings.insert(make_pair(culture, "native_central_american"));
				// South Americans
				else if (culture == "aimara" || culture == "amazonian" || culture == "araucanian" || culture == "caddoan" ||
							culture == "chacoan" || culture == "guajiro" || culture == "guarani" || culture == "je" ||
							culture == "maranon" || culture == "muskogean" || culture == "na_dene" ||
							culture == "patagonian" || culture == "quechua" || culture == "tupinamba")
					cultureGroups->mappings.insert(make_pair(culture, "native_south_american"));
				// Failsafe
				else
					cultureGroups->mappings.insert(make_pair(culture, "native_carribean"));
			}
			else
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
		if (commonItems::DoesFileExist(mod.path + "/common/cultures.txt"))
		{
			Log(LogLevel::Info) << "\tReading mod cultures from " << mod.name;
			cultureGroups->mappings.clear();
			parseFile(mod.path + "/common/cultures.txt");
		}
	}

	return std::move(cultureGroups);
}