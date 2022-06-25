#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/WarCreator/MapUtils.h"
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


ModSpanishCivilWar::Builder::Builder(const std::shared_ptr<HoI4::Country> country,
	 const date& the_date,
	 const std::unique_ptr<Maps::MapData>& map_data,
	 const std::unique_ptr<HoI4::States>& the_states)
{
	the_civil_war_mod_ = std::make_unique<ModSpanishCivilWar>();

	BuildUpdatedElections(country, the_date);
	BuildDecisionCategories(country->getTag(), country->getCapitalState().value());
	auto the_ideological_situation =
		 GetIdeologicalSituation(country->getIdeologySupport(), country->getGovernmentIdeology());
	BuildEvents(country->getTag(), the_ideological_situation);

	// Combine contiguous and disconnectes_states in a struct? How many more variations will be needed later? Some.
	auto contiguous_areas =
		 country->getContiguousAreas(map_data, the_states->getStates(), the_states->getProvinceToStateIDMap());
	auto contiguous_states = HoI4::MapUtils::getStatesInArea(contiguous_areas[0], the_states->getProvinceToStateIDMap());
	auto disconnected_states = GetDissconnectedStates(contiguous_areas, the_states->getProvinceToStateIDMap());

	BuildFoci(country->getTag(), the_ideological_situation, contiguous_states, disconnected_states);
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

void ModSpanishCivilWar::Builder::BuildDecisions(const std::string tag, const int captial_state_id)
{
	std::string buffer = GetFileBufferStr("decision_categories.txt", kFolder);
	std::stringstream input_stream;

	buffer = std::regex_replace(buffer, std::regex(kTag), tag);
	buffer = std::regex_replace(buffer, std::regex(kState), std::to_string(captial_state_id));

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
void ModSpanishCivilWar::Builder::BuildFoci(const std::string tag,
	 const IdeologicalSituationSet& ideological_situation,
	 const std::set<int>& home_state_ids,
	 const std::set<int>& disconnected_state_ids)
{
	std::string buffer = GetFileBufferStr("foci.txt", kFolder);
	std::stringstream input_stream;

	auto situation_iter = ideological_situation.begin();

	buffer = std::regex_replace(buffer, std::regex(kTag), tag);
	buffer = std::regex_replace(buffer, std::regex(kGovernmentIdeology), situation_iter->ideology_);
	buffer = std::regex_replace(buffer, std::regex(kPlotterIdeology), (++situation_iter)->ideology_);

	input_stream << buffer;

	// Rename types once all foci are known
	// Send them out for additional processing by unique needs
	registerKeyword("type1", [this, disconnected_state_ids](std::istream& the_stream) {
		auto blobs = commonItems::blobList(the_stream);
		BuildType1Foci(blobs, disconnected_state_ids);
	});
	registerKeyword("type2", [this](std::istream& the_stream) {
		auto blobs = commonItems::blobList(the_stream);
		BuildType2Foci(blobs);
	});

	parseStream(input_stream);
	clearRegisteredKeywords();

	// Use national_foci_ vector to make focus tree
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

void ModSpanishCivilWar::Builder::BuildType1Foci(commonItems::blobList blobs, std::set<int> noncontiguous_state_ids)
{
	// Noncontiguous states templating

	const auto& buffer_foci = blobs.getBlobs();
	std::string delimiter = "\n\t\t\t\t\t\tstate = " + kNonContiguousState;
	std::vector<std::string> insertions;

	for (const auto& state_id: noncontiguous_state_ids)
	{
		insertions.push_back("\n\t\t\t\t\t\tstate = " + std::to_string(state_id));
	}

	std::map<std::string, std::vector<std::string>> template_instructions{{delimiter, insertions}};

	auto streams = ParsableStreamsFromTemplate(buffer_foci, template_instructions);

	for (auto& stream: streams)
	{
		national_focuses_.push_back(HoI4Focus(stream));
	}
}

void ModSpanishCivilWar::Builder::BuildType2Foci(commonItems::blobList blobs)
{
	// No templating, just straight up after regex
	const auto& buffer_foci = blobs.getBlobs();

	for (const auto& foci : buffer_foci)
	{
		std::stringstream stream(foci);
		national_focuses_.push_back(HoI4Focus(stream));
	}
}