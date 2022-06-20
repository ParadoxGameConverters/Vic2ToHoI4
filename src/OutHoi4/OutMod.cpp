#include "src/OutHoi4/OutMod.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/OutFlags.h"
#include "src/OutHoi4/OutHoi4World.h"
#include <string>



namespace
{

void CreateOutputFolder(const std::string& output_name)
{
	Log(LogLevel::Info) << "\tCopying blank mod";
	if (!commonItems::TryCreateFolder("output"))
	{
		throw std::runtime_error("Could not create output folder");
	}
	if (!commonItems::CopyFolder("blankmod", "output/" + output_name))
	{
		throw std::runtime_error("Could not copy blankMod");
	}
}


void CreateModFiles(const std::string& output_name)
{
	Log(LogLevel::Info) << "\tCreating .mod files";

	std::ofstream mod_file("output/" + output_name + ".mod");
	if (!mod_file.is_open())
	{
		throw std::runtime_error("Could not create .mod file");
	}
	mod_file << "name = \"Converted - " << output_name << "\"\n";
	mod_file << "path = \"mod/" << output_name << "/\"\n";
	mod_file << "user_dir = \"" << output_name << "_user_dir\"\n";
	mod_file << "replace_path=\"common/countries\"\n";
	mod_file << "replace_path=\"common/ideologies\"\n";
	mod_file << "replace_path=\"common/national_focus\"\n";
	mod_file << "replace_path=\"events\"\n";
	mod_file << "replace_path=\"history/countries\"\n";
	mod_file << "replace_path=\"history/states\"\n";
	mod_file << "replace_path=\"history/units\"\n";
	mod_file << "replace_path=\"map/supplyareas\"\n";
	mod_file << "replace_path=\"map/strategicregions\"\n";
	mod_file << "supported_version=\"1.11.*\"";
	mod_file.close();

	std::ofstream descriptor_file("output/" + output_name + "/descriptor.mod");
	if (!descriptor_file.is_open())
	{
		throw std::runtime_error("Could not create descriptor.mod");
	}
	descriptor_file << "name = \"Converted - " << output_name << "\"\n";
	descriptor_file << "replace_path=\"common/countries\"\n";
	descriptor_file << "replace_path=\"common/ideologies\"\n";
	descriptor_file << "replace_path=\"common/national_focus\"\n";
	descriptor_file << "replace_path=\"events\"\n";
	descriptor_file << "replace_path=\"history/countries\"\n";
	descriptor_file << "replace_path=\"history/states\"\n";
	descriptor_file << "replace_path=\"history/units\"\n";
	descriptor_file << "replace_path=\"map/supplyareas\"\n";
	descriptor_file << "replace_path=\"map/strategicregions\"\n";
	descriptor_file << "supported_version=\"1.11.*\"";
	descriptor_file.close();
}

} // namespace



void clearOutputFolder(const std::string& outputName)
{
	const auto outputFolder = "output/" + outputName;
	if (commonItems::DoesFolderExist(outputFolder))
	{
		Log(LogLevel::Info) << "Removing pre-existing copy of " << outputName;
		if (!commonItems::DeleteFolder(outputFolder))
		{
			throw std::runtime_error("Could not remove pre-existing output folder " + outputFolder +
											 ". Please delete folder and try converting again.");
		}
	}
}


void output(const HoI4::World& destWorld,
	 const std::string& outputName,
	 const bool debugEnabled,
	 const Mods& vic2Mods,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Progress) << "80%";
	Log(LogLevel::Info) << "Outputting mod";

	CreateOutputFolder(outputName);
	CreateModFiles(outputName);
	Log(LogLevel::Progress) << "85%";
	copyFlags(destWorld.getCountries(), outputName, vic2Mods, destWorld.getMajorIdeologies());
	Log(LogLevel::Progress) << "90%";
	OutputWorld(destWorld, outputName, debugEnabled, theConfiguration);
}