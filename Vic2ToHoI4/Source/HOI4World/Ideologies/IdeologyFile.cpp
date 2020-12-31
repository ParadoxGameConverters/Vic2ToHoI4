#include "IdeologyFile.h"
#include "CommonRegexes.h"
#include "Ideology.h"
#include "ParserHelpers.h"



HoI4::IdeologyFile::IdeologyFile(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideologyName, std::istream& theStream) {
		Ideology newIdeology(ideologyName, theStream);
		ideologies.insert(std::make_pair(ideologyName, newIdeology));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}