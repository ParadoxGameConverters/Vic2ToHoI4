#include "PortraitFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::PortraitFactory::PortraitFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& size, std::istream& input) {
		size_ = size;
		definition_ = commonItems::getString(input);
	});
}


HoI4::Portrait HoI4::PortraitFactory::importPortrait(std::string_view type, std::istream& input)
{
	size_.clear();
	definition_.clear();

	parseStream(input);

	return Portrait(type, size_, definition_);
}