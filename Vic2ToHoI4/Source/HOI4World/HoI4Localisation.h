#ifndef HOI4LOCALISATION_H_
#define HOI4LOCALISATION_H_



#include "../V2World/State.h"
#include "ScriptedLocalisations/ScriptedLocalisations.h"
#include <array>
#include <iostream>
#include <map>
#include <optional>
#include <string>


class V2Localisations;

namespace Vic2
{
class StateDefinitions;
}

namespace HoI4
{
class State;
class States;
} // namespace HoI4

class governmentMapper;



typedef std::map<std::string, std::string> keyToLocalisationMap;					  // key -> localisation
typedef std::map<std::string, keyToLocalisationMap> languageToLocalisationsMap; // language -> (key -> localisation)

typedef std::string language;
typedef int stateNumber;



class HoI4Localisation
{
  public:
	HoI4Localisation(const HoI4Localisation&) = delete;
	HoI4Localisation(HoI4Localisation&&) = delete;
	HoI4Localisation& operator=(const HoI4Localisation&) = delete;
	HoI4Localisation& operator=(HoI4Localisation&&) = delete;
	~HoI4Localisation() = default;

	static void addStateLocalisation(const HoI4::State& hoi4State,
		 const Vic2::State& vic2State,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const V2Localisations& vic2Localisations)
	{
		getInstance()->AddStateLocalisation(hoi4State, vic2State, theStateDefinitions, vic2Localisations);
	}

	static void addStateLocalisations(const HoI4::States& states, const V2Localisations& vic2Localisations)
	{
		getInstance()->AddStateLocalisations(states, vic2Localisations);
	}

	static void createCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags,
		 const governmentMapper& governmentMap,
		 const V2Localisations& vic2Localisations)
	{
		getInstance()->CreateCountryLocalisations(tags, governmentMap, vic2Localisations);
	}

	static void updateMainCountryLocalisation(const std::string& HoI4Key,
		 const std::string& Vic2Tag,
		 const std::string& Vic2Government,
		 const V2Localisations& vic2Localisations)
	{
		getInstance()->UpdateMainCountryLocalisation(HoI4Key, Vic2Tag, Vic2Government, vic2Localisations);
	}

	static void addNonenglishCountryLocalisations() { getInstance()->AddNonenglishCountryLocalisations(); }

	static void copyFocusLocalisations(const std::string& oldKey, const std::string& newKey)
	{
		getInstance()->CopyFocusLocalisations(oldKey, newKey);
	}

	static void copyEventLocalisations(const std::string& oldKey, const std::string& newKey)
	{
		getInstance()->CopyEventLocalisations(oldKey, newKey);
	}

	static void addEventLocalisation(const std::string& event, const std::string& localisation)
	{
		getInstance()->AddEventLocalisation(event, localisation);
	}

	static void addEventLocalisationFromVic2(const std::string& Vic2Key,
		 const std::string& HoI4Key,
		 const V2Localisations& vic2Localisations)
	{
		getInstance()->AddEventLocalisationFromVic2(Vic2Key, HoI4Key, vic2Localisations);
	}

	static void addIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation)
	{
		getInstance()->AddIdeaLocalisation(idea, localisation);
	}

	static void addPoliticalPartyLocalisation(const std::string& Vic2Key,
		 const std::string& HoI4Key,
		 const V2Localisations& vic2Localisations)
	{
		getInstance()->AddPoliticalPartyLocalisation(Vic2Key, HoI4Key, vic2Localisations);
	}

	static void addDecisionLocalisation(const std::string& key, const std::optional<std::string>& localisation)
	{
		getInstance()->AddDecisionLocalisation(key, localisation);
	}

	static void generateCustomLocalisations(HoI4::ScriptedLocalisations& scriptedLocalisations,
		 const std::set<std::string>& majorIdeologies)
	{
		getInstance()->GenerateCustomLocalisations(scriptedLocalisations, majorIdeologies);
	}

	static void updateLocalisationText(const std::string& key, const std::string& oldText, const std::string& newText)
	{
		getInstance()->UpdateLocalisationText(key, oldText, newText);
	}

	[[nodiscard]] const auto& getStateLocalisations() const { return getInstance()->stateLocalisations; }
	[[nodiscard]] const auto& getVPLocalisations() const { return getInstance()->VPLocalisations; }
	[[nodiscard]] const auto& getCountryLocalisations() const { return getInstance()->countryLocalisations; }
	[[nodiscard]] const auto& getOriginalFocuses() const { return getInstance()->originalFocuses; }
	[[nodiscard]] const auto& getNewFocuses() const { return getInstance()->newFocuses; }
	[[nodiscard]] const auto& getIdeaLocalisations() const { return getInstance()->ideaLocalisations; }
	[[nodiscard]] const auto& getGenericIdeaLocalisations() const { return getInstance()->genericIdeaLocalisations; }
	[[nodiscard]] const auto& getOriginalEventLocalisations() const { return getInstance()->originalEventLocalisations; }
	[[nodiscard]] const auto& getNewEventLocalisations() const { return getInstance()->newEventLocalisations; }
	[[nodiscard]] const auto& getPoliticalPartyLocalisations() const
	{
		return getInstance()->politicalPartyLocalisations;
	}
	[[nodiscard]] const auto& getDecisionLocalisations() const { return getInstance()->decisionLocalisations; }
	[[nodiscard]] const auto& getCustomLocalisations() const { return getInstance()->customLocalisations; }

	static HoI4Localisation* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new HoI4Localisation();
		}
		return instance;
	}

  private:
	static HoI4Localisation* instance;

	HoI4Localisation() noexcept;
	void importLocalisations();
	void importFocusLocalisations(const std::string& filename);
	void importGenericIdeaLocalisations(const std::string& filename);
	void importEventLocalisations(const std::string& filename);
	static void importLocalisationFile(const std::string& filename, languageToLocalisationsMap& localisations);
	void prepareBlankLocalisations();

	void AddNonenglishCountryLocalisations();

	void CreateCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags,
		 const governmentMapper& governmentMap,
		 const V2Localisations& vic2Localisations);
	void addLocalisationsForAllGovernments(const std::pair<const std::string&, const std::string&>& tags,
		 const std::pair<const std::string&, const std::string&>& suffixes,
		 const governmentMapper& governmentMap,
		 const V2Localisations& vic2Localisations);
	void addLocalisationsInAllLanguages(const std::string& destTag,
		 const std::pair<const std::string&, const std::string&>& suffixes,
		 const std::string& HoI4GovernmentIdeology,
		 const keyToLocalisationMap& namesInLanguage);
	languageToLocalisationsMap::iterator getExistingLocalisationsInLanguage(const std::string& language);
	static void addLocalisation(const std::string& newKey,
		 keyToLocalisationMap& existingLanguage,
		 const std::string& localisation,
		 const std::string& HoI4Suffix);
	bool addNeutralLocalisation(const std::pair<const std::string&, const std::string&>& tags,
		 const std::pair<const std::string&, const std::string&>& suffixes,
		 const V2Localisations& vic2Localisations);

	void UpdateMainCountryLocalisation(const std::string& HoI4Key,
		 const std::string& Vic2Tag,
		 const std::string& Vic2Government,
		 const V2Localisations& vic2Localisations);
	bool attemptToUpdateMainCountryLocalisation(const std::string& HoI4Key,
		 const std::string& Vic2Key,
		 const V2Localisations& vic2Localisations);

	void CopyFocusLocalisations(const std::string& oldKey, const std::string& newKey);

	void CopyEventLocalisations(const std::string& oldKey, const std::string& newKey);

	void AddStateLocalisation(const HoI4::State& hoi4State,
		 const Vic2::State& vic2State,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const V2Localisations& vic2Localisations);
	void AddStateLocalisations(const HoI4::States& states, const V2Localisations& vic2Localisations);
	void addStateLocalisationForLanguage(const HoI4::State& hoi4State,
		 const Vic2::State& vic2State,
		 const std::pair<const std::string, std::string>& Vic2NameInLanguage,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const V2Localisations& vic2Localisations);
	void addVPLocalisationForLanguage(const HoI4::State& state,
		 const std::pair<const std::string, std::string>& Vic2NameInLanguage);
	std::map<stateNumber, std::string>& getExistingStateLocalisation(const std::string& language);
	keyToLocalisationMap& getExistingVPLocalisation(const std::string& language);
	void addLanguageToStateLocalisations(const std::string& language);
	void addLanguageToVPLocalisations(const std::string& language);
	void addNonenglishStateLocalisations();
	void addNonenglishVPLocalisations();
	void addDebugLocalisations(const std::pair<const int, HoI4::State>& state, const V2Localisations& vic2Localisations);

	static bool sourceStateHasOneProvince(const Vic2::State& sourceState);
	static bool sourceStateHasAllButOneProvinceFromDefinition(const Vic2::State& sourceState,
		 const Vic2::StateDefinitions& theStateDefinitions);
	static bool stateHasAllDefinedProvincesAfterConversion(const HoI4::State& state,
		 const Vic2::State& sourceState,
		 const Vic2::StateDefinitions& theStateDefinitions);

	void AddEventLocalisation(const std::string& event, const std::string& localisation);
	void AddEventLocalisationFromVic2(const std::string& Vic2Key,
		 const std::string& HoI4Key,
		 const V2Localisations& vic2Localisations);

	void AddIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation);

	void AddPoliticalPartyLocalisation(const std::string& Vic2Key,
		 const std::string& HoI4Key,
		 const V2Localisations& vic2Localisations);
	void AddDecisionLocalisation(const std::string& key, const std::optional<std::string>& localisation);

	void GenerateCustomLocalisations(HoI4::ScriptedLocalisations& scriptedLocalisations,
		 const std::set<std::string>& majorIdeologies);

	void UpdateLocalisationText(const std::string& key, const std::string& oldText, const std::string& newText);

	static std::string getLanguageCode(const std::string& language);
	void insertScriptedLocalisation(const std::string& localisationKey,
		 const std::string& replacementKey,
		 HoI4::ScriptedLocalisation& scriptedLocalisation,
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



#endif // HOI4LOCALISATION_H_