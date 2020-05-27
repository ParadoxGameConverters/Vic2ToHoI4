#include "Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "StringUtils.h"
#include <fstream>
#include <vector>



Configuration::Factory::Factory()
{
	registerKeyword("SaveGame", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString filenameString(theStream);
		inputFile = filenameString.getString();
		const auto length = inputFile.find_last_of('.');
		if ((length == std::string::npos) || (".v2" != inputFile.substr(length, inputFile.length())))
		{
			throw std::invalid_argument("The save was not a Vic2 save. Choose a save ending in '.v2' and convert again.");
		}
		Log(LogLevel::Info) << "\tVic2 save is " << inputFile;
	});
	registerKeyword("HoI4directory", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString directoryString(theStream);
		HoI4Path = directoryString.getString();
		if (HoI4Path.empty() || !Utils::DoesFolderExist(HoI4Path))
		{
			throw std::runtime_error("No HoI4 path was specified in configuration.txt, or the path was invalid");
		}
		if (!Utils::DoesFileExist(HoI4Path + "/hoi4.exe") && !Utils::DoesFileExist(HoI4Path + "/hoi4"))
		{
			throw std::runtime_error("The HoI4 path specified in configuration.txt does not contain HoI4");
		}

		Log(LogLevel::Info) << "\tHoI4 path install path is " << HoI4Path;
	});
	registerKeyword("Vic2directory", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString directoryString(theStream);
		Vic2Path = directoryString.getString();
		if (Vic2Path.empty() || !Utils::DoesFolderExist(Vic2Path))
		{
			throw std::runtime_error("No Victoria 2 path was specified in configuration.txt, or the path was invalid");
		}
		if (!Utils::DoesFileExist(Vic2Path + "/v2game.exe") && !Utils::DoesFileExist(Vic2Path + "/v2game"))
		{
			throw std::runtime_error("The Victoria 2 path specified in configuration.txt does not contain Victoria 2");
		}

		Log(LogLevel::Info) << "\tVictoria 2 install path is " << Vic2Path;
	});
	registerKeyword("Vic2Mods", [this](const std::string& unused, std::istream& theStream) {
		std::string line;
		std::getline(theStream, line);
		line = line.substr(line.find_first_of("\""), line.length());
		line = stringutils::remQuotes(line);
		std::stringstream lineStream;
		lineStream << line;
		const commonItems::stringList modsStrings(lineStream);
		Vic2Mods = modsStrings.getStrings();
	});
	registerKeyword("force_multiplier", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		forceMultiplier = std::clamp(static_cast<float>(factorValue.getDouble()), 0.01f, 100.0f);
		Log(LogLevel::Info) << "\tForce multiplier: " << forceMultiplier;
	});
	registerKeyword("manpower_factor", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		manpowerFactor = std::clamp(static_cast<float>(factorValue.getDouble()), 0.01f, 10.0f);
		Log(LogLevel::Info) << "\tManpower factor: " << manpowerFactor;
	});
	registerKeyword("industrial_shape_factor", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		industrialShapeFactor = std::clamp(static_cast<float>(factorValue.getDouble()), 0.0f, 1.0f);
		Log(LogLevel::Info) << "\tIndustrial shape factor: " << industrialShapeFactor;
	});
	registerKeyword("ic_factor", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		icFactor = std::clamp(static_cast<float>(factorValue.getDouble()), 0.0f, 1.0f);
		Log(LogLevel::Info) << "\tIC factor: " << icFactor;
	});
	registerKeyword("ideologies", [this](const std::string& unused, std::istream& theStream) {
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
	registerKeyword("ideologies_choice", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList choiceStrings(theStream);
		for (const auto& choice: choiceStrings.getStrings())
		{
			specifiedIdeologies.push_back(choice);
			Log(LogLevel::Info) << "\tSpecified " << choice;
		}
	});
	registerKeyword("debug", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString debugValue(theStream);
		if (debugValue.getString() == "yes")
		{
			debug = true;
			Log(LogLevel::Info) << "\tDebug mode activated";
		}
		else
		{
			debug = false;
			Log(LogLevel::Info) << "\tDebug mode deactivated";
		}
	});
	registerKeyword("remove_cores", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString removeCoresValue(theStream);
		if (removeCoresValue.getString() == "no")
		{
			removeCores = false;
			Log(LogLevel::Info) << "\tDisabling remove cores";
		}
		else
		{
			removeCores = true;
			Log(LogLevel::Info) << "\tEnabling remove cores";
		}
	});
	registerKeyword("create_factions", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString createFactionsValue(theStream);
		if (createFactionsValue.getString() == "no")
		{
			createFactions = false;
			Log(LogLevel::Info) << "\tDisabling keep factions";
		}
		else
		{
			createFactions = true;
			Log(LogLevel::Info) << "\tEnabling keep factions";
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(const std::string& filename)
{
	Log(LogLevel::Info) << "Reading configuration file";
	parseFile(filename);
	setOutputName(inputFile);

	return std::make_unique<Configuration>(inputFile,
		 outputName,
		 HoI4Path,
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
		 createFactions);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(std::istream& theStream)
{
	Log(LogLevel::Info) << "Reading configuration file";
	parseStream(theStream);
	setOutputName(inputFile);

	return std::make_unique<Configuration>(inputFile,
		 outputName,
		 HoI4Path,
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
		 createFactions);
}


void Configuration::Factory::setOutputName(const std::string& V2SaveFileName)
{
	outputName = V2SaveFileName;

	if (outputName.empty())
	{
		return;
	}

	const auto lastBackslash = V2SaveFileName.find_last_of('\\');
	const auto lastSlash = V2SaveFileName.find_last_of('/');
	if ((lastBackslash == std::string::npos) && (lastSlash != std::string::npos))
	{
		outputName = outputName.substr(lastSlash + 1, outputName.length());
	}
	else if ((lastBackslash != std::string::npos) && (lastSlash == std::string::npos))
	{
		outputName = outputName.substr(lastBackslash + 1, outputName.length());
	}
	else if ((lastBackslash != std::string::npos) && (lastSlash != std::string::npos))
	{
		const auto slash = std::max(lastBackslash, lastSlash);
		outputName = outputName.substr(slash + 1, outputName.length());
	}
	else if ((lastBackslash == std::string::npos) && (lastSlash == std::string::npos))
	{
		// no change, but explicitly considered
	}

	const auto length = outputName.find_last_of('.');
	if ((length == std::string::npos) || (".v2" != outputName.substr(length, outputName.length())))
	{
		throw std::invalid_argument("The save was not a Vic2 save. Choose a save ending in '.v2' and convert again.");
	}
	outputName = outputName.substr(0, length);

	std::replace(outputName.begin(), outputName.end(), '-', '_');
	std::replace(outputName.begin(), outputName.end(), ' ', '_');

	Log(LogLevel::Info) << "Using output name " << outputName;
}