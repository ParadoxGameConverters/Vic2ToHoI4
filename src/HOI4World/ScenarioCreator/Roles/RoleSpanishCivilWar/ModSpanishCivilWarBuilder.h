#ifndef MOD_SPANISH_CIVIL_WAR_BUILDER_H
#define MOD_SPANISH_CIVIL_WAR_BUILDER_H

#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"

class ModSpanishCivilWar::Builder: commonItems::parser
{
  public:
	Builder(const std::shared_ptr<HoI4::Country> country, const date& the_date);
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
	void BuildDecisions(const std::string tag);
	void BuildEvents(const std::string tag, const IdeologicalSituationSet& ideological_situation);
	void BuildIdeas();
	void BuildFoci(const std::string tag, const IdeologicalSituationSet& ideological_situation);
	void BuildUpdatedElections(const std::shared_ptr<HoI4::Country> country, const date& the_date);

	void BuildType1Foci(commonItems::blobList blobs, std::vector<HoI4::State> noncontiguous_states);
	void BuildType2Foci(std::istream& the_stream);

	static void AddIntervention(const std::shared_ptr<ModSpanishCivilWar> the_war, const HoI4::Country& interveener);


	std::unique_ptr<ModSpanishCivilWar> the_civil_war_mod_;
};

#endif // MOD_SPANISH_CIVIL_WAR_BUILDER_H