#include "src/OutHoi4/OutMod.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/OutFlags.h"
#include "src/OutHoi4/OutHoi4World.h"
#include <filesystem>
#include <string>



namespace
{

void CreateOutputFolder(const std::filesystem::path& output_name)
{
	Log(LogLevel::Info) << "\tCopying blank mod";
	if (!commonItems::DoesFolderExist("output") && !std::filesystem::create_directories("output"))
	{
		throw std::runtime_error("Could not create output folder");
	}
	try
	{
		std::filesystem::copy("blankmod", "output" / output_name, std::filesystem::copy_options::recursive);
	}
	catch (...)
	{
		throw std::runtime_error("Could not copy blankMod");
	}
}


void CreateModFiles(const std::filesystem::path& output_name)
{
	Log(LogLevel::Info) << "\tCreating .mod files";

	std::filesystem::path mod_filename = "output" / output_name;
	mod_filename += ".mod";
	std::ofstream mod_file(mod_filename);
	if (!mod_file.is_open())
	{
		throw std::runtime_error("Could not create .mod file");
	}
	mod_file << "name = \"Converted - " << output_name.string() << "\"\n";
	mod_file << "path = \"mod/" << output_name.string() << "/\"\n";
	mod_file << "user_dir = \"" << output_name.string() << "_user_dir\"\n";
	mod_file << "replace_path=\"common/abilities\"\n";
	mod_file << "replace_path=\"common/ai_navy/goals\"\n";
	mod_file << "replace_path=\"common/ai_navy/taskforce\"\n";
	mod_file << "replace_path=\"common/countries\"\n";
	mod_file << "replace_path=\"common/ideologies\"\n";
	mod_file << "replace_path=\"common/military_industrial_organization/organizations\"\n";
	mod_file << "replace_path=\"common/national_focus\"\n";
	mod_file << "replace_path=\"common/peace_conference/ai_peace\"\n";
	mod_file << "replace_path=\"common/peace_conference/cost_modifiers\"\n";
	mod_file << "replace_path=\"events\"\n";
	mod_file << "replace_path=\"history/countries\"\n";
	mod_file << "replace_path=\"history/states\"\n";
	mod_file << "replace_path=\"history/units\"\n";
	mod_file << "replace_path=\"map/supplyareas\"\n";
	mod_file << "replace_path=\"map/strategicregions\"\n";
	mod_file << "supported_version=\"1.17.*\"";
	mod_file.close();

	std::filesystem::path descriptor_filename = "output" / output_name;
	descriptor_filename += "/descriptor.mod";
	std::ofstream descriptor_file(descriptor_filename);
	if (!descriptor_file.is_open())
	{
		throw std::runtime_error("Could not create descriptor.mod");
	}
	descriptor_file << "name = \"Converted - " << output_name.string() << "\"\n";
	descriptor_file << "replace_path=\"common/abilities\"\n";
	descriptor_file << "replace_path=\"common/ai_navy/goals\"\n";
	descriptor_file << "replace_path=\"common/ai_navy/taskforce\"\n";
	descriptor_file << "replace_path=\"common/countries\"\n";
	descriptor_file << "replace_path=\"common/ideologies\"\n";
	descriptor_file << "replace_path=\"common/military_industrial_organization/organizations\"\n";
	descriptor_file << "replace_path=\"common/national_focus\"\n";
	descriptor_file << "replace_path=\"common/peace_conference/ai_peace\"\n";
	descriptor_file << "replace_path=\"common/peace_conference/cost_modifiers\"\n";
	descriptor_file << "replace_path=\"events\"\n";
	descriptor_file << "replace_path=\"history/countries\"\n";
	descriptor_file << "replace_path=\"history/states\"\n";
	descriptor_file << "replace_path=\"history/units\"\n";
	descriptor_file << "replace_path=\"map/supplyareas\"\n";
	descriptor_file << "replace_path=\"map/strategicregions\"\n";
	descriptor_file << "supported_version=\"1.17.*\"";
	descriptor_file.close();
}

} // namespace



void clearOutputFolder(const std::filesystem::path& outputName)
{
	const auto outputFolder = "output" / outputName;
	if (commonItems::DoesFolderExist(outputFolder))
	{
		Log(LogLevel::Info) << "Removing pre-existing copy of " << outputName;
		if (std::filesystem::remove_all(outputFolder) == -1)
		{
			throw std::runtime_error("Could not remove pre-existing output folder " + outputFolder.string() +
											 ". Please delete folder and try converting again.");
		}
	}
}


void output(const HoI4::World& destWorld,
	 const std::filesystem::path& outputName,
	 const bool debugEnabled,
	 const Mods& vic2Mods,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Progress) << "80%";
	Log(LogLevel::Info) << "Outputting mod";

	CreateOutputFolder(outputName);
	CreateModFiles(outputName);
	Log(LogLevel::Progress) << "85%";
	copyFlags(destWorld.getCountries(),
		 destWorld.GetUnionCountries(),
		 outputName,
		 vic2Mods,
		 destWorld.getMajorIdeologies());
	Log(LogLevel::Progress) << "90%";
	OutputWorld(destWorld, outputName, debugEnabled, theConfiguration);
}
