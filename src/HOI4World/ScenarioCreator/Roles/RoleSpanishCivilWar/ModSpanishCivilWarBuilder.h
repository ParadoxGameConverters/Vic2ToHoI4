#ifndef MOD_SPANISH_CIVIL_WAR_BUILDER_H
#define MOD_SPANISH_CIVIL_WAR_BUILDER_H

#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/HoI4Focus.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"

class ModSpanishCivilWar::Builder: commonItems::parser
{
  public:
	Builder(const std::shared_ptr<HoI4::Country> country,
		 const date& the_date,
		 const std::unique_ptr<Maps::MapData>& map_data,
		 const std::unique_ptr<HoI4::States>& the_states);
	std::unique_ptr<ModSpanishCivilWar> Build() { return std::move(the_civil_war_mod_); }

  private:
	static const std::string kFolder;
	static const std::string kTag;
	static const std::string kCapitalState;
	static const std::string kState;
	static const std::string kNonContiguousState;
	static const std::string kPlotterIdeology;
	static const std::string kGovernmentIdeology;

	void BuildDecisionCategories(const std::string tag, const int captial_state_id);
	void BuildDecisions(const std::string tag, const int captial_state_id);
	void BuildEvents(const std::string tag, const IdeologicalSituationSet& ideological_situation);
	void BuildIdeas();
	void BuildFoci(const std::string tag,
		 const IdeologicalSituationSet& ideological_situation,
		 const std::set<int>& home_state_ids,
		 const std::set<int>& noncontiguous_state_ids);
	void BuildUpdatedElections(const std::shared_ptr<HoI4::Country> country, const date& the_date);

	void BuildType1Foci(commonItems::blobList blobs, std::set<int> noncontiguous_state_ids);
	void BuildType2Foci(commonItems::blobList blobs);

	std::unique_ptr<ModSpanishCivilWar> the_civil_war_mod_;

	std::vector<HoI4Focus> national_focuses_;
};

#endif // MOD_SPANISH_CIVIL_WAR_BUILDER_H