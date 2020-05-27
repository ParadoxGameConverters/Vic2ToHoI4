#include "Resources.h"
#include "ParserHelpers.h"
#include "ResourcesLink.h"



HoI4::Resources::Resources() noexcept
{
	registerKeyword("link", [this](const std::string& unused, std::istream& theStream) {
		ResourcesLink theLink(theStream);
		resourceMap.insert(std::make_pair(theLink.getProvinceNum(), theLink.takeResources()));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("DataFiles/resources.txt");
	clearRegisteredKeywords();
}


std::map<std::string, double> HoI4::Resources::getResourcesInProvince(const int provinceNum) const
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