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
ModSpanishCivilWar::Builder::Builder(const std::shared_ptr<HoI4::Country> country, const date& the_date)
{
	the_civil_war_mod_ = std::make_unique<ModSpanishCivilWar>();

	BuildUpdatedElections(country, the_date);
	BuildDecisionCategories(country->getTag(), country->getCapitalState().value());
	BuildEvents(country->getTag(), country->getIdeologySupport(), country->getGovernmentIdeology());
}

void ModSpanishCivilWar::Builder::BuildDecisionCategories(const std::string tag, const int capital_state_id)
{
	std::string buffer = GetFileBufferStr("decision_categories.txt", kFolder);
	std::stringstream input_stream;

	buffer = std::regex_replace(buffer, std::regex(kTag), tag);
	buffer = std::regex_replace(buffer, std::regex(kCapitalState), std::to_string(capital_state_id));

	input_stream << buffer;

	auto decision_categories = HoI4::DecisionsCategories::Factory().getDecisionsCategories(input_stream);

	the_civil_war_mod_->SetDecisionCategories(decision_categories);
}

void ModSpanishCivilWar::Builder::BuildDecisions(const std::string tag)
{
	std::string buffer = GetFileBufferStr("decision_categories.txt", kFolder);
	std::stringstream input_stream;

	buffer = std::regex_replace(buffer, std::regex(kTag), tag);
	buffer = std::regex_replace(buffer, std::regex(kState), "563");

	input_stream << buffer;

	// Call parseStream to regex off country->getTag() + "_the_inevitable_civil_war bit
	// TAG_expand_influence_in_the_THIS_STATE_garrison is a single template that should be generated for multiple states
	registerRegex(commonItems::catchallRegex, [this](const std::string& category_name, std::istream& the_stream) {
		const HoI4::DecisionsInCategory decisions(category_name, the_stream);
		the_civil_war_mod_->AddDecisionsInCategory(decisions, category_name);
	});

	// TBD decisions/events
	// SPA_hand_over_the_ceda_campaign_chest_mission
	// SPR_military_plot_republicans // Unessecary duplication in vanilla?
	// lar_spain.4
	// lar_spain.5
	// SPR_secure_the_guardia_de_asalto_mission
	// SPR_secure_the_guardia_civil_mission
	// SPA_military_plot_nationalists
	// id = lar_spain.3
	//
	// TBD ideas
	// SPR_government_power_struggle
}

void ModSpanishCivilWar::Builder::BuildEvents(const std::string tag,
	 const std::map<std::string, int> ideology_support,
	 const std::string gov_ideology)
{
	the_civil_war_mod_->election_on_action_event_ = tag + "_scw.1";
}

void ModSpanishCivilWar::Builder::BuildIdeas()
{
}

void ModSpanishCivilWar::Builder::BuildFoci(const std::string tag,
	 const std::map<std::string, int> ideology_support,
	 const std::string gov_ideology)
{
	std::string buffer = GetFileBufferStr("foci.txt", kFolder);
	std::stringstream input_stream;

	buffer = std::regex_replace(buffer, std::regex(kTag), tag);

	input_stream << buffer;

	// Rename types once all foci are known
	registerKeyword("type1", [this](std::istream& the_stream) {;
		BuildType1Foci(the_stream);
	});

	parseStream(input_stream);
	clearRegisteredKeywords();
}

void ModSpanishCivilWar::Builder::BuildUpdatedElections(const std::shared_ptr<HoI4::Country> country,
	 const date& the_date)
{
	date election_day = the_date;
	election_day.increaseByMonths(1);
	election_day = date(election_day.getYear(), election_day.getMonth(), election_day.getDay() % 28 + 1);
	election_day.subtractYears(4);

	country->setLastElection(election_day);
	country->setLastElection36(date(1932, 2, election_day.getDay()));
}

void ModSpanishCivilWar::Builder::BuildType1Foci(std::istream& the_stream)
{
	// Do addition regex and cyclic fills
	// send new stream to Foci ctor
}

void ModSpanishCivilWar::Builder::AddIntervention(const std::shared_ptr<ModSpanishCivilWar> the_war,
	 const HoI4::Country& interveener)
{
}
