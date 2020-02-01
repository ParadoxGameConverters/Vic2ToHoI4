#include "ActualResources.h"
#include "ParserHelpers.h"



ActualResources::ActualResources(std::istream& theStream)
{
	registerKeyword(std::regex("[a-z_]+"), [this](const std::string& resourceName, std::istream& theStream) {
		const commonItems::singleDouble resourceAmount(theStream);
		theResources.insert(std::make_pair(resourceName, resourceAmount.getDouble()));
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}