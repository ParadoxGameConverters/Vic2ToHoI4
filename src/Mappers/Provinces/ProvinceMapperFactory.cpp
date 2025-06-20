#include "src/Mappers/Provinces/ProvinceMapperFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/GameVersion.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Configuration.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Mappers/Provinces/VersionedMappings.h"
#include <fstream>
#include <ranges>



namespace
{

std::optional<int> getNextProvinceNumFromFile(std::ifstream& definitions)
{
	std::string line;
	getline(definitions, line);

	if (const auto pos = line.find_first_of(';'); pos != std::string::npos)
	{
		try
		{
			return stoi(line.substr(0, pos));
		}
		catch (...)
		{
			Log(LogLevel::Warning) << "Bad line in /map/definition.csv: " << line;
		}

		return 0;
	}

	return std::nullopt;
}


void verifyProvinceIsMapped(const Mappers::VersionedMappings& versionedMapper, int provNum)
{
	if (!versionedMapper.getHoI4ToVic2Mapping().contains(provNum))
	{
		Log(LogLevel::Warning) << "No mapping for HoI4 province " << provNum;
	}
}


void checkAllHoI4ProvincesMapped(const Mappers::VersionedMappings& versionedMapper,
	 const Configuration& theConfiguration)
{
	std::ifstream definitions(theConfiguration.getHoI4Path() / "map/definition.csv");
	if (!definitions.is_open())
	{
		throw std::runtime_error("Could not open " + (theConfiguration.getHoI4Path() / "map/definition.csv").string());
	}

	while (true)
	{
		if (definitions.eof())
		{
			break;
		}
		auto provNum = getNextProvinceNumFromFile(definitions);
		if (!provNum)
		{
			continue;
		}
		if (*provNum == 0)
		{
			continue;
		}

		verifyProvinceIsMapped(versionedMapper, *provNum);
	}

	definitions.close();
}

} // namespace



Mappers::ProvinceMapper::Factory::Factory(const Configuration& theConfiguration)
{
	registerRegex(R"(\d\.[\d]+\.\d)", [this, theConfiguration](const std::string& unused, std::istream& theStream) {
		const auto thisVersionsMappings = versionedMappingsFactory.importVersionedMappings(theStream);
		checkAllHoI4ProvincesMapped(*thisVersionsMappings, theConfiguration);
		provinceMapper->HoI4ToVic2ProvinceMap = thisVersionsMappings->getHoI4ToVic2Mapping();
		provinceMapper->Vic2ToHoI4ProvinceMap = thisVersionsMappings->getVic2ToHoI4Mapping();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::ProvinceMapper> Mappers::ProvinceMapper::Factory::importProvinceMapper(
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "Parsing province mappings";
	provinceMapper = std::make_unique<ProvinceMapper>();

	auto mapped = false;
	for (const auto& mod: theConfiguration.getVic2Mods() | std::views::reverse)
	{
		if (commonItems::DoesFileExist(mod.path / "hybridization.txt"))
		{
			parseFile("Configurables/Historical Project Mod 0.4.6_province_mappings.txt");
			mapped = true;
			break;
		}

		std::filesystem::path mod_mappings = std::filesystem::path("Configurables") / mod.name;
		mod_mappings += "_province_mappings.txt";
		if (commonItems::DoesFileExist(mod_mappings))
		{
			parseFile(mod_mappings);
			mapped = true;
			break;
		}
	}
	if (!mapped)
	{
		parseFile("Configurables/province_mappings.txt");
	}

	return std::move(provinceMapper);
}


std::vector<int> Mappers::ProvinceMapper::getVic2ToHoI4ProvinceMapping(const int Vic2Province) const
{
	if (Vic2Province == 0)
	{
		return {};
	}
	const auto mapping = Vic2ToHoI4ProvinceMap.find(Vic2Province);
	if (mapping == Vic2ToHoI4ProvinceMap.end())
	{
		Log(LogLevel::Warning) << "No mapping found for Vic2 province " << Vic2Province;
		return {};
	}

	return mapping->second;
}


std::vector<int> Mappers::ProvinceMapper::getHoI4ToVic2ProvinceMapping(const int HoI4Province) const
{
	const auto mapping = HoI4ToVic2ProvinceMap.find(HoI4Province);
	if (mapping == HoI4ToVic2ProvinceMap.end())
	{
		Log(LogLevel::Warning) << "No mapping found for HoI4 province " << HoI4Province;
		return {};
	}

	return mapping->second;
}


std::set<int> Mappers::ProvinceMapper::getEquivalentVic2Provinces(const std::set<int>& hoi4_provinces) const
{
	std::set<int> equivalentProvinces;

	for (const auto hoi4_province: hoi4_provinces)
	{
		if (const auto mapping = HoI4ToVic2ProvinceMap.find(hoi4_province); mapping != HoI4ToVic2ProvinceMap.end())
		{
			for (const auto vic2_province: mapping->second)
			{
				equivalentProvinces.insert(vic2_province);
			}
		}
	}

	return equivalentProvinces;
}