#include "Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include <fstream>
#include <vector>



std::unique_ptr<Configuration> ConfigurationDetails::importDetails(std::istream& theStream)
{
	std::string HoI4Path;
	std::string Vic2Path;
	std::vector<std::string> Vic2Mods;
	auto forceMultiplier = 0.0;
	auto manpowerFactor = 0.0;
	auto industrialShapeFactor = 0.0;
	auto icFactor = 0.0;
	auto ideologiesOptions = ideologyOptions::keep_major;
	std::vector<std::string> specifiedIdeologies;
	auto debug = false;
	auto removeCores = true;
	auto createFactions = true;
	auto version = HoI4::Version();

	registerKeyword("HoI4directory", [&HoI4Path](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString directoryString(theStream);
		HoI4Path = directoryString.getString();
		if (HoI4Path.empty() || !Utils::doesFolderExist(HoI4Path))
		{
			throw std::runtime_error("No HoI4 path was specified in configuration.txt, or the path was invalid");
		}
		if (!Utils::DoesFileExist(HoI4Path + "/hoi4.exe") && !Utils::DoesFileExist(HoI4Path + "/hoi4"))
		{
			throw std::runtime_error("The HoI4 path specified in configuration.txt does not contain HoI4");
		}

		Log(LogLevel::Info) << "\tHoI4 path install path is " << HoI4Path;
	});
	registerKeyword("V2directory", [&Vic2Path](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString directoryString(theStream);
		Vic2Path = directoryString.getString();
		if (Vic2Path.empty() || !Utils::doesFolderExist(Vic2Path))
		{
			throw std::runtime_error("No Victoria 2 path was specified in configuration.txt, or the path was invalid");
		}
		if (!Utils::DoesFileExist(Vic2Path + "/v2game.exe") && !Utils::DoesFileExist(Vic2Path + "/v2game"))
		{
			throw std::runtime_error("The Victoria 2 path specified in configuration.txt does not contain Victoria 2");
		}

		Log(LogLevel::Info) << "\tVictoria 2 install path is " << Vic2Path;
	});
	registerKeyword("Vic2Mods", [&Vic2Mods](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList modsStrings(theStream);
		Vic2Mods = modsStrings.getStrings();
	});
	registerKeyword("force_multiplier", [&forceMultiplier](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		forceMultiplier = factorValue.getDouble();
		Log(LogLevel::Info) << "\tForce multiplier: " << forceMultiplier;
	});
	registerKeyword("manpower_factor", [&manpowerFactor](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		manpowerFactor = factorValue.getDouble();
		Log(LogLevel::Info) << "\tManpower factor: " << manpowerFactor;
	});
	registerKeyword("industrial_shape_factor",
		 [&industrialShapeFactor](const std::string& unused, std::istream& theStream) {
			 const commonItems::singleDouble factorValue(theStream);
			 industrialShapeFactor = factorValue.getDouble();
			 Log(LogLevel::Info) << "\tIndustrial shape factor: " << industrialShapeFactor;
		 });
	registerKeyword("ic_factor", [&icFactor](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		icFactor = factorValue.getDouble();
		Log(LogLevel::Info) << "\tIC factor: " << icFactor;
	});
	registerKeyword("ideologies", [&ideologiesOptions](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString ideologiesOptionString(theStream);
		if (ideologiesOptionString.getString() == "keep_default")
		{
			ideologiesOptions = ideologyOptions::keep_default;
			Log(LogLevel::Info) << "\tKeeping default ideologies";
		}
		else if (ideologiesOptionString.getString() == "keep_all")
		{
			ideologiesOptions = ideologyOptions::keep_all;
			Log(LogLevel::Info) << "\tKeeping all ideologies";
		}
		else if (ideologiesOptionString.getString() == "specified")
		{
			ideologiesOptions = ideologyOptions::specified;
			Log(LogLevel::Info) << "\tKeeping specified ideologies";
		}
		else // (ideologiesOptionString.getString() == "keep_major")
		{
			ideologiesOptions = ideologyOptions::keep_major;
			Log(LogLevel::Info) << "\tKeeping major ideologies";
		}
	});
	registerKeyword("ideologies_choice", [&specifiedIdeologies](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString choiceString(theStream);
		specifiedIdeologies.push_back(choiceString.getString());
		Log(LogLevel::Info) << "\tSpecified " << choiceString.getString();
	});
	registerKeyword("debug", [&debug](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString debugString(theStream);
		if (debugString.getString() == "yes")
		{
			debug = true;
			Log(LogLevel::Info) << "\tDebug mode activated";
		}
	});
	registerKeyword("remove_cores", [&removeCores](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString removeCoresString(theStream);
		if (removeCoresString.getString() == "false")
		{
			removeCores = false;
			Log(LogLevel::Info) << "\tDisabling remove cores";
		}
	});
	registerKeyword("create_factions", [&createFactions](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString createFactionsString(theStream);
		if (createFactionsString.getString() == "no")
		{
			createFactions = false;
			Log(LogLevel::Info) << "\tDisabling keep factions";
		}
	});
	registerKeyword("HoI4Version", [&version](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString versionString(theStream);
		version = HoI4::Version(versionString.getString());
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	Log(LogLevel::Info) << "Reading configuration file";
	parseStream(theStream);

	Log(LogLevel::Info) << "\tConfigured HoI4 version is " << version;

	return std::make_unique<Configuration>(HoI4Path,
		 Vic2Path,
		 Vic2Mods,
		 forceMultiplier,
		 manpowerFactor,
		 industrialShapeFactor,
		 icFactor,
		 ideologiesOptions,
		 specifiedIdeologies,
		 debug,
		 removeCores,
		 createFactions,
		 version);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(const std::string& filename)
{
	std::unique_ptr<Configuration> configuration;

	registerKeyword("configuration", [&configuration](const std::string& unused, std::istream& theStream) {
		configuration = ConfigurationDetails{}.importDetails(theStream);
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseFile(filename);

	return configuration;
}