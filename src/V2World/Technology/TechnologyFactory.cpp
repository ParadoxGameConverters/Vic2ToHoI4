#include "TechnologyFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::TechnologyFactory::TechnologyFactory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& technology, std::istream& theStream) {
		technologies.push_back(technology);
		commonItems::ignoreItem(technology, theStream);
	});
}


std::vector<std::string> Vic2::TechnologyFactory::importTechnologies(std::istream& theStream)
{
	technologies.clear();
	parseStream(theStream);
	return technologies;
}