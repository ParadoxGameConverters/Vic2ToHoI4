#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"
#include <regex>

// No string identifier can be a substring of another identifier for this to work
const std::string ModSpanishCivilWar::Builder::kFolder = "SpanishCivilWar";
const std::string ModSpanishCivilWar::Builder::kTag = "TAG";
const std::string ModSpanishCivilWar::Builder::kCapitalState = "CAPITAL_STATE";
const std::string ModSpanishCivilWar::Builder::kState = "THIS_STATE";
const std::string ModSpanishCivilWar::Builder::kPlotterIdeology = "OPPOSITION_IDEOLOGY";
const std::string ModSpanishCivilWar::Builder::kGovernmentIdeology = "GOVERNMENT_IDEOLOGY";

// Parse over mod files, create nessecary objects while find&replacing keywords to make the magic happen

// Could open the file, regex the stream then pass the stream to the parsers, but it wouldn't work
// Is there overhead to opening files so many times? If a decision must be crafted for every state
// that could be 50x opening and closing hte same file per decision like that.

// Alternatively, parse the file directly and then use accessors/settors on the resulting objects
// to regex out kTag for HUN and such.

// Ideally I could open a file and read everything into a stream, then work off copies of that stream
// to avoid excessive file i/o, does commonItems have such a feature?

// decision_categories.txt
ModSpanishCivilWar::Builder::Builder()
{
	the_civil_war_mod_ = std::make_unique<ModSpanishCivilWar>();

	// May handle naively with regex in this case
	auto decision_categories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(
		 "Configurables/Scenarios/SpanishCivilWar/decision_categories.txt");
	for (auto& category: decision_categories->getTheCategories())
	{
		// Regex all of the constants out at the appropitate places
	}

	// Thats a std::move on each end, probably a better way to do it
	the_civil_war_mod_->SetDecisionCategories(decision_categories);
}

// decisions.txt

// events.txt
