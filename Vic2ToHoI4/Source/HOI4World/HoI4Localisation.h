/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#ifndef HOI4LOCALISATION_H_
#define HOI4LOCALISATION_H_



#include "../V2World/State.h"
#include <array>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>



class HoI4States;

namespace HoI4
{
class State;
}
class governmentMapper;



typedef std::map<std::string, std::string> keyToLocalisationMap; // key -> localisation
typedef std::map<std::string, keyToLocalisationMap> languageToLocalisationsMap; // language -> (key -> localisation)

typedef std::string language;
typedef int stateNumber;




class HoI4Localisation
{
	public:
		static void addStateLocalisations(const HoI4States* states)
		{
			getInstance()->AddStateLocalisations(states);
		}

		static void createCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags, const governmentMapper& governmentMap)
		{
			getInstance()->CreateCountryLocalisations(tags, governmentMap);
		}

		static void updateMainCountryLocalisation(const std::string& HoI4Key, const std::string& Vic2Tag, const std::string& Vic2Government)
		{
			getInstance()->UpdateMainCountryLocalisation(HoI4Key, Vic2Tag, Vic2Government);
		}

		static void addNonenglishCountryLocalisations()
		{
			getInstance()->AddNonenglishCountryLocalisations();
		}

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

		static void addEventLocalisationFromVic2(const std::string& Vic2Key, const std::string& HoI4Key)
		{
			getInstance()->AddEventLocalisationFromVic2(Vic2Key, HoI4Key);
		}

		static void addIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation)
		{
			getInstance()->AddIdeaLocalisation(idea, localisation);
		}

		static void addPoliticalPartyLocalisation(const std::string& Vic2Key, const std::string& HoI4Key)
		{
			getInstance()->AddPoliticalPartyLocalisation(Vic2Key, HoI4Key);
		}

		static void updateLocalisationWithCountry(const std::string& key, const std::string& oldText, const std::string& newTextLocalisationKey)
		{
			getInstance()->UpdateLocalisationWithCountry(key, oldText, newTextLocalisationKey);
		}

		static void output()
		{
			getInstance()->Output();
		}

	private:
		static HoI4Localisation* instance;
		static HoI4Localisation* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new HoI4Localisation();
			}
			return instance;
		}
		HoI4Localisation() noexcept;
		void importLocalisations();
		void importFocusLocalisations(const std::string& filename);
		void importGenericIdeaLocalisations(const std::string& filename);
		void importEventLocalisations(const std::string& filename);
		void importLocalisationFile(const std::string& filename, languageToLocalisationsMap& localisations);
		void prepareIdeaLocalisations();

		HoI4Localisation(const HoI4Localisation&) = delete;
		HoI4Localisation& operator=(const HoI4Localisation&) = delete;

		void AddNonenglishCountryLocalisations();

		void CreateCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags, const governmentMapper& governmentMap);
		void addLocalisationsForAllGovernments(const std::pair<const std::string&, const std::string&>& tags, const std::pair<const std::string&, const std::string&>& suffixes, const governmentMapper& governmentMap);
		void addLocalisationsInAllLanguages(const std::string& destTag, const std::pair<const std::string&, const std::string&>& suffixes, const std::string& HoI4GovernmentIdeology, const keyToLocalisationMap& namesInLanguage);
		languageToLocalisationsMap::iterator getExistingLocalisationsInLanguage(const std::string& language);
		void addLocalisation(
			const std::string& newKey,
			keyToLocalisationMap& existingLanguage,
			const std::string& localisation,
			const std::string& HoI4Suffix
		);
		bool addNeutralLocalisation(const std::pair<const std::string&, const std::string&>& tags, const std::pair<const std::string&, const std::string&>& suffixes);

		void UpdateMainCountryLocalisation(const std::string& HoI4Key, const std::string& Vic2Tag, const std::string& Vic2Government);
		bool attemptToUpdateMainCountryLocalisation(const std::string& HoI4Key, const std::string& Vic2Key);

		void CopyFocusLocalisations(const std::string& oldKey, const std::string& newKey);

		void CopyEventLocalisations(const std::string& oldKey, const std::string& newKey);

		void AddStateLocalisations(const HoI4States* states);
		void addStateLocalisationForLanguage(
			const HoI4::State& state,
			const std::pair<const std::string, std::string>& Vic2NameInLanguage
		);
		void addVPLocalisationForLanguage(const HoI4::State& state, const std::pair<const std::string, std::string>& Vic2NameInLanguage);
		std::map<stateNumber, std::string>& getExistingStateLocalisation(const std::string& language);
		keyToLocalisationMap& getExistingVPLocalisation(const std::string& language);
		void addLanguageToStateLocalisations(const std::string& language);
		void addLanguageToVPLocalisations(const std::string& language);
		void addNonenglishStateLocalisations();
		void addNonenglishVPLocalisations();
		void addDebugLocalisations(const std::pair<const int, HoI4::State>& state);

		bool sourceStateHasOneProvince(const Vic2::State& sourceState);
		bool sourceStateHasAllButOneProvinceFromDefinition(const Vic2::State& sourceState);
		bool stateHasAllDefinedProvincesAfterConversion(const HoI4::State& state);

		void AddEventLocalisation(const std::string& event, const std::string& localisation);
		void AddEventLocalisationFromVic2(const std::string& Vic2Key, const std::string& HoI4Key);

		void AddIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation);

		void AddPoliticalPartyLocalisation(const std::string& Vic2Key, const std::string& HoI4Key);

		void UpdateLocalisationWithCountry(const std::string& key, const std::string& oldText, const std::string& newTextLocalisationKey);

		void Output() const;
		void outputCountries(const std::string& localisationPath) const;
		void outputFocuses(const std::string& localisationPath) const;
		void outputStateLocalisations(const std::string& localisationPath) const;
		void outputVPLocalisations(const std::string& localisationPath) const;
		void outputIdeaLocalisations(const std::string& localisationPath) const;
		void outputEventLocalisations(const std::string& localisationPath) const;
		void outputPoliticalPartyLocalisations(const std::string& localisationPath) const;
		void outputLocalisations(const std::string& filenameStart, const languageToLocalisationsMap& localisations) const;

		std::map<language, std::map< stateNumber, std::string>> stateLocalisations;
		languageToLocalisationsMap VPLocalisations;
		languageToLocalisationsMap countryLocalisations;
		languageToLocalisationsMap originalFocuses;
		languageToLocalisationsMap newFocuses;
		languageToLocalisationsMap ideaLocalisations;
		languageToLocalisationsMap genericIdeaLocalisations;
		languageToLocalisationsMap originalEventLocalisations;
		languageToLocalisationsMap newEventLocalisations;
		languageToLocalisationsMap politicalPartyLocalisations;
};



#endif // HOI4LOCALISATION_H_