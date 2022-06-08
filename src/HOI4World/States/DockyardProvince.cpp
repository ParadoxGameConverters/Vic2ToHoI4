#include "src/HOI4World/States/DockyardProvince.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::DockyardProvince::DockyardProvince(std::istream& theStream)
{
	registerKeyword("naval_base", [this](std::istream& theStream) {
		commonItems::singleInt baseInt(theStream);
		dockyardsLevel = baseInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}