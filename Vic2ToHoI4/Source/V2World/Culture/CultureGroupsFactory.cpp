#include "CultureGroupsFactory.h"
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



Vic2::CultureGroups::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& groupName, std::istream& theStream) {
		group newCultureGroup(theStream);
		for (auto culture: newCultureGroup.getCultures())
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

	parseFile((theConfiguration.getVic2Path() + "/common/cultures.txt"));
	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		if (commonItems::DoesFileExist(
				  theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt"))
		{
			Log(LogLevel::Info) << "\tReading mod cultures from " << mod.getName();
			parseFile((theConfiguration.getVic2ModPath() + "/" + mod.getDirectory() + "/common/cultures.txt"));
		}
	}

	return std::move(cultureGroups);
}