#include "src/HOI4World/Map/Resources.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Map/ResourcesLink.h"



HoI4::Resources::Resources() noexcept
{
	registerKeyword("link", [this](std::istream& theStream) {
		ResourcesLink theLink(theStream);

		const auto province = theLink.getProvinceNum();
		auto newResources = theLink.takeResources();

		auto& existingResources = resourceMap[province]; // creates entry if missing

		for (const auto& [resource, amount]: newResources)
		{
			existingResources[resource] += amount;
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("Configurables/resources.txt");
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