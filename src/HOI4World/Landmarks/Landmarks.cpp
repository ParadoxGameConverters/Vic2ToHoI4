#include "src/HOI4World/Landmarks/Landmarks.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::Landmarks::Landmarks(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& landmarkName, std::istream& theStream) {
		const Landmark newLandmark(landmarkName, theStream);
		buildings[landmarkName] = std::make_shared<HoI4::Landmark>(newLandmark);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}