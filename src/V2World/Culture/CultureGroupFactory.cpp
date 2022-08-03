#include "src/V2World/Culture/CultureGroupFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::CultureGroupFactory::CultureGroupFactory()
{
	registerRegex("leader|is_overseas|unit", [this](const std::string& unused, std::istream& the_stream) {
		commonItems::ignoreItem(unused, the_stream);
	});
	registerKeyword("union", [this](std::istream& the_stream) {
		union_tag_ = commonItems::getString(the_stream);
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& culture_name, std::istream& the_stream) {
		culture_group_.push_back(culture_name);
		commonItems::ignoreItem(culture_name, the_stream);
	});
}


Vic2::CultureGroup Vic2::CultureGroupFactory::GetCultureGroup(std::istream& the_stream)
{
	culture_group_.clear();
	union_tag_.reset();
	parseStream(the_stream);
	return {.cultures = culture_group_, .union_tag = union_tag_};
}