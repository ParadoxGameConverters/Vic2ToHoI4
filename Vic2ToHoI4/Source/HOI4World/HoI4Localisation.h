#ifndef HOI4_LOCALISATION_H
#define HOI4_LOCALISATION_H



#include "Configuration.h"
#include "Localisations/ArticleRules/ArticleRules.h"
#include "Mappers/CountryName/CountryNameMapper.h"
#include "Mappers/Government/GovernmentMapper.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "ScriptedLocalisations/ScriptedLocalisations.h"
#include "States/HoI4State.h"
#include "States/HoI4States.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/States/State.h"
#include "V2World/States/StateDefinitions.h"
#include <map>
#include <optional>
#include <string>



namespace HoI4
{

using keyToLocalisationMap = std::map<std::string, std::string>;					  // key -> localisation
using languageToLocalisationsMap = std::map<std::string, keyToLocalisationMap>; // language -> (key -> localisation)

using language = std::string;
using stateNumber = int;



class Localisation
{
  public:
	class Importer;

	Localisation(std::map<language, std::map<stateNumber, std::string>> stateLocalisations,
		 languageToLocalisationsMap VPLocalisations,
		 languageToLocalisationsMap countryLocalisations,
		 languageToLocalisationsMap originalFocuses,
		 languageToLocalisationsMap newFocuses,
		 languageToLocalisationsMap ideaLocalisations,
		 languageToLocalisationsMap genericIdeaLocalisations,
		 languageToLocalisationsMap originalEventLocalisations,
		 languageToLocalisationsMap newEventLocalisations,
		 languageToLocalisationsMap politicalPartyLocalisations,
		 languageToLocalisationsMap decisionLocalisations,
		 languageToLocalisationsMap customLocalisations):
		 stateLocalisations(std::move(stateLocalisations)),
		 VPLocalisations(std::move(VPLocalisations)), countryLocalisations(std::move(countryLocalisations)),
		 originalFocuses(std::move(originalFocuses)), newFocuses(std::move(newFocuses)),
		 ideaLocalisations(std::move(ideaLocalisations)), genericIdeaLocalisations(std::move(genericIdeaLocalisations)),
		 originalEventLocalisations(std::move(originalEventLocalisations)),
		 newEventLocalisations(std::move(newEventLocalisations)),
		 politicalPartyLocalisations(std::move(politicalPartyLocalisations)),
		 decisionLocalisations(std::move(decisionLocalisations)), customLocalisations(std::move(customLocalisations))
	{
	}

	void addStateLocalisation(const State& hoi4State,
		 const Vic2::State& vic2State,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const Vic2::Localisations& vic2Localisations,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<std::string, std::string>& grammarMappings);
	void addStateLocalisations(const States& states,
		 const Vic2::Localisations& vic2Localisations,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const Configuration& theConfiguration);
	void createCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags,
		 const Mappers::CountryNameMapper& countryNameMapper,
		 const std::set<std::string>& majorIdeologies,
		 const Vic2::Localisations& vic2Localisations,
		 const ArticleRules& articleRules);
	void updateMainCountryLocalisation(const std::string& HoI4Key,
		 const std::string& Vic2Tag,
		 const std::string& Vic2Government,
		 const Vic2::Localisations& vic2Localisations,
		 const ArticleRules& articleRules);
	void addNonenglishCountryLocalisations();
	void copyFocusLocalisations(const std::string& oldKey, const std::string& newKey);
	void copyEventLocalisations(const std::string& oldKey, const std::string& newKey);
	void addEventLocalisation(const std::string& event, const std::string& localisation);
	void addEventLocalisationFromVic2(const std::string& Vic2Key,
		 const std::string& HoI4Key,
		 const Vic2::Localisations& vic2Localisations);
	void addIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation);
	void addIdeaLocalisation(const std::string& idea, const std::string& localisation, const std::string& language);
	void addPoliticalPartyLocalisation(const std::string& Vic2Key,
		 const std::string& HoI4Key,
		 const Vic2::Localisations& vic2Localisations);
	void addDecisionLocalisation(const std::string& key, const std::optional<std::string>& localisation);
	void generateCustomLocalisations(ScriptedLocalisations& scriptedLocalisations,
		 const std::set<std::string>& majorIdeologies);
	void updateLocalisationText(const std::string& key, const std::string& oldText, const std::string& newText);

	[[nodiscard]] const auto& getStateLocalisations() const { return stateLocalisations; }
	[[nodiscard]] const auto& getVPLocalisations() const { return VPLocalisations; }
	[[nodiscard]] const auto& getCountryLocalisations() const { return countryLocalisations; }
	[[nodiscard]] const auto& getOriginalFocuses() const { return originalFocuses; }
	[[nodiscard]] const auto& getNewFocuses() const { return newFocuses; }
	[[nodiscard]] const auto& getIdeaLocalisations() const { return ideaLocalisations; }
	[[nodiscard]] const auto& getGenericIdeaLocalisations() const { return genericIdeaLocalisations; }
	[[nodiscard]] const auto& getOriginalEventLocalisations() const { return originalEventLocalisations; }
	[[nodiscard]] const auto& getNewEventLocalisations() const { return newEventLocalisations; }
	[[nodiscard]] const auto& getPoliticalPartyLocalisations() const { return politicalPartyLocalisations; }
	[[nodiscard]] const auto& getDecisionLocalisations() const { return decisionLocalisations; }
	[[nodiscard]] const auto& getCustomLocalisations() const { return customLocalisations; }

  private:
	void addLocalisationsForAllGovernments(const std::pair<const std::string&, const std::string&>& tags,
		 const std::string& vic2Suffix,
		 const std::string& hoi4Suffix,
		 const Mappers::CountryNameMapper& countryNameMapper,
		 const std::set<std::string>& majorIdeologies,
		 const Vic2::Localisations& vic2Localisations,
		 const ArticleRules& articleRules);
	void addLocalisationsInAllLanguages(const std::string& destTag,
		 const std::string& vic2Suffix,
		 const std::string& hoi4Suffix,
		 const std::string& HoI4GovernmentIdeology,
		 const keyToLocalisationMap& namesInLanguage,
		 const ArticleRules& articleRules);
	languageToLocalisationsMap::iterator getExistingLocalisationsInLanguage(const std::string& language);
	static void addLocalisation(const std::string& newKey,
		 const std::string& language,
		 keyToLocalisationMap& existingLanguage,
		 const std::string& localisation,
		 const std::string& HoI4Suffix,
		 const ArticleRules& articleRules);
	bool addNeutralLocalisation(const std::pair<const std::string&, const std::string&>& tags,
		 const std::string& vic2Suffix,
		 const std::string& hoi4Suffix,
		 const Vic2::Localisations& vic2Localisations,
		 const ArticleRules& articleRules);

	bool attemptToUpdateMainCountryLocalisation(const std::string& HoI4Key,
		 const std::string& Vic2Key,
		 const Vic2::Localisations& vic2Localisations);
	bool attemptToUpdateMainCountryLocalisationChangingArticles(const std::string& HoI4Key,
		 const std::string& Vic2Key,
		 const Vic2::Localisations& vic2Localisations,
		 const ArticleRules& articleRules);

	void addStateLocalisationForLanguage(const State& hoi4State,
		 const Vic2::State& vic2State,
		 const std::string& language,
		 const std::string& name,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const Vic2::Localisations& vic2Localisations,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<std::string, std::string>& grammarMappings);
	void addVPLocalisationForLanguage(const State& state, const std::string& language, const std::string& name);
	std::map<stateNumber, std::string>& getExistingStateLocalisation(const std::string& language);
	keyToLocalisationMap& getExistingVPLocalisation(const std::string& language);
	void addLanguageToStateLocalisations(const std::string& language);
	void addLanguageToVPLocalisations(const std::string& language);
	void addNonenglishStateLocalisations();
	void addNonenglishVPLocalisations();
	void addDebugLocalisations(const std::pair<const int, State>& state,
		 const Vic2::Localisations& vic2Localisations,
		 const Mappers::ProvinceMapper& theProvinceMapper);

	static bool sourceStateHasOneProvince(const State& hoi4State, const Mappers::ProvinceMapper& theProvinceMapper);
	static bool destinationStateHasOneProvince(const State& hoi4State);
	static bool sourceStateHasAllButOneProvinceFromDefinition(const Vic2::State& sourceState,
		 const Vic2::StateDefinitions& theStateDefinitions);
	static bool stateHasAllDefinedProvincesAfterConversion(const State& state,
		 const Vic2::State& sourceState,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const Mappers::ProvinceMapper& theProvinceMapper);

	static std::string getLanguageCode(const std::string& language);
	void insertScriptedLocalisation(const std::string& localisationKey,
		 const std::string& replacementKey,
		 ScriptedLocalisation& scriptedLocalisation,
		 const std::set<std::string>& majorIdeologies) const;

	std::map<language, std::map<stateNumber, std::string>> stateLocalisations;
	languageToLocalisationsMap VPLocalisations;
	languageToLocalisationsMap countryLocalisations;
	languageToLocalisationsMap originalFocuses;
	languageToLocalisationsMap newFocuses;
	languageToLocalisationsMap ideaLocalisations;
	languageToLocalisationsMap genericIdeaLocalisations;
	languageToLocalisationsMap originalEventLocalisations;
	languageToLocalisationsMap newEventLocalisations;
	languageToLocalisationsMap politicalPartyLocalisations;
	languageToLocalisationsMap decisionLocalisations;
	languageToLocalisationsMap customLocalisations;
};


class Localisation::Importer
{
  public:
	std::unique_ptr<Localisation> generateLocalisations(const Configuration& theConfiguration);

  private:
	void importLocalisations(const Configuration& theConfiguration);
	void importFocusLocalisations(const std::string& filename);
	void importGenericIdeaLocalisations(const std::string& filename);
	void importEventLocalisations(const std::string& filename);
	static void importLocalisationFile(const std::string& filename, languageToLocalisationsMap& localisations);
	void prepareBlankLocalisations();

	std::map<language, std::map<stateNumber, std::string>> stateLocalisations;
	languageToLocalisationsMap VPLocalisations;
	languageToLocalisationsMap countryLocalisations;
	languageToLocalisationsMap originalFocuses;
	languageToLocalisationsMap newFocuses;
	languageToLocalisationsMap ideaLocalisations;
	languageToLocalisationsMap genericIdeaLocalisations;
	languageToLocalisationsMap originalEventLocalisations;
	languageToLocalisationsMap newEventLocalisations;
	languageToLocalisationsMap politicalPartyLocalisations;
	languageToLocalisationsMap decisionLocalisations;
	languageToLocalisationsMap customLocalisations;
};

} // namespace HoI4



#endif // HOI4_LOCALISATION_H