/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "ProvinceMapper.h"
#include "ProvinceMapping.h"
#include "VersionedMappings.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "../../Configuration.h"
#include <fstream>



provinceMapper theProvinceMapper;



void provinceMapper::initialize()
{
	bool gotMappings = false;
	registerKeyword(std::regex("\\d\\.\\d\\.\\d"), [this, &gotMappings](const std::string& version, std::istream& theStream){
		HoI4::Version currentVersion(version);
		if ((theConfiguration.getHOI4Version() >= currentVersion) && !gotMappings)
		{
			LOG(LogLevel::Debug) << "Using version " << version << " mappings";
			versionMappings thisVersionsMappings(theStream);
			HoI4ToVic2ProvinceMap = thisVersionsMappings.getHoI4ToVic2Mapping();
			Vic2ToHoI4ProvinceMap = thisVersionsMappings.getVic2ToHoI4Mapping();
			gotMappings = true;
		}
		else
		{
			commonItems::ignoreItem(version, theStream);
		}
	});

	LOG(LogLevel::Info) << "Parsing province mappings";
	bool mapped = false;
	for (auto mod: theConfiguration.getVic2Mods())
	{
		if (Utils::DoesFileExist(mod + "_province_mappings.txt"))
		{
			parseFile(mod + "_province_mappings.txt");
			mapped = true;
			break;
		}
	}
	if (!mapped)
	{
		parseFile("province_mappings.txt");
	}

	checkAllHoI4ProvinesMapped();
}


void provinceMapper::initialize(std::istream& input)
{
	registerKeyword(std::regex("\\d\\.\\d\\.\\d"), [this](const std::string& version, std::istream& theStream){
		HoI4::Version currentVersion(version);
		if ((theConfiguration.getHOI4Version() >= currentVersion))
		{
			LOG(LogLevel::Debug) << "Using version " << version << " mappings";
			versionMappings thisVersionsMappings(theStream);
			HoI4ToVic2ProvinceMap = thisVersionsMappings.getHoI4ToVic2Mapping();
			Vic2ToHoI4ProvinceMap = thisVersionsMappings.getVic2ToHoI4Mapping();
		}
		else
		{
			commonItems::ignoreItem(version, theStream);
		}
	});

	parseStream(input);
	checkAllHoI4ProvinesMapped();
}


void provinceMapper::checkAllHoI4ProvinesMapped() const
{
	std::ifstream definitions(theConfiguration.getHoI4Path() + "/map/definition.csv");
	if (!definitions.is_open())
	{
		LOG(LogLevel::Error) << "Could not open " << theConfiguration.getHoI4Path() << "/map/definition.csv";
		exit(EXIT_FAILURE);
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


std::optional<int> provinceMapper::getNextProvinceNumFromFile(std::ifstream& definitions) const
{
	std::string line;
	getline(definitions, line);
	int pos = line.find_first_of(';');
	if (pos != std::string::npos)
	{
		return stoi(line.substr(0, pos));
	}
	else
	{
		return {};
	}
}


void provinceMapper::verifyProvinceIsMapped(int provNum) const
{
	if (provNum != 0)
	{
		auto num = HoI4ToVic2ProvinceMap.find(provNum);
		if (num == HoI4ToVic2ProvinceMap.end())
		{
			LOG(LogLevel::Warning) << "No mapping for HoI4 province " << provNum;
		}
	}
}


std::optional<std::vector<int>> provinceMapper::getVic2ToHoI4ProvinceMapping(int Vic2Province) const
{
	if (auto mapping = Vic2ToHoI4ProvinceMap.find(Vic2Province); mapping != Vic2ToHoI4ProvinceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}


std::optional<std::vector<int>> provinceMapper::getHoI4ToVic2ProvinceMapping(int HoI4Province) const
{
	if (auto mapping = HoI4ToVic2ProvinceMap.find(HoI4Province); mapping != HoI4ToVic2ProvinceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}