#include "src/V2World/Culture/CultureGroupsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"



const std::set<std::string> north_americans{"central_algonquian",
	 "cherokee",
	 "cree",
	 "dakota",
	 "eastern_algonquian",
	 "eskaleut",
	 "inuit",
	 "iroquoian",
	 "metis",
	 "navajo",
	 "penutian",
	 "plains_algonquian",
	 "pueblo",
	 "siouan",
	 "native_american_minor"};

const std::set<std::string> central_americans{"chibchan", "mayan", "nahua", "sonoran", "tarascan", "zapotec"};

const std::set<std::string> south_americans{"aimara",
	 "amazonian",
	 "araucanian",
	 "caddoan",
	 "chacoan",
	 "guajiro",
	 "guarani",
	 "je",
	 "maranon",
	 "muskogean",
	 "na_dene",
	 "patagonian",
	 "quechua",
	 "tupinamba"};


Vic2::CultureGroups::Factory::Factory()
{
	parser_.registerRegex(commonItems::catchallRegex, [this](const std::string& group_name, std::istream& the_stream) {
		const auto culture_group = culture_group_factory_.GetCultureGroup(the_stream);
		if (culture_group.union_tag)
		{
			culture_groups_->union_tags_.insert(*culture_group.union_tag);
		}
		for (const auto& culture: culture_group.cultures)
		{
			// Fix HPM grouping all natives under one culture group
			if (group_name == "native_american")
			{
				if (north_americans.contains(culture))
				{
					culture_groups_->mappings_.insert(std::make_pair(culture, "native_north_american"));
				}
				else if (central_americans.contains(culture))
				{
					culture_groups_->mappings_.insert(std::make_pair(culture, "native_central_american"));
				}
				else if (south_americans.contains(culture))
				{
					culture_groups_->mappings_.insert(std::make_pair(culture, "native_south_american"));
				}
				else
				{
					culture_groups_->mappings_.insert(std::make_pair(culture, "native_carribean"));
				}
			}
			else
			{
				culture_groups_->mappings_.insert(make_pair(culture, group_name));
			}
		}
	});
}


std::unique_ptr<Vic2::CultureGroups> Vic2::CultureGroups::Factory::GetCultureGroups(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	Log(LogLevel::Info) << "Determining culture groups";

	culture_groups_ = std::make_unique<CultureGroups>();

	if (const auto cultures_file = mod_filesystem.GetActualFileLocation("/common/cultures.txt"); cultures_file)
	{
		parser_.parseFile(*cultures_file);
	}

	return std::move(culture_groups_);
}