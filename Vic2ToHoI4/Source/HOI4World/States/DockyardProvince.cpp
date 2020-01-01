#include "DockyardProvince.h"
#include "ParserHelpers.h"



HoI4::DockyardProvince::DockyardProvince(std::istream& theStream)
{
	registerKeyword(std::regex("naval_base"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt baseInt(theStream);
		dockyardsLevel = baseInt.getInt();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}