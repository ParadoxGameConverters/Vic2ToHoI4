#include "IdeologyFile.h"
#include "HOI4Ideology.h"



HoI4::IdeologyFile::IdeologyFile(std::istream& theStream)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& ideologyName, std::istream& theStream)
	{
		HoI4Ideology* newIdeology = new HoI4Ideology(ideologyName, theStream);
		ideologies.insert(make_pair(ideologyName, newIdeology));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}