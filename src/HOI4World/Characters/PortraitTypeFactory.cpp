#include "src/HOI4World/Characters/PortraitTypeFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PortraitTypeFactory::PortraitTypeFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& size, std::istream& input) {
		portraits_.emplace_back(Portrait{type_, size, commonItems::getString(input)});
	});
}



std::vector<HoI4::Portrait> HoI4::PortraitTypeFactory::importPortraits(std::string_view type, std::istream& input)
{
	type_ = type;
	portraits_.clear();
	parseStream(input);
	return portraits_;
}