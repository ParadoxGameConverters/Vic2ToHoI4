#include "GraphicsCultureGroup.h"
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
		leaderPortraits = ideologyToPortraitsMappingFactory.importMapping(theStream);
	});
	registerKeyword("ideology_minister_portraits", [this](std::istream& theStream) {
		ideologyMinisterPortraits = ideologyToPortraitsMappingFactory.importMapping(theStream);
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