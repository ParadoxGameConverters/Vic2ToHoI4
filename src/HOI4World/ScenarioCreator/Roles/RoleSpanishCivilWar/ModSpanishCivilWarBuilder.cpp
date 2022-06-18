#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"
#include "external/common_items/CommonRegexes.h"
#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include <regex>
#include <sstream>

// No string identifier can be a substring of another identifier for this to work
const std::string ModSpanishCivilWar::Builder::kFolder = "SpanishCivilWar";
const std::string ModSpanishCivilWar::Builder::kTag = "TAG";
const std::string ModSpanishCivilWar::Builder::kCapitalState = "CAPITAL_STATE";
const std::string ModSpanishCivilWar::Builder::kState = "THIS_STATE";
const std::string ModSpanishCivilWar::Builder::kPlotterIdeology = "OPPOSITION_IDEOLOGY";
const std::string ModSpanishCivilWar::Builder::kGovernmentIdeology = "GOVERNMENT_IDEOLOGY";

// ALL PARSING IS CURRENTLY EXPLORATORY. Parsing will be compartamentalized into functions and organized and all that
// jazz. Just trying to figure out the how of it right now, and what adjustments need to be made to the HoI4::decision
// classes

// Parse over mod files, create nessecary objects while find&replacing keywords to make the magic happen

// Could open the file, regex the stream then pass the stream to the parsers, but it wouldn't work
// Is there overhead to opening files so many times? If a decision must be crafted for every state
// that could be 50x opening and closing hte same file per decision like that.

// Alternatively, parse the file directly and then use accessors/settors on the resulting objects
// to regex out kTag for HUN and such.

// Ideally I could open a file and read everything into a stream, then work off copies of that stream
// to avoid excessive file i/o, does commonItems have such a feature?

// decision_categories.txt
ModSpanishCivilWar::Builder::Builder(std::shared_ptr<HoI4::Country> country)
{
	the_civil_war_mod_ = std::make_unique<ModSpanishCivilWar>();

	// May handle naively with regex in this case
	// Slap this in a function later
	std::string file = "Configurables/Scenarios/" + kFolder + "/decision_categories.txt";
	std::stringstream buffer_stream = GetStreamFromFile(file);
	std::string buffer = buffer_stream.str();
	std::stringstream input_stream;

	buffer = std::regex_replace(buffer, std::regex(kTag), country->getTag());
	buffer = std::regex_replace(buffer, std::regex(kCapitalState), std::to_string(country->getCapitalState().value()));

	input_stream << buffer;

	auto decision_categories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(input_stream);

	// decisions.txt
	// Slap this in a function later
	std::string file2 = "Configurables/Scenarios/" + kFolder + "/decisions.txt";
	std::stringstream buffer_stream2 = GetStreamFromFile(file2);
	std::string buffer2 = buffer_stream2.str();
	std::stringstream input_stream2;

	buffer2 = std::regex_replace(buffer2, std::regex(kTag), country->getTag());
	buffer2 = std::regex_replace(buffer2, std::regex(kState), "563");

	input_stream2 << buffer2;


	// Call parseStream to regex off country->getTag() + "_the_inevitable_civil_war bit
	// TAG_expand_influence_in_the_THIS_STATE_garrison is a single template that should be generated for multiple states
	registerRegex(commonItems::catchallRegex, [this](const std::string& category_name, std::istream& the_stream) {
		const HoI4::DecisionsInCategory decisions(category_name, the_stream);
		the_civil_war_mod_->AddDecisionsInCategory(decisions, category_name);
	});

	parseStream(input_stream2);
	clearRegisteredKeywords();

	the_civil_war_mod_->SetDecisionCategories(decision_categories);
}

// events.txt
