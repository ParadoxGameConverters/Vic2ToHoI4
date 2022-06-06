#include "ActualResources.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::ActualResources::ActualResources(std::istream& theStream)
{
	registerRegex("[a-z_]+", [this](const std::string& resourceName, std::istream& theStream) {
		const commonItems::singleDouble resourceAmount(theStream);
		theResources.insert(std::make_pair(resourceName, resourceAmount.getDouble()));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}