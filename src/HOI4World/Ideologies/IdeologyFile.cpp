#include "src/HOI4World/Ideologies/IdeologyFile.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Ideologies/Ideology.h"



HoI4::IdeologyFile::IdeologyFile(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideologyName, std::istream& theStream) {
		Ideology newIdeology(ideologyName, theStream);
		ideologies.insert(std::make_pair(ideologyName, newIdeology));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}