#include "OutCountryCategories.h"
#include "OutCountryCategory.h"
#include <fstream>



void HoI4::outCountryCategories(const std::map<std::string, TagsAndExtras>& countryCategories,
	 const std::string& outputName)
{
	std::ofstream countryCategoriesFile("output/" + outputName + "/common/scripted_triggers/country_categories.txt");

	for (const auto& [category, tagsAndExtras]: countryCategories)
	{
		outputCountryCategory(countryCategoriesFile, category, tagsAndExtras);
	}

	countryCategoriesFile.close();
}