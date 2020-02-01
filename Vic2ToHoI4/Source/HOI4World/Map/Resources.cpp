#include "Resources.h"
#include "ResourcesLink.h"
#include "ParserHelpers.h"



Resources::Resources() noexcept
{
	registerKeyword(std::regex("link"), [this](const std::string& unused, std::istream& theStream){
		ResourcesLink theLink(theStream);
		resourceMap.insert(std::make_pair(theLink.getProvinceNum(), theLink.takeResources()));
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseFile("DataFiles/resources.txt");
	clearRegisteredKeywords();
}


std::map<std::string, double> Resources::getResourcesInProvince(const int provinceNum) const
{
	if (const auto mapping = resourceMap.find(provinceNum); mapping != resourceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}