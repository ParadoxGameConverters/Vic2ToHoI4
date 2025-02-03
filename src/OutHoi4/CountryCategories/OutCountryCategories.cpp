#include "src/OutHoi4/CountryCategories/OutCountryCategories.h"
#include "src/OutHoi4/CountryCategories/OutCountryCategory.h"
#include <fstream>



void HoI4::outCountryCategories(const std::map<std::string, TagsAndExtras>& countryCategories,
	 const std::filesystem::path& outputName)
{
	const std::filesystem::path filename = "output" / outputName / "common/scripted_triggers/country_categories.txt";
	std::ofstream countryCategoriesFile(filename);

	for (const auto& [category, tagsAndExtras]: countryCategories)
	{
		outputCountryCategory(countryCategoriesFile, category, tagsAndExtras);
	}

	countryCategoriesFile.close();
}