#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PlaneModules::PlaneModules(std::istream& the_stream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& module_slot, std::istream& regex_stream) {
		modules_.insert(std::make_pair(module_slot, commonItems::getString(regex_stream)));
	});

	parseStream(the_stream);
}