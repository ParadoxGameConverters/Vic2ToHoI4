#include "Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include <fstream>
#include <vector>



Configuration::Factory::Factory()
{
	registerKeyword("HoI4directory", [this](const std::string& unused, std::istream& theStream) {
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
	registerKeyword("Vic2directory", [this](const std::string& unused, std::istream& theStream) {
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
	registerKeyword("Vic2Mods", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList modsStrings(theStream);
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
		const commonItems::singleInt ideologiesOptionNumber(theStream);
		if (ideologiesOptionNumber.getInt() == 3)
		{
			ideologiesOptions = ideologyOptions::keep_default;
			Log(LogLevel::Info) << "\tKeeping default ideologies";
		}
		else if (ideologiesOptionNumber.getInt() == 2)
		{
			ideologiesOptions = ideologyOptions::keep_all;
			Log(LogLevel::Info) << "\tKeeping all ideologies";
		}
		else if (ideologiesOptionNumber.getInt() == 4)
		{
			ideologiesOptions = ideologyOptions::specified;
			Log(LogLevel::Info) << "\tKeeping specified ideologies";
		}
		else // (ideologiesOptionString.getInt() == 1)
		{
			ideologiesOptions = ideologyOptions::keep_major;
			Log(LogLevel::Info) << "\tKeeping major ideologies";
		}
	});
	registerKeyword("ideologies_choice", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList choicesNumbersList(theStream);
		auto choiceNumbers = choicesNumbersList.getInts();
		for (const auto& choiceNumber: choiceNumbers)
		{
			switch (choiceNumber)
			{
				case 1:
					specifiedIdeologies.push_back("communism");
					Log(LogLevel::Info) << "\tSpecified communism";
					break;
				case 2:
					specifiedIdeologies.push_back("absolutist");
					Log(LogLevel::Info) << "\tSpecified absolutist";
					break;
				case 3:
					specifiedIdeologies.push_back("democratic");
					Log(LogLevel::Info) << "\tSpecified democratic";
					break;
				case 4:
					specifiedIdeologies.push_back("fascism");
					Log(LogLevel::Info) << "\tSpecified fascism";
					break;
				case 5:
					specifiedIdeologies.push_back("radical");
					Log(LogLevel::Info) << "\tSpecified radical";
					break;
				default:
					Log(LogLevel::Warning) << "Unknown ideology specified";
			}
		}
	});
	registerKeyword("debug", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt debugValue(theStream);
		if (debugValue.getInt() == 2)
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
		const commonItems::singleInt removeCoresValue(theStream);
		if (removeCoresValue.getInt() == 2)
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
		const commonItems::singleInt createFactionsValue(theStream);
		if (createFactionsValue.getInt() == 2)
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
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(const std::string& filename)
{
	Log(LogLevel::Info) << "Reading configuration file";
	parseFile(filename);

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
		 createFactions);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(std::istream& theStream)
{
	Log(LogLevel::Info) << "Reading configuration file";
	parseStream(theStream);

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
		 createFactions);
}