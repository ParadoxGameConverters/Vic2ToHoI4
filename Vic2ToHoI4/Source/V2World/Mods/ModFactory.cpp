#include "ModFactory.h"
#include "ParserHelpers.h"



Vic2::Mod::Factory::Factory()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		mod->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("path", [this](const std::string& unused, std::istream& theStream) {
		mod->directory = commonItems::singleString{theStream}.getString();
		mod->directory = mod->directory.substr(4, mod->directory.size());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Mod> Vic2::Mod::Factory::getMod(const std::string& modFile, const std::string& Vic2ModDir)
{
	mod = std::make_unique<Mod>();
	parseFile(Vic2ModDir + "/" + modFile);
	return std::move(mod);
}