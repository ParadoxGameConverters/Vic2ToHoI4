#include "ScriptedLocalisationFactory.h"
#include "ParserHelpers.h"



HoI4::ScriptedLocalisation::Factory::Factory()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		scriptedLocalisation->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("text", [this](const std::string& unused, std::istream& theStream) {
		scriptedLocalisation->texts.push_back(commonItems::singleItem(unused, theStream));
	});
}


std::unique_ptr<HoI4::ScriptedLocalisation> HoI4::ScriptedLocalisation::Factory::getScriptedLocalisation(
	 std::istream& theStream)
{
	scriptedLocalisation = std::make_unique<ScriptedLocalisation>();
	parseStream(theStream);
	return std::move(scriptedLocalisation);
}