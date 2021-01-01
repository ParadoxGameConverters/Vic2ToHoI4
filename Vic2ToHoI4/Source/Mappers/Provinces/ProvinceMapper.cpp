#include "ProvinceMapper.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "GameVersion.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "VersionedMappings.h"
#include <fstream>



mappers::ProvinceMapper mappers::ProvinceMapper::Parser::initializeMapper(const Configuration& theConfiguration)
{
	auto gotMappings = false;
	registerRegex(R"(\d\.[\d]+\.\d)",
		 [this, &gotMappings, theConfiguration](const std::string& version, std::istream& theStream) {
			 const GameVersion defaultVersion(version);
			 if ((GameVersion{1, 10, 1, 0} >= defaultVersion) && !gotMappings)
			 {
				 Log(LogLevel::Info) << "\tUsing version " << version << " mappings";
				 const VersionedMappings thisVersionsMappings(theStream);
				 HoI4ToVic2ProvinceMap = thisVersionsMappings.getHoI4ToVic2Mapping();
				 Vic2ToHoI4ProvinceMap = thisVersionsMappings.getVic2ToHoI4Mapping();
				 gotMappings = true;
			 }
			 else
			 {
				 commonItems::ignoreItem(version, theStream);
			 }
		 });
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	Log(LogLevel::Info) << "Parsing province mappings";

	auto mapped = false;
	for (const auto& mod: theConfiguration.getVic2Mods())
	{
		if (commonItems::DoesFileExist("Configurables/" + mod.getName() + "_province_mappings.txt"))
		{
			parseFile("Configurables/" + mod.getName() + "_province_mappings.txt");
			mapped = true;
			break;
		}
	}
	if (!mapped)
	{
		parseFile("Configurables/province_mappings.txt");
	}

	checkAllHoI4ProvincesMapped(theConfiguration);

	return ProvinceMapper(HoI4ToVic2ProvinceMap, Vic2ToHoI4ProvinceMap);
}


void mappers::ProvinceMapper::Parser::checkAllHoI4ProvincesMapped(const Configuration& theConfiguration) const
{
	std::ifstream definitions(theConfiguration.getHoI4Path() + "/map/definition.csv");
	if (!definitions.is_open())
	{
		throw std::runtime_error("Could not open " + theConfiguration.getHoI4Path() + "/map/definition.csv");
	}

	while (true)
	{
		auto provNum = getNextProvinceNumFromFile(definitions);
		if (!provNum)
		{
			break;
		}

		verifyProvinceIsMapped(*provNum);
	}

	definitions.close();
}


std::optional<int> mappers::ProvinceMapper::Parser::getNextProvinceNumFromFile(std::ifstream& definitions) const
{
	std::string line;
	getline(definitions, line);

	if (const auto pos = line.find_first_of(';'); pos != std::string::npos)
	{
		return stoi(line.substr(0, pos));
	}
	else
	{
		return {};
	}
}


void mappers::ProvinceMapper::Parser::verifyProvinceIsMapped(const int provNum) const
{
	if (provNum != 0)
	{
		if (!HoI4ToVic2ProvinceMap.contains(provNum))
		{
			Log(LogLevel::Warning) << "No mapping for HoI4 province " << provNum;
		}
	}
}


std::optional<std::vector<int>> mappers::ProvinceMapper::getVic2ToHoI4ProvinceMapping(const int Vic2Province) const
{
	if (const auto mapping = Vic2ToHoI4ProvinceMap.find(Vic2Province); mapping != Vic2ToHoI4ProvinceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}


std::optional<std::vector<int>> mappers::ProvinceMapper::getHoI4ToVic2ProvinceMapping(const int HoI4Province) const
{
	if (const auto mapping = HoI4ToVic2ProvinceMap.find(HoI4Province); mapping != HoI4ToVic2ProvinceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}