#include "GraphicsCultureGroup.h"
#include "IdeologyToPortraitsMapping.h"
#include "ParserHelpers.h"



Mappers::GraphicsCultureGroup::GraphicsCultureGroup(std::istream& theStream)
{
	registerKeyword("army_portraits", [this](std::istream& theStream) {
		armyPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("navy_portraits", [this](std::istream& theStream) {
		navyPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("male_monarch_portraits", [this](std::istream& theStream) {
		maleMonarchPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("female_monarch_portraits", [this](std::istream& theStream) {
		femaleMonarchPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("leader_portraits", [this](std::istream& theStream) {
		IdeologyToPortraitsMapping mappings(theStream);
		leaderPortraits = mappings.getMap();
	});
	registerKeyword("ideology_minister_portraits", [this](std::istream& theStream) {
		IdeologyToPortraitsMapping mappings(theStream);
		ideologyMinisterPortraits = mappings.getMap();
	});
	registerKeyword("graphical_culture", [this](std::istream& theStream) {
		commonItems::stringList graphicsString(theStream);
		graphicalCulture = graphicsString.getStrings()[0];
	});
	registerKeyword("graphical_culture_2d", [this](std::istream& theStream) {
		commonItems::stringList graphicsString(theStream);
		graphicalCulture2D = graphicsString.getStrings()[0];
	});

	parseStream(theStream);
}