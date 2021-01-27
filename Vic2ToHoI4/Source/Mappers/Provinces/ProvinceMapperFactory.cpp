#include "ProvinceMapperFactory.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "GameVersion.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "ProvinceMapper.h"
#include "VersionedMappings.h"
#include <fstream>



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
			return 0;
		}
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

	return std::move(provinceMapper);
}


std::vector<int> Mappers::ProvinceMapper::getVic2ToHoI4ProvinceMapping(const int Vic2Province) const
{
	const auto mapping = Vic2ToHoI4ProvinceMap.find(Vic2Province);
	if (mapping == Vic2ToHoI4ProvinceMap.end())
	{
		return {};
	}

	return mapping->second;
}


std::vector<int> Mappers::ProvinceMapper::getHoI4ToVic2ProvinceMapping(const int HoI4Province) const
{
	const auto mapping = HoI4ToVic2ProvinceMap.find(HoI4Province);
	if (mapping == HoI4ToVic2ProvinceMap.end())
	{
		return {};
	}

	return mapping->second;
}