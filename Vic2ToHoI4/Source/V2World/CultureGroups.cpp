#include "CultureGroups.h"
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



class group: commonItems::parser
{
  public:
	explicit group(std::istream& theStream);

	auto getCultures() const { return cultures; }

  private:
	std::vector<std::string> cultures;
};


group::group(std::istream& theStream)
{
	registerKeyword("union", commonItems::ignoreItem);
	registerKeyword("leader", commonItems::ignoreItem);
	registerKeyword("unit", commonItems::ignoreItem);
	registerKeyword("is_overseas", commonItems::ignoreItem);
	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureName, std::istream& theStream) {
		cultures.push_back(cultureName);
		commonItems::ignoreItem(cultureName, theStream);
	});

	parseStream(theStream);
}



void Vic2::cultureGroups::init(const Configuration& theConfiguration)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& groupName, std::istream& theStream) {
		group newCultureGroup(theStream);
		for (auto culture: newCultureGroup.getCultures())
		{
			mappings.insert(make_pair(culture, groupName));
		}
	});

	Log(LogLevel::Info) << "Determining culture groups";

	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		if (Utils::DoesFileExist(theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt"))
		{
			Log(LogLevel::Info) << "\tReading mod cultures from " << mod.getName();
			parseFile((theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt"));
		}
	}

	parseFile((theConfiguration.getVic2Path() + "/common/cultures.txt"));
}


std::optional<std::string> Vic2::cultureGroups::getGroup(const std::string& culture) const
{
	if (auto mapping = mappings.find(culture); mapping != mappings.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}