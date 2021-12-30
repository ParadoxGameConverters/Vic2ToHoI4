#include "PortraitsFactory.h"
#include "CommonRegexes.h"



HoI4::PortraitsFactory::PortraitsFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& type, std::istream& input) {
		const auto newPortraits = portraitTypeFactory.importPortraits(type, input);
		for (const auto& newPortrait: newPortraits)
		{
			portraits_.push_back(newPortrait);
		}
	});
}


std::vector<HoI4::Portrait> HoI4::PortraitsFactory::importPortraits(std::istream& input)
{
	portraits_.clear();
	parseStream(input);
	return portraits_;
}