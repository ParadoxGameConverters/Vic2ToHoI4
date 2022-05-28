#include "ScriptedLocalisationsFactory.h"
#include "ParserHelpers.h"



HoI4::ScriptedLocalisations::Factory::Factory()
{
	registerKeyword("defined_text", [this](std::istream& theStream) {
		scriptedLocalisations->ideologyLocalisations.push_back(*factory.getScriptedLocalisation(theStream));
	});
}


std::unique_ptr<HoI4::ScriptedLocalisations> HoI4::ScriptedLocalisations::Factory::getScriptedLocalisations()
{
	scriptedLocalisations = std::make_unique<ScriptedLocalisations>();
	parseFile("blankMod/output/common/scripted_localisation/ideologies.txt");
	return std::move(scriptedLocalisations);
}