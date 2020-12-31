#include "DockyardProvince.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::DockyardProvince::DockyardProvince(std::istream& theStream)
{
	registerKeyword("naval_base", [this](std::istream& theStream) {
		commonItems::singleInt baseInt(theStream);
		dockyardsLevel = baseInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}