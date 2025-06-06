#include "src/Configuration.h"
#include "external/common_items/CommonFunctions.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/GameVersion.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include <algorithm>
#include <fstream>
#include <vector>



Configuration::Factory::Factory()
{
	registerKeyword("SaveGame", [this](std::istream& theStream) {
		configuration->inputFile = commonItems::getString(theStream);
		if (".v2" != configuration->inputFile.extension())
		{
			throw std::invalid_argument("The save was not a Vic2 save. Choose a save ending in '.v2' and convert again.");
		}
		Log(LogLevel::Info) << "\tVic2 save is " << configuration->inputFile.string();
	});
	registerKeyword("HoI4directory", [this](std::istream& theStream) {
		configuration->HoI4Path = commonItems::getString(theStream);
		if (configuration->HoI4Path.empty() || !commonItems::DoesFolderExist(configuration->HoI4Path))
		{
			throw std::runtime_error("No HoI4 path was specified in configuration.txt, or the path was invalid");
		}
		if (!commonItems::DoesFileExist(configuration->HoI4Path / "hoi4.exe") &&
			 !commonItems::DoesFileExist(configuration->HoI4Path / "hoi4"))
		{
			throw std::runtime_error("The HoI4 path specified in configuration.txt does not contain HoI4");
		}

		Log(LogLevel::Info) << "\tHoI4 path install path is " << configuration->HoI4Path.string();
	});
	registerKeyword("Vic2directory", [this](std::istream& theStream) {
		configuration->Vic2Path = commonItems::getString(theStream);
		if (configuration->Vic2Path.empty() || !commonItems::DoesFolderExist(configuration->Vic2Path))
		{
			throw std::runtime_error("No Victoria 2 path was specified in configuration.txt, or the path was invalid");
		}
		if (!commonItems::DoesFileExist(configuration->Vic2Path / "v2game.exe") &&
			 !commonItems::DoesFileExist(configuration->Vic2Path / "v2game") &&
			 !commonItems::DoesFolderExist(configuration->Vic2Path / "Victoria 2 - Heart Of Darkness.app") &&
			 !commonItems::DoesFolderExist(configuration->Vic2Path / "../../MacOS"))
		{
			throw std::runtime_error("The Victoria 2 path specified in configuration.txt does not contain Victoria 2");
		}

		Log(LogLevel::Info) << "\tVictoria 2 install path is " << configuration->Vic2Path.string();
	});
	registerKeyword("targetGameModPath", [this](std::istream& theStream) {
		Log(LogLevel::Info) << "\tHoI4 mod path is " << commonItems::getString(theStream);
	});
	registerKeyword("selectedMods", [this](std::istream& theStream) {
		const auto& theList = commonItems::stringList{theStream}.getStrings();
		modFileNames.insert(theList.begin(), theList.end());
		Log(LogLevel::Info) << modFileNames.size() << " mods selected by configuration. Deselected mods will be ignored.";
	});
	registerKeyword("force_multiplier", [this](std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		configuration->forceMultiplier = std::clamp(static_cast<float>(factorValue.getDouble()), 0.01f, 100.0f);
		Log(LogLevel::Info) << "\tForce multiplier: " << configuration->forceMultiplier;
	});
	registerKeyword("manpower_factor", [this](std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		configuration->manpowerFactor = std::clamp(static_cast<float>(factorValue.getDouble()), 0.01f, 10.0f);
		Log(LogLevel::Info) << "\tManpower factor: " << configuration->manpowerFactor;
	});
	registerKeyword("industrial_shape_factor", [this](std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		configuration->industrialShapeFactor = std::clamp(static_cast<float>(factorValue.getDouble()), 0.0f, 1.0f);
		Log(LogLevel::Info) << "\tIndustrial shape factor: " << configuration->industrialShapeFactor;
	});
	registerKeyword("factory_factor", [this](std::istream& theStream) {
		const commonItems::singleDouble factorValue(theStream);
		configuration->factoryFactor = std::clamp(static_cast<float>(factorValue.getDouble()), 0.0f, 1.0f);
		Log(LogLevel::Info) << "\tFactory factor: " << configuration->factoryFactor;
	});
	registerKeyword("ideologies", [this](std::istream& theStream) {
		const commonItems::singleString ideologiesOptionString(theStream);
		if (ideologiesOptionString.getString() == "keep_default")
		{
			configuration->ideologiesOptions = ideologyOptions::keep_default;
			Log(LogLevel::Info) << "\tKeeping default ideologies";
		}
		else if (ideologiesOptionString.getString() == "keep_all")
		{
			configuration->ideologiesOptions = ideologyOptions::keep_all;
			Log(LogLevel::Info) << "\tKeeping all ideologies";
		}
		else if (ideologiesOptionString.getString() == "specify")
		{
			configuration->ideologiesOptions = ideologyOptions::specified;
			Log(LogLevel::Info) << "\tKeeping specified ideologies";
		}
		else // (ideologiesOptionString.getString() == "keep_major")
		{
			configuration->ideologiesOptions = ideologyOptions::keep_major;
			Log(LogLevel::Info) << "\tKeeping major ideologies";
		}
	});
	registerKeyword("ideologies_choice", [this](std::istream& theStream) {
		const commonItems::stringList choiceStrings(theStream);
		for (const auto& choice: choiceStrings.getStrings())
		{
			configuration->specifiedIdeologies.push_back(choice);
			Log(LogLevel::Info) << "\tSpecified " << choice;
		}
	});
	registerKeyword("debug", [this](std::istream& theStream) {
		const commonItems::singleString debugValue(theStream);
		if (debugValue.getString() == "yes")
		{
			configuration->debug = true;
			Log(LogLevel::Debug) << "\tDebug mode activated";
		}
		else
		{
			configuration->debug = false;
			Log(LogLevel::Debug) << "\tDebug mode deactivated";
		}
	});
	registerKeyword("remove_cores", [this](std::istream& theStream) {
		const commonItems::singleString removeCoresValue(theStream);
		if (removeCoresValue.getString() == "remove_none")
		{
			configuration->removeCores = removeCoresOptions::remove_none;
			Log(LogLevel::Info) << "\tDisabling remove cores";
		}
		else if (removeCoresValue.getString() == "remove_too_little_culture")
		{
			configuration->removeCores = removeCoresOptions::remove_too_little_culture;
			Log(LogLevel::Info) << "\tRemoving cores with too little accepted culture";
		}
		else if (removeCoresValue.getString() == "remove_same_culture_as_owner")
		{
			configuration->removeCores = removeCoresOptions::remove_same_culture_as_owner;
			Log(LogLevel::Info) << "\tRemoving cores with the same culture as the owner";
		}
		else if (removeCoresValue.getString() == "remove_accepted_culture_by_owner")
		{
			configuration->removeCores = removeCoresOptions::remove_accepted_culture_by_owner;
			Log(LogLevel::Info) << "\tRemoving cores where the owner accepts the culture";
		}
		else // if (removeCoresValue.getString() == "extreme_removal")
		{
			configuration->removeCores = removeCoresOptions::extreme_removal;
			Log(LogLevel::Info) << "\tRemoving cores wherever appropriate";
		}
	});
	registerKeyword("create_factions", [this](std::istream& theStream) {
		const commonItems::singleString createFactionsValue(theStream);
		if (createFactionsValue.getString() == "no")
		{
			configuration->createFactions = false;
			Log(LogLevel::Info) << "\tDisabling keep factions";
		}
		else
		{
			configuration->createFactions = true;
			Log(LogLevel::Info) << "\tEnabling keep factions";
		}
	});
	registerKeyword("percent_of_commanders", [this](std::istream& theStream) {
		configuration->percentOfCommanders =
			 std::clamp(static_cast<float>(commonItems::singleDouble{theStream}.getDouble()), 0.0F, 100.0F) / 100.0F;
		Log(LogLevel::Info) << "\tPercent of commanders: " << configuration->percentOfCommanders;
	});
	registerKeyword("output_name", [this](const std::string& unused, std::istream& theStream) {
		configuration->customOutputName = commonItems::singleString(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(const std::filesystem::path& filename,
	 const commonItems::ConverterVersion& converterVersion)
{
	Log(LogLevel::Info) << "Reading configuration file";
	configuration = std::make_unique<Configuration>();
	parseFile(filename);
	verifyVic2Version(converterVersion);
	verifyHoI4Version(converterVersion);
	setOutputName(configuration->inputFile, configuration->customOutputName);
	importMods();

	return std::move(configuration);
}


std::unique_ptr<Configuration> Configuration::Factory::importConfiguration(std::istream& theStream,
	 const commonItems::ConverterVersion& converterVersion)
{
	Log(LogLevel::Info) << "Reading configuration file";
	configuration = std::make_unique<Configuration>();
	parseStream(theStream);
	verifyVic2Version(converterVersion);
	verifyHoI4Version(converterVersion);
	setOutputName(configuration->inputFile, configuration->customOutputName);
	importMods();

	return std::move(configuration);
}


void Configuration::Factory::setOutputName(const std::filesystem::path& V2SaveFileName,
	 const std::string& customOutputName)
{
	std::string outputName;
	if (customOutputName.empty())
	{
		const std::filesystem::path filename = V2SaveFileName.filename();
		if (filename.extension() != ".v2")
		{
			throw std::invalid_argument("The save was not a Vic2 save. Choose a save ending in '.v2' and convert again.");
		}
		outputName = filename.stem().string();
	}
	else
	{
		outputName = customOutputName;
	}
	if (outputName.empty())
	{
		return;
	}

	outputName = normalizeStringPath(outputName);

	Log(LogLevel::Info) << "Using output name " << outputName;
	configuration->outputName = outputName;
}


void Configuration::Factory::importMods()
{
	commonItems::ModLoader modLoader;
	Mods incomingMods;
	for (const auto& modFileName: modFileNames)
	{
		incomingMods.emplace_back(Mod("", modFileName));
	}
	modLoader.loadMods(configuration->getVic2Path(), incomingMods);
	configuration->Vic2Mods = modLoader.getMods();
	sortMods();
}


void Configuration::Factory::sortMods()
{
	// using Kahn's algorithm - https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
	auto unsortedMods = configuration->Vic2Mods;

	// track incoming edges
	std::map<std::string, std::set<std::string>> incomingDependencies;
	for (const auto& mod: unsortedMods)
	{
		for (const auto& dependency: mod.dependencies)
		{
			auto [itr, inserted] = incomingDependencies.emplace(dependency, std::set{mod.name});
			if (!inserted)
			{
				itr->second.insert(mod.name);
			}
		}
	}

	// add mods with no incoming edges to the sorted mods
	Mods sortedMods;
	while (!unsortedMods.empty())
	{
		auto itr = unsortedMods.begin();
		while (incomingDependencies.contains(itr->name))
		{
			++itr;
			if (itr == unsortedMods.end())
			{
				throw std::invalid_argument("A mod dependency was missing. Include all mods used in Vic2.");
			}
		}

		sortedMods.push_back(*itr);

		for (const auto& dependencyName: itr->dependencies)
		{
			auto dependency = incomingDependencies.find(dependencyName);
			dependency->second.erase(itr->name);
			if (dependency->second.empty())
			{
				incomingDependencies.erase(dependencyName);
			}
		}

		unsortedMods.erase(itr);
	}
	std::ranges::reverse(sortedMods);

	configuration->Vic2Mods = sortedMods;
}


void Configuration::Factory::verifyVic2Version(const commonItems::ConverterVersion& converterVersion) const
{
	GameVersion vic2version;
	if (commonItems::DoesFileExist(configuration->Vic2Path / "changelog_3.04.txt"))
	{
		Log(LogLevel::Info) << "\tVic2 version: 3.0.4";
		return;
	}

	std::filesystem::path readmePath = configuration->Vic2Path / "ReadMe.txt";
	if (!commonItems::DoesFileExist(readmePath))
	{
		readmePath = configuration->Vic2Path / "Readme.txt";
		if (!commonItems::DoesFileExist(readmePath))
		{
			Log(LogLevel::Error) << "Vic2 version could not be determined, proceeding blind!";
			return;
		}
	}

	const auto V2Version = GameVersion::extractVersionFromReadMe(readmePath);
	if (!V2Version)
	{
		Log(LogLevel::Error) << "Vic2 version could not be determined, proceeding blind!";
		return;
	}

	Log(LogLevel::Info) << "\tVic2 version: " << V2Version->toShortString();

	if (converterVersion.getMinSource() > *V2Version)
	{
		Log(LogLevel::Error) << "Vic2 version is v" << V2Version->toShortString() << ", converter requires minimum v"
									<< converterVersion.getMinSource().toShortString() << "!";
		throw std::runtime_error("Converter vs Vic2 installation mismatch!");
	}
	if (!converterVersion.getMaxSource().isLargerishThan(*V2Version))
	{
		Log(LogLevel::Error) << "Vic2 version is v" << V2Version->toShortString() << ", converter requires maximum v"
									<< converterVersion.getMaxSource().toShortString() << "!";
		throw std::runtime_error("Converter vs Vic2 installation mismatch!");
	}
}

void Configuration::Factory::verifyHoI4Version(const commonItems::ConverterVersion& converterVersion) const
{
	const auto HoI4Version = GameVersion::extractVersionFromLauncher(configuration->HoI4Path / "launcher-settings.json");
	if (!HoI4Version)
	{
		Log(LogLevel::Error) << "HoI4 version could not be determined, proceeding blind!";
		return;
	}

	Log(LogLevel::Info) << "\tHoI4 version: " << HoI4Version->toShortString();

	if (converterVersion.getMinTarget() > *HoI4Version)
	{
		Log(LogLevel::Error) << "HoI4 version is v" << HoI4Version->toShortString() << ", converter requires minimum v"
									<< converterVersion.getMinTarget().toShortString() << "!";
		throw std::runtime_error("Converter vs HoI4 installation mismatch!");
	}
	if (!converterVersion.getMaxTarget().isLargerishThan(*HoI4Version))
	{
		Log(LogLevel::Error) << "HoI4 version is v" << HoI4Version->toShortString() << ", converter requires maximum v"
									<< converterVersion.getMaxTarget().toShortString() << "!";
		throw std::runtime_error("Converter vs HoI4 installation mismatch!");
	}
}
