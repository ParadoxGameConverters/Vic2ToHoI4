#include "ScriptedLocalisationFactory.h"
#include "ParserHelpers.h"



HoI4::ScriptedLocalisation::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		scriptedLocalisation->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("text", [this](std::istream& theStream) {
		scriptedLocalisation->texts.push_back(commonItems::stringOfItem(theStream).getString());
	});
}


std::unique_ptr<HoI4::ScriptedLocalisation> HoI4::ScriptedLocalisation::Factory::getScriptedLocalisation(
	 std::istream& theStream)
{
	scriptedLocalisation = std::make_unique<ScriptedLocalisation>();
	parseStream(theStream);
	return std::move(scriptedLocalisation);
}