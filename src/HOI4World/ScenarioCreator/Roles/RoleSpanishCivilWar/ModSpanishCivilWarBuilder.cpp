#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include <regex>
#include <sstream>

// No string identifier can be a substring of another identifier for this to work
const std::string ModSpanishCivilWar::Builder::kFolder = "SpanishCivilWar";
const std::string ModSpanishCivilWar::Builder::kTag = "TAG";
const std::string ModSpanishCivilWar::Builder::kCapitalState = "CAPITAL_STATE";
const std::string ModSpanishCivilWar::Builder::kState = "THIS_STATE";
const std::string ModSpanishCivilWar::Builder::kNonContiguousState = "DISCONNECTED_STATE";
const std::string ModSpanishCivilWar::Builder::kPlotterIdeology = "OPPOSITION_IDEOLOGY";
const std::string ModSpanishCivilWar::Builder::kGovernmentIdeology = "GOVERNMENT_IDEOLOGY";


ModSpanishCivilWar::Builder::Builder(const std::shared_ptr<HoI4::Country> country, const date& the_date)
{
	the_civil_war_mod_ = std::make_unique<ModSpanishCivilWar>();

	BuildUpdatedElections(country, the_date);
	BuildDecisionCategories(country->getTag(), country->getCapitalState().value());
	auto the_ideological_situation =
		 GetIdeologicalSituation(country->getIdeologySupport(), country->getGovernmentIdeology());
	BuildEvents(country->getTag(), the_ideological_situation);
	BuildFoci(country->getTag(), the_ideological_situation);
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
	 const IdeologicalSituationSet& ideological_situation)
{
	the_civil_war_mod_->election_on_action_event_ = tag + "_scw.1";
}

void ModSpanishCivilWar::Builder::BuildIdeas()
{
}

// Investigate how war creator does its branch thing
void ModSpanishCivilWar::Builder::BuildFoci(const std::string tag, const IdeologicalSituationSet& ideological_situation)
{
	std::string buffer = GetFileBufferStr("foci.txt", kFolder);
	std::stringstream input_stream;

	auto situation_iter = ideological_situation.begin(); // Maybe assign out what we need to local variables?

	buffer = std::regex_replace(buffer, std::regex(kTag), tag);
	buffer = std::regex_replace(buffer, std::regex(kGovernmentIdeology), situation_iter->ideology_);
	buffer = std::regex_replace(buffer, std::regex(kPlotterIdeology), (++situation_iter)->ideology_);

	input_stream << buffer;

	// Rename types once all foci are known
	// Send them out for additional processing by unique needs
	registerKeyword("type1", [this](std::istream& the_stream) {
		auto blobs = commonItems::blobList(the_stream);
		BuildType1Foci(blobs, std::vector<HoI4::State>()); // Need the map data
	});
	registerKeyword("type2", [this](std::istream& the_stream) {
		BuildType2Foci(the_stream);
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

void ModSpanishCivilWar::Builder::BuildType1Foci(commonItems::blobList blobs,
	 std::vector<HoI4::State> noncontiguous_states)
{
	// Duplicate lines with kNonContiguousState for each state in country that matches
	// Then build the focus
	const auto& buffer_foci = blobs.getBlobs();
	std::string delimiter = "\n\t\t\t\t\t\tstate = " + kNonContiguousState;
	
	for (auto buffer: buffer_foci)
	{
		if(const auto insert_position = buffer.find(delimiter) + delimiter.size(); insert_position != std::string::npos)
		{
			for (const auto& state: noncontiguous_states)
			{
				std::string to_insert = "\n\t\t\t\t\t\tstate = " + std::to_string(state.getID());
				buffer.insert(insert_position, to_insert);
			}

			buffer = std::regex_replace(buffer, std::regex(delimiter), "");

			std::stringstream input_stream;
			input_stream << buffer;

			the_civil_war_mod_->AddFocus(std::make_shared<HoI4Focus>(input_stream));
		}
		else
		{
			Log(LogLevel::Warning) << "Couldn't generate type1 national focus for " << the_civil_war_mod_->GetName();
		}
	}
}

void ModSpanishCivilWar::Builder::BuildType2Foci(std::istream& the_stream)
{
	the_civil_war_mod_->AddFocus(std::make_shared<HoI4Focus>(the_stream));
}

void ModSpanishCivilWar::Builder::AddIntervention(const std::shared_ptr<ModSpanishCivilWar> the_war,
	 const HoI4::Country& interveener)
{
}
