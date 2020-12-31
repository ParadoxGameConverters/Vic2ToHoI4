#include "SubstitutesImporter.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::substitutesImporter::substitutesImporter(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& left, std::istream& theStream) {
		const commonItems::singleString right(theStream);
		substitutes.insert(std::make_pair(left, right.getString()));
	});

	parseStream(theStream);
}