#include "ModFactory.h"
#include "CommonRegexes.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



Vic2::Mod::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		mod->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("path", [this](std::istream& theStream) {
		mod->directory = commonItems::singleString{theStream}.getString();
		mod->directory = mod->directory.substr(4, mod->directory.size());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Mod> Vic2::Mod::Factory::getMod(const std::string& modFile, const std::string& Vic2ModDir)
{
	mod = std::make_unique<Mod>();
	parseFile(Vic2ModDir + "/" + modFile);
	if (mod->name.empty())
	{
		throw std::runtime_error("The mod defined by " + modFile + " has no name.");
	}
	if (mod->directory.empty())
	{
		throw std::runtime_error(mod->name + " specifies no folder.");
	}
	if (!commonItems::DoesFolderExist(Vic2ModDir + "/" + mod->directory))
	{
		throw std::runtime_error(mod->name + "'s folder is missing.");
	}
	return std::move(mod);
}