#include "GraphicsCultureGroupFactory.h"
#include "ParserHelpers.h"



Mappers::GraphicsCultureGroup::Factory::Factory()
{
	registerKeyword("army_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->armyPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("navy_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->navyPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("male_monarch_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->maleMonarchPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("female_monarch_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->femaleMonarchPortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("leader_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->leaderPortraits = ideologyToPortraitsMappingFactory.importMapping(theStream);
	});
	registerKeyword("ideology_minister_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->ideologyMinisterPortraits = ideologyToPortraitsMappingFactory.importMapping(theStream);
	});
	registerKeyword("male_operative_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->maleOperativePortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("female_operative_portraits", [this](std::istream& theStream) {
		graphicsCultureGroup->femaleOperativePortraits = commonItems::stringList(theStream).getStrings();
	});
	registerKeyword("graphical_culture", [this](std::istream& theStream) {
		graphicsCultureGroup->graphicalCulture = commonItems::singleString(theStream).getString();
	});
	registerKeyword("graphical_culture_2d", [this](std::istream& theStream) {
		graphicsCultureGroup->graphicalCulture2D = commonItems::singleString(theStream).getString();
	});
}


std::unique_ptr<Mappers::GraphicsCultureGroup> Mappers::GraphicsCultureGroup::Factory::importCultureGroup(
	 std::istream& theStream)
{
	graphicsCultureGroup = std::make_unique<GraphicsCultureGroup>();
	parseStream(theStream);
	return std::move(graphicsCultureGroup);
}