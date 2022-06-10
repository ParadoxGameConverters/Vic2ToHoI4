#include "src/Mappers/Graphics/GraphicsMapper.h"
#include "external/common_items/CommonFunctions.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Mappers/Graphics/GraphicsCultureGroup.h"
#include <limits>
#include <ranges>



std::vector<std::string> Mappers::GraphicsMapper::getArmyPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto armyPortraitMapping = armyPortraitMappings.find(culture);
		 armyPortraitMapping != armyPortraitMappings.end())
	{
		return armyPortraitMapping->second;
	}

	if (const auto armyPortraitMapping = armyPortraitMappings.find(cultureGroup);
		 armyPortraitMapping != armyPortraitMappings.end())
	{
		return armyPortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getNavyPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto navyPortraitMapping = navyPortraitMappings.find(culture);
		 navyPortraitMapping != navyPortraitMappings.end())
	{
		return navyPortraitMapping->second;
	}

	if (const auto navyPortraitMapping = navyPortraitMappings.find(cultureGroup);
		 navyPortraitMapping != navyPortraitMappings.end())
	{
		return navyPortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getMaleMonarchPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto maleMonarchMapping = maleMonarchMappings.find(culture);
		 maleMonarchMapping != maleMonarchMappings.end())
	{
		return maleMonarchMapping->second;
	}

	if (const auto maleMonarchMapping = maleMonarchMappings.find(cultureGroup);
		 maleMonarchMapping != maleMonarchMappings.end())
	{
		return maleMonarchMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemaleMonarchPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto femaleMonarchMapping = femaleMonarchMappings.find(culture);
		 femaleMonarchMapping != femaleMonarchMappings.end())
	{
		return femaleMonarchMapping->second;
	}

	if (const auto femaleMonarchMapping = femaleMonarchMappings.find(cultureGroup);
		 femaleMonarchMapping != femaleMonarchMappings.end())
	{
		return femaleMonarchMapping->second;
	}

	return {};
}


std::string Mappers::GraphicsMapper::getLeaderPortrait(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& ideology)
{
	auto portraits = getLeaderPortraits(culture, ideology);
	if (!portraits.empty())
	{
		std::string least_used_portrait;
		int least_used_times = std::numeric_limits<int>::max();
		for (const auto& portrait: portraits)
		{
			int times_used = 0;
			if (const auto& itr = used_portraits_.find(portrait); itr != used_portraits_.end())
			{
				times_used = itr->second;
			}

			if (times_used < least_used_times)
			{
				least_used_portrait = portrait;
				least_used_times = times_used;
			}
		}

		if (const auto& [itr, inserted] = used_portraits_.emplace(least_used_portrait, 1); itr != used_portraits_.end())
		{
			++itr->second;
		}

		return least_used_portrait;
	}

	portraits = getLeaderPortraits(cultureGroup, ideology);
	if (!portraits.empty())
	{
		std::string least_used_portrait;
		int least_used_times = std::numeric_limits<int>::max();
		for (const auto& portrait: portraits)
		{
			int times_used = 0;
			if (const auto& itr = used_portraits_.find(portrait); itr != used_portraits_.end())
			{
				times_used = itr->second;
			}

			if (times_used < least_used_times)
			{
				least_used_portrait = portrait;
				least_used_times = times_used;
			}
		}

		if (const auto& [itr, inserted] = used_portraits_.emplace(least_used_portrait, 1); itr != used_portraits_.end())
		{
			++itr->second;
		}

		return least_used_portrait;
	}

	return "gfx/leaders/leader_unknown.dds";
}


std::vector<std::string> Mappers::GraphicsMapper::getLeaderPortraits(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& ideology) const
{
	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(culture);
		 leaderPortraitMapping != leaderPortraitMappings.end())
	{
		if (const auto portraits = leaderPortraitMapping->second.find(ideology);
			 portraits != leaderPortraitMapping->second.end())
		{
			return portraits->second;
		}
	}

	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(cultureGroup);
		 leaderPortraitMapping != leaderPortraitMappings.end())
	{
		if (const auto portraits = leaderPortraitMapping->second.find(ideology);
			 portraits != leaderPortraitMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {"gfx/leaders/leader_unknown.dds"};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemalePortraits(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& type) const
{
	if (const auto femaleLeaderMapping = femalePortraitMappings.find(culture);
		 femaleLeaderMapping != femalePortraitMappings.end())
	{
		if (const auto portraits = femaleLeaderMapping->second.find(type); portraits != femaleLeaderMapping->second.end())
		{
			return portraits->second;
		}
	}

	if (const auto femaleLeaderMapping = femalePortraitMappings.find(cultureGroup);
		 femaleLeaderMapping != femalePortraitMappings.end())
	{
		if (const auto portraits = femaleLeaderMapping->second.find(type); portraits != femaleLeaderMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {"gfx/leaders/leader_unknown_female.dds"};
}


std::string Mappers::GraphicsMapper::getIdeologyMinisterPortrait(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& ideology)
{
	auto portraits = getIdeologyMinisterPortraits(culture, ideology);
	if (!portraits.empty())
	{
		std::string least_used_portrait;
		int least_used_times = std::numeric_limits<int>::max();
		for (const auto& portrait: portraits)
		{
			int times_used = 0;
			if (const auto& itr = used_portraits_.find(portrait); itr != used_portraits_.end())
			{
				times_used = itr->second;
			}

			if (times_used < least_used_times)
			{
				least_used_portrait = portrait;
				least_used_times = times_used;
			}
		}

		if (const auto& [itr, inserted] = used_portraits_.emplace(least_used_portrait, 1); itr != used_portraits_.end())
		{
			++itr->second;
		}

		return least_used_portrait;
	}

	portraits = getIdeologyMinisterPortraits(cultureGroup, ideology);
	if (!portraits.empty())
	{
		std::string least_used_portrait;
		int least_used_times = std::numeric_limits<int>::max();
		for (const auto& portrait: portraits)
		{
			int times_used = 0;
			if (const auto& itr = used_portraits_.find(portrait); itr != used_portraits_.end())
			{
				times_used = itr->second;
			}

			if (times_used < least_used_times)
			{
				least_used_portrait = portrait;
				least_used_times = times_used;
			}
		}

		if (const auto& [itr, inserted] = used_portraits_.emplace(least_used_portrait, 1); itr != used_portraits_.end())
		{
			++itr->second;
		}

		return least_used_portrait;
	}

	return "gfx/interface/ideas/idea_unknown.dds";
}


std::vector<std::string> Mappers::GraphicsMapper::getLeaderPortraits(const std::string& cultureOrGroup,
	 const std::string& ideology) const
{
	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(cultureOrGroup);
		 leaderPortraitMapping != leaderPortraitMappings.end())
	{
		if (const auto portraits = leaderPortraitMapping->second.find(ideology);
			 portraits != leaderPortraitMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getIdeologyMinisterPortraits(const std::string& cultureOrGroup,
	 const std::string& ideology) const
{
	if (const auto ideologyMinisterMapping = ideologyMinisterMappings.find(cultureOrGroup);
		 ideologyMinisterMapping != ideologyMinisterMappings.end())
	{
		if (const auto portraits = ideologyMinisterMapping->second.find(ideology);
			 portraits != ideologyMinisterMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getMaleOperativePortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto operativePortraitMapping = maleOperativeMappings.find(culture);
		 operativePortraitMapping != maleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	if (const auto operativePortraitMapping = maleOperativeMappings.find(cultureGroup);
		 operativePortraitMapping != maleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemaleOperativePortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto operativePortraitMapping = femaleOperativeMappings.find(culture);
		 operativePortraitMapping != femaleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	if (const auto operativePortraitMapping = femaleOperativeMappings.find(cultureGroup);
		 operativePortraitMapping != femaleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	return {};
}


std::optional<std::string> Mappers::GraphicsMapper::getGraphicalCulture(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto graphicalCulture = graphicalCultureMap.find(culture); graphicalCulture != graphicalCultureMap.end())
	{
		return graphicalCulture->second;
	}

	if (const auto graphicalCulture = graphicalCultureMap.find(cultureGroup);
		 graphicalCulture != graphicalCultureMap.end())
	{
		return graphicalCulture->second;
	}

	return std::nullopt;
}


std::optional<std::string> Mappers::GraphicsMapper::get2dGraphicalCulture(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto graphicalCulture2d = graphicalCulture2dMap.find(culture);
		 graphicalCulture2d != graphicalCulture2dMap.end())
	{
		return graphicalCulture2d->second;
	}

	if (const auto graphicalCulture2d = graphicalCulture2dMap.find(cultureGroup);
		 graphicalCulture2d != graphicalCulture2dMap.end())
	{
		return graphicalCulture2d->second;
	}

	return std::nullopt;
}


void Mappers::GraphicsMapper::debugPortraits(const Configuration& theConfiguration)
{
	if (!theConfiguration.getDebug())
	{
		return;
	}

	Log(LogLevel::Debug) << "Debugging portraits";
	std::set<std::string> portraitFiles;
	portraitFiles.merge(loadPortraitFiles(theConfiguration.getHoI4Path() + "/", "gfx/leaders/"));
	portraitFiles.merge(loadPortraitFiles("blankmod/", "gfx/leaders/"));
	portraitFiles.merge(loadPortraitFiles(theConfiguration.getHoI4Path() + "/", "gfx/interface/ideas/"));
	portraitFiles.merge(loadPortraitFiles("blankmod/", "gfx/interface/ideas/"));

	std::set<std::string> mapperPortraits;
	mapperPortraits.merge(loadPortraitMappings(armyPortraitMappings));
	mapperPortraits.merge(loadPortraitMappings(navyPortraitMappings));
	mapperPortraits.merge(loadPortraitMappings(maleMonarchMappings));
	mapperPortraits.merge(loadPortraitMappings(femaleMonarchMappings));
	mapperPortraits.merge(loadPortraitMappings(leaderPortraitMappings));
	mapperPortraits.merge(loadPortraitMappings(femalePortraitMappings));
	mapperPortraits.merge(loadPortraitMappings(ideologyMinisterMappings));

	for (const auto& portrait: mapperPortraits)
	{
		if (!portraitFiles.contains(portrait))
		{
			Log(LogLevel::Debug) << "Missing portrait: " << portrait;
			tryFindingPortrait(portrait, portraitFiles);
		}
	}
}


std::set<std::string> Mappers::GraphicsMapper::loadPortraitFiles(const std::string& root, const std::string& gfxFolder)
{
	std::set<std::string> portraitFiles;
	for (auto path: commonItems::GetAllFilesInFolderRecursive(root + gfxFolder))
	{
		path = gfxFolder + path;
		path = std::regex_replace(path, std::regex(R"(\\)"), "/");
		portraitFiles.insert(toLower(path));
	}
	return portraitFiles;
}


std::set<std::string> Mappers::GraphicsMapper::loadPortraitMappings(const culturesAndGroupsToPortraitsMap& mappings)
{
	std::set<std::string> mapperPortraits;
	for (const auto& culture: mappings | std::views::values)
	{
		for (const auto& portrait: culture)
		{
			mapperPortraits.insert(toLower(portrait));
		}
	}
	return mapperPortraits;
}


std::set<std::string> Mappers::GraphicsMapper::loadPortraitMappings(const ideologyToPortraitsMap& mappings)
{
	std::set<std::string> mapperPortraits;
	for (const auto& cultureGroup: mappings | std::views::values)
	{
		for (const auto& culture: cultureGroup | std::views::values)
		{
			for (const auto& portrait: culture)
			{
				mapperPortraits.insert(toLower(portrait));
			}
		}
	}
	return mapperPortraits;
}


std::string Mappers::GraphicsMapper::toLower(const std::string& oldString)
{
	std::string newString = oldString;
	std::transform(newString.begin(), newString.end(), newString.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	return newString;
}


void Mappers::GraphicsMapper::tryFindingPortrait(const std::string& path, std::set<std::string> portraitFiles)
{
	const auto& portraitName = trimExtension(trimPath(path));
	for (const auto& portraitFile: portraitFiles)
	{
		const auto& filename = trimExtension(trimPath(portraitFile));
		if (filename == portraitName)
		{
			Log(LogLevel::Debug) << " -> Potential match in " << portraitFile;
		}
	}
}
