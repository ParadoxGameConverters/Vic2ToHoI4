#include "src/HOI4World/MilitaryMappings/SubstitutesImporter.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::substitutesImporter::substitutesImporter(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& left, std::istream& theStream) {
		const commonItems::singleString right(theStream);
		substitutes.insert(std::make_pair(left, right.getString()));
	});

	parseStream(theStream);
}