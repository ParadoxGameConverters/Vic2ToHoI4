#include "src/HOI4World/Landmarks/Landmark.h"
#include "external/common_items/ParserHelpers.h"



HoI4::Landmark::Landmark(const std::string& landmarkName, std::istream& theStream): name(std::move(landmarkName))
{
	registerKeyword("country_modifiers", [this](std::istream& theStream) {
		countryModifiers = new LandmarkModifiers(theStream);
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& propertyName, std::istream& theStream) {
		properties.push_back(std::make_pair(propertyName, commonItems::stringOfItem{theStream}.getString()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}