#include "src/HOI4World/HoI4Localisation.h"
#include "external/common_items/ConvenientParser.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/Localisations/AllReplacementRules.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/Mappers/Government/GovernmentMapper.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/Localisations/Vic2Localisations.h"
#include "src/V2World/States/State.h"
#include "src/V2World/States/StateDefinitions.h"
#include <algorithm>
#include <fstream>
#include <ranges>


// watch for getTextInEachLanguage



namespace
{


const std::set<std::string> supported_languages = {"braz_por",
	 "czech",
	 "dutch",
	 "english",
	 "finnish",
	 "french",
	 "german",
	 "hungarian",
	 "italian",
	 "japanese",
	 "polish",
	 "russian",
	 "spanish",
	 "swedish"};

void importLocalisationFile(const std::filesystem::path& filename, HoI4::languageToLocalisationsMap& localisations)
{
	HoI4::keyToLocalisationMap newLocalisations;

	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open " + filename.string());
	}
	commonItems::absorbBOM(file);

	std::string language;
	while (!file.eof())
	{
		std::string line;
		getline(file, line);
		if (line.starts_with("l_"))
		{
			language = line.substr(2, line.length() - 3);
			continue;
		}

		const auto colon = line.find(':');
		if (colon == std::string::npos)
		{
			continue;
		}
		auto key = line.substr(1, colon - 1);

		line = line.substr(colon, line.length());
		const auto quote = line.find('\"');
		const auto value = line.substr(quote + 1, line.length() - quote - 2);

		newLocalisations[key] = value;
	}

	auto [iterator, success] = localisations.emplace(language, newLocalisations);
	if (!success)
	{
		for (const auto& [key, new_localization]: newLocalisations)
		{
			iterator->second[key] = new_localization;
		}
	}

	file.close();
}


void addLocalisation(const std::string& newKey,
	 const std::string& language,
	 HoI4::keyToLocalisationMap& existingKeyToLocalisationMapping,
	 const std::string& localisation,
	 const std::string& HoI4Suffix,
	 const HoI4::ArticleRules& articleRules)
{
	if (const auto existingLocalisation = existingKeyToLocalisationMapping.find(newKey);
		 existingLocalisation == existingKeyToLocalisationMapping.end())
	{
		existingKeyToLocalisationMapping.insert(
			 std::make_pair(newKey, articleRules.updateArticles(language, localisation)));
		if (!HoI4Suffix.empty())
		{
			existingKeyToLocalisationMapping.insert(std::make_pair(newKey + HoI4Suffix, localisation));
		}
	}
	else
	{
		existingKeyToLocalisationMapping[newKey] = articleRules.updateArticles(language, localisation);
		if (!HoI4Suffix.empty())
		{
			existingKeyToLocalisationMapping[newKey + HoI4Suffix] = localisation;
		}
	}
}


bool destinationStateHasOneProvince(const HoI4::State& hoi4State)
{
	return hoi4State.getProvinces().size() == 1;
}


bool sourceStateHasAllButOneProvinceFromDefinition(const Vic2::State& sourceState,
	 const int firstSourceProvince,
	 const Vic2::StateDefinitions& theStateDefinitions)
{
	int missingProvinces = 0;
	for (const auto definitionProvince: theStateDefinitions.getAllProvinces(firstSourceProvince))
	{
		if (!sourceState.getProvinceNumbers().contains(definitionProvince))
		{
			++missingProvinces;
		}
	}
	return missingProvinces == 1;
}


bool sourceProvincesHaveAllButOneProvinceFromDefinition(const std::set<int>& sourceProvinceNumbers,
	 const Vic2::StateDefinitions& theStateDefinitions)
{
	return sourceProvinceNumbers.size() ==
			 theStateDefinitions.getAllProvinces(*sourceProvinceNumbers.begin()).size() - 1;
}


bool stateHasAllDefinedProvincesAfterConversion(const HoI4::State& state,
	 const std::set<int>& sourceProvinceNumbers,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const Mappers::ProvinceMapper& theProvinceMapper)
{
	std::set<int> stateDefinitionDefinitionProvinces;

	for (const auto sourceProvince: theStateDefinitions.getAllProvinces(*sourceProvinceNumbers.begin()))
	{
		for (auto HoI4Province: theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince))
		{
			stateDefinitionDefinitionProvinces.insert(HoI4Province);
		}
	}

	return std::ranges::all_of(stateDefinitionDefinitionProvinces, [state](int definedProvince) {
		return state.getProvinces().contains(definedProvince);
	});
}


std::optional<Vic2::LanguageToLocalisationMap> getConfigurableDominionNames(
	 const Vic2::Localisations& vic2Localisations,
	 const std::string& region,
	 const std::string& cultureGroup,
	 const std::string& culture,
	 const std::string& ideology)
{
	if (const auto localisations =
			  vic2Localisations.getTextInEachLanguage("dom_" + cultureGroup + "_" + ideology + "_" + region);
		 !localisations.empty())
	{
		return localisations;
	}

	if (const auto localisations = vic2Localisations.getTextInEachLanguage("dom_" + cultureGroup + "_" + region);
		 !localisations.empty())
	{
		return localisations;
	}

	if (const auto localisations =
			  vic2Localisations.getTextInEachLanguage("dom_" + culture + "_" + ideology + "_" + region);
		 !localisations.empty())
	{
		return localisations;
	}

	if (const auto localisations = vic2Localisations.getTextInEachLanguage("dom_" + culture + "_" + region);
		 !localisations.empty())
	{
		return localisations;
	}

	if (const auto localisations = vic2Localisations.getTextInEachLanguage("dom_" + ideology + "_" + region);
		 !localisations.empty())
	{
		return localisations;
	}

	if (const auto localisations = vic2Localisations.getTextInEachLanguage("dom_" + region); !localisations.empty())
	{
		return localisations;
	}

	return std::nullopt;
}


constexpr std::string_view overlord_string = "$OVERLORD$";
constexpr std::string_view overlord_adjective_string = "$OVERLORD_ADJ$";
Vic2::LanguageToLocalisationMap configureDominionNames(const Vic2::LanguageToLocalisationMap& configurableDominionNames,
	 const Vic2::LanguageToLocalisationMap& ownerNames,
	 const Vic2::LanguageToLocalisationMap& ownerAdjectives)
{
	Vic2::LanguageToLocalisationMap localisationsForGovernment;
	for (auto& [language, localisation]: configurableDominionNames)
	{
		std::string newLocalisation = localisation;
		if (const auto ownerName = ownerNames.find(language); ownerName != ownerNames.end())
		{
			while (newLocalisation.find(overlord_string) != std::string::npos)
			{
				newLocalisation.replace(newLocalisation.find(overlord_string), overlord_string.length(), ownerName->second);
			}
		}
		if (const auto ownerAdjective = ownerAdjectives.find(language); ownerAdjective != ownerAdjectives.end())
		{
			while (newLocalisation.find(overlord_adjective_string) != std::string::npos)
			{
				newLocalisation.replace(newLocalisation.find(overlord_adjective_string),
					 overlord_adjective_string.length(),
					 ownerAdjective->second);
			}
		}

		localisationsForGovernment.emplace(language, newLocalisation);
	}

	return localisationsForGovernment;
}


bool stateHasCapital(const std::set<int>& source_province_numbers, const Vic2::StateDefinitions& state_definitions)
{
	const auto state_id = state_definitions.getStateID(*source_province_numbers.begin());
	if (!state_id.has_value())
	{
		return false;
	}

	const auto possible_capital = state_definitions.getCapitalProvince(state_id.value());
	if (!possible_capital.has_value())
	{
		return false;
	}

	return source_province_numbers.contains(possible_capital.value());
}


std::string getLanguageCode(const std::string& language)
{
	if (language == "braz_por")
	{
		return "PT";
	}
	if (language == "french")
	{
		return "FR";
	}
	if (language == "italian")
	{
		return "IT";
	}
	if (language == "spanish")
	{
		return "ES";
	}

	return "";
}


void insertScriptedLocalisation(const std::string& localisationKey,
	 const std::string& replacementKey,
	 HoI4::ScriptedLocalisation& scriptedLocalisation,
	 const std::set<std::string>& majorIdeologies)
{
	const std::regex extractRegex("([A-Z0-9]{3})_([a-z]+)_ADJ");

	std::smatch match;
	std::regex_match(localisationKey, match, extractRegex);
	const std::string tag = match[1];
	const std::string ideology = match[2];
	if (!majorIdeologies.contains(ideology))
	{
		return;
	}

	std::string text;
	text += "= {\n";
	text += "\t\ttrigger = {\n";
	text += "\t\t\tOR = { tag = " + tag + " original_tag = " + tag + " }\n";
	text += "\t\t\thas_government = " + ideology + "\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = " + localisationKey + replacementKey + "\n";
	text += "\t}";
	scriptedLocalisation.addText(text);
}

} // namespace


std::unique_ptr<HoI4::Localisation> HoI4::Localisation::Importer::generateLocalisations(std::filesystem::path hoi4_directory)
{
	importLocalisations(hoi4_directory);
	prepareBlankLocalisations();

	return std::make_unique<Localisation>(stateLocalisations,
		 VPLocalisations,
		 countryLocalisations,
		 originalFocuses,
		 newFocuses,
		 ideaLocalisations,
		 genericIdeaLocalisations,
		 originalEventLocalisations,
		 newEventLocalisations,
		 politicalPartyLocalisations,
		 decisionLocalisations,
		 customLocalisations,
		 characterLocalisations_);
}


void HoI4::Localisation::Importer::importLocalisations(const std::filesystem::path& hoi4_directory)
{
	for (const auto& subdirectory: commonItems::GetAllSubfolders(hoi4_directory / "localisation"))
	{
		for (const auto& fileName: commonItems::GetAllFilesInFolder(hoi4_directory / "localisation" / subdirectory))
		{
			const std::filesystem::path full_path = hoi4_directory / "localisation" / subdirectory / fileName;
			if (fileName.string().starts_with("focus"))
			{
				importFocusLocalisations(full_path);
			}
			else if (fileName.string().starts_with("ideas"))
			{
				importGenericIdeaLocalisations(full_path);
			}
			else if (fileName.string().starts_with("events"))
			{
				importEventLocalisations(full_path);
			}
		}
	}

	for (const auto& subdirectory: commonItems::GetAllSubfolders(std::filesystem::path("blankmod/localisation")))
	{
		for (const auto& fileName: commonItems::GetAllFilesInFolder("blankmod/localisation" / subdirectory))
		{
			const std::filesystem::path full_path = "blankmod/localisation" / subdirectory / fileName;
			if (fileName.string().starts_with("focus"))
			{
				importFocusLocalisations(full_path);
			}
			else if (fileName.string().starts_with("ideas"))
			{
				importGenericIdeaLocalisations(full_path);
			}
			else if (fileName.string().starts_with("events"))
			{
				importEventLocalisations(full_path);
			}
		}
	}
}


void HoI4::Localisation::Importer::importFocusLocalisations(const std::filesystem::path& filename)
{
	importLocalisationFile(filename, originalFocuses);
}


void HoI4::Localisation::Importer::importGenericIdeaLocalisations(const std::filesystem::path& filename)
{
	importLocalisationFile(filename, genericIdeaLocalisations);
}


void HoI4::Localisation::Importer::importEventLocalisations(const std::filesystem::path& filename)
{
	importLocalisationFile(filename, originalEventLocalisations);
}


void HoI4::Localisation::Importer::prepareBlankLocalisations()
{
	for (const auto& language: genericIdeaLocalisations | std::views::keys)
	{
		keyToLocalisationMap newLocalisationsMap;
		ideaLocalisations.insert(make_pair(language, newLocalisationsMap));
		decisionLocalisations.insert(make_pair(language, newLocalisationsMap));
	}
}


void HoI4::Localisation::createCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags,
	 const Mappers::CountryNameMapper& countryNameMapper,
	 const std::set<std::string>& majorIdeologies,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	addLocalisationsForAllGovernments(tags,
		 "",
		 "_DEF",
		 countryNameMapper,
		 majorIdeologies,
		 vic2Localisations,
		 articleRules);
	addLocalisationsForAllGovernments(tags,
		 "_ADJ",
		 "",
		 countryNameMapper,
		 majorIdeologies,
		 vic2Localisations,
		 articleRules);

	if (!addNeutralLocalisation(tags, "", "_DEF", vic2Localisations, articleRules))
	{
		Log(LogLevel::Warning) << "Could not find plain localisation for " << tags.first;
	}
	if (!addNeutralLocalisation(tags, "_ADJ", "", vic2Localisations, articleRules))
	{
		Log(LogLevel::Warning) << "Could not find plain adjective localisation for " << tags.first;
	}
}


void HoI4::Localisation::addLocalisationsForAllGovernments(
	 const std::pair<const std::string&, const std::string&>& tags,
	 const std::string& vic2Suffix,
	 const std::string& hoi4Suffix,
	 const Mappers::CountryNameMapper& countryNameMapper,
	 const std::set<std::string>& majorIdeologies,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	for (const auto& ideology: majorIdeologies)
	{
		const auto vic2Government = countryNameMapper.getVic2Government(ideology, tags.first);
		if (!vic2Government)
		{
			continue;
		}

		auto localisationForGovernment =
			 vic2Localisations.getTextInEachLanguage(tags.first + "_" + *vic2Government + vic2Suffix);
		addLocalisationsInAllLanguages(tags.second,
			 vic2Suffix,
			 hoi4Suffix,
			 ideology,
			 localisationForGovernment,
			 articleRules);
		if (localisationForGovernment.empty())
		{
			addLocalisationsInAllLanguages(tags.second,
				 vic2Suffix,
				 hoi4Suffix,
				 ideology,
				 vic2Localisations.getTextInEachLanguage(tags.first + vic2Suffix),
				 articleRules);
		}
	}
}


void HoI4::Localisation::addLocalisationsInAllLanguages(const std::string& destTag,
	 const std::string& vic2Suffix,
	 const std::string& hoi4Suffix,
	 const std::string& HoI4GovernmentIdeology,
	 const keyToLocalisationMap& namesInLanguage,
	 const ArticleRules& articleRules)
{
	for (const auto& [key, localisation]: namesInLanguage)
	{
		const auto existingLanguageToLocalisationMapping = getExistingLocalisationsInLanguage(key);

		std::string newKey = destTag;
		if (!HoI4GovernmentIdeology.empty())
		{
			newKey += "_" + HoI4GovernmentIdeology;
		}
		newKey += vic2Suffix;
		addLocalisation(newKey,
			 key,
			 existingLanguageToLocalisationMapping->second,
			 localisation,
			 hoi4Suffix,
			 articleRules);
	}
}


bool HoI4::Localisation::addNeutralLocalisation(const std::pair<const std::string&, const std::string&>& tags,
	 const std::string& vic2Suffix,
	 const std::string& hoi4Suffix,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	if (const auto plainLocalisation = vic2Localisations.getTextInEachLanguage(tags.first + vic2Suffix);
		 !plainLocalisation.empty())
	{
		for (const auto& [name, language]: plainLocalisation)
		{
			auto& existingLocalisation = getExistingLocalisationsInLanguage(name)->second;

			auto newKey = tags.second + "_neutrality" + vic2Suffix;
			addLocalisation(newKey, name, existingLocalisation, language, hoi4Suffix, articleRules);

			// For collaboration governments using non-ideological keys
			newKey = tags.second + vic2Suffix;
			addLocalisation(newKey, name, existingLocalisation, language, hoi4Suffix, articleRules);
		}
		return true;
	}

	return false;
}


HoI4::languageToLocalisationsMap::iterator HoI4::Localisation::getExistingLocalisationsInLanguage(
	 const std::string& language)
{
	auto existingLanguage = countryLocalisations.find(language);
	if (existingLanguage == countryLocalisations.end())
	{
		const keyToLocalisationMap newLocalisations;
		countryLocalisations[language] = newLocalisations;
		existingLanguage = countryLocalisations.find(language);
	}

	return existingLanguage;
}


void HoI4::Localisation::createGeneratedDominionLocalisations(const std::string& tag,
	 const Country& dominion,
	 const std::string& ownerOldTag,
	 const Vic2::Localisations& vic2Localisations,
	 const Mappers::CountryNameMapper& countryNameMapper,
	 const std::set<std::string>& majorIdeologies,
	 const ArticleRules& articleRules)
{
	const auto& region = dominion.getRegion();
	std::set<std::string> localisationIdeologies = majorIdeologies;
	localisationIdeologies.insert("neutrality");
	localisationIdeologies.insert("");

	for (const auto& ideology: localisationIdeologies)
	{
		const auto vic2Government = countryNameMapper.getVic2Government(ideology, ownerOldTag);
		if (!vic2Government)
		{
			continue;
		}

		auto ownerNames = vic2Localisations.getTextInEachLanguage(ownerOldTag + "_" + *vic2Government);
		if (ownerNames.empty())
		{
			ownerNames = vic2Localisations.getTextInEachLanguage(ownerOldTag);
		}
		auto ownerAdjectives = vic2Localisations.getTextInEachLanguage(ownerOldTag + "_" + *vic2Government + "_ADJ");
		if (ownerAdjectives.empty())
		{
			ownerAdjectives = vic2Localisations.getTextInEachLanguage(ownerOldTag + "_ADJ");
		}

		Vic2::LanguageToLocalisationMap localisationsForGovernment;
		if (auto possibleConfigurableDominionNames = getConfigurableDominionNames(vic2Localisations,
				  region,
				  dominion.getPrimaryCultureGroup(),
				  dominion.getPrimaryCulture(),
				  ideology);
			 possibleConfigurableDominionNames)
		{
			localisationsForGovernment =
				 configureDominionNames(*possibleConfigurableDominionNames, ownerNames, ownerAdjectives);
		}
		else
		{
			for (const auto& [language, localisation]: ownerAdjectives)
			{
				std::string newLocalisation = localisation;
				if (const auto& secondPart = vic2Localisations.getTextInLanguage(region, language); secondPart)
				{
					newLocalisation += " " + *secondPart;
				}
				localisationsForGovernment.emplace(language, newLocalisation);
			}
		}

		addLocalisationsInAllLanguages(tag, "", "_DEF", ideology, localisationsForGovernment, articleRules);
		if (localisationsForGovernment.empty())
		{
			addLocalisationsInAllLanguages(tag,
				 "",
				 "_DEF",
				 ideology,
				 vic2Localisations.getTextInEachLanguage(region),
				 articleRules);
		}

		addLocalisationsInAllLanguages(tag,
			 "_ADJ",
			 "",
			 ideology,
			 vic2Localisations.getTextInEachLanguage("dom_" + region + "_ADJ"),
			 articleRules);
	}
}


void HoI4::Localisation::createUnrecognizedNationLocalisations(const std::string& tag,
	 const Country& nation,
	 const Vic2::Localisations& vic2Localisations,
	 const Mappers::CountryNameMapper& countryNameMapper,
	 const std::set<std::string>& majorIdeologies,
	 const ArticleRules& articleRules)
{
	const auto& region = nation.getRegion();

	const auto unrecognizedNameLocalisations = vic2Localisations.getTextInEachLanguage("unrecognized_name");
	const auto unrecognizedAdjectiveLocalisations = vic2Localisations.getTextInEachLanguage("unrecognized_adjective");
	std::set<std::string> localisationIdeologies = majorIdeologies;
	localisationIdeologies.insert("");

	for (const auto& ideology: localisationIdeologies)
	{
		Vic2::LanguageToLocalisationMap localisationsForGovernment;
		// if there is a pre-set localisation of the form 'unrecognized_<region>', use it
		if (const auto localisations = vic2Localisations.getTextInEachLanguage("unrecognized_" + region);
			 !localisations.empty())
		{
			localisationsForGovernment =
				 configureDominionNames(localisations, unrecognizedNameLocalisations, unrecognizedAdjectiveLocalisations);
		}
		// otherwise do 'Unrecognized $Region$'
		else
		{
			for (const auto& [language, localisation]: unrecognizedAdjectiveLocalisations)
			{
				std::string newLocalisation = localisation;
				if (const auto& secondPart = vic2Localisations.getTextInLanguage(region, language); secondPart)
				{
					newLocalisation += " " + *secondPart;
				}
				localisationsForGovernment.emplace(language, newLocalisation);
			}
		}

		addLocalisationsInAllLanguages(tag, "", "_DEF", ideology, localisationsForGovernment, articleRules);
		if (localisationsForGovernment.empty())
		{
			addLocalisationsInAllLanguages(tag,
				 "",
				 "_DEF",
				 ideology,
				 vic2Localisations.getTextInEachLanguage(region),
				 articleRules);
		}

		addLocalisationsInAllLanguages(tag,
			 "_ADJ",
			 "",
			 ideology,
			 vic2Localisations.getTextInEachLanguage(region + "_ADJ"),
			 articleRules);
	}
}


void HoI4::Localisation::updateMainCountryLocalisation(const std::string& HoI4Key,
	 const std::string& Vic2Tag,
	 const std::string& Vic2Government,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	if (!attemptToUpdateMainCountryLocalisationChangingArticles(HoI4Key,
			  Vic2Tag + "_" + Vic2Government,
			  vic2Localisations,
			  articleRules))
	{
		attemptToUpdateMainCountryLocalisationChangingArticles(HoI4Key, Vic2Tag, vic2Localisations, articleRules);
	}
	if (!attemptToUpdateMainCountryLocalisation(HoI4Key + "_DEF", Vic2Tag + "_" + Vic2Government, vic2Localisations))
	{
		attemptToUpdateMainCountryLocalisation(HoI4Key + "_DEF", Vic2Tag, vic2Localisations);
	}
	if (!attemptToUpdateMainCountryLocalisation(HoI4Key + "_ADJ",
			  Vic2Tag + "_" + Vic2Government + "_ADJ",
			  vic2Localisations))
	{
		attemptToUpdateMainCountryLocalisation(HoI4Key + "_ADJ", Vic2Tag + "_ADJ", vic2Localisations);
	}
}


bool HoI4::Localisation::attemptToUpdateMainCountryLocalisation(const std::string& HoI4Key,
	 const std::string& Vic2Key,
	 const Vic2::Localisations& vic2Localisations)
{
	auto Vic2Text = vic2Localisations.getTextInEachLanguage(Vic2Key);
	if (!Vic2Text.empty())
	{
		return false;
	}

	for (const auto& [language, text]: Vic2Text)
	{
		const auto localisations = getExistingLocalisationsInLanguage(language);
		if (auto localisation = localisations->second.find(HoI4Key); localisation != localisations->second.end())
		{
			localisation->second = text;
		}
	}

	return true;
}


bool HoI4::Localisation::attemptToUpdateMainCountryLocalisationChangingArticles(const std::string& HoI4Key,
	 const std::string& Vic2Key,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	const auto Vic2Text = vic2Localisations.getTextInEachLanguage(Vic2Key);
	if (Vic2Text.empty())
	{
		return false;
	}

	for (const auto& [language, text]: Vic2Text)
	{
		const auto localisations = getExistingLocalisationsInLanguage(language);
		if (auto localisation = localisations->second.find(HoI4Key); localisation != localisations->second.end())
		{
			localisation->second = articleRules.updateArticles(language, text);
		}
	}

	return true;
}


void HoI4::Localisation::addNonenglishCountryLocalisations()
{
	const auto englishLocalisations = countryLocalisations.find("english");
	countryLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	countryLocalisations.insert(make_pair("polish", englishLocalisations->second));
	countryLocalisations.insert(make_pair("russian", englishLocalisations->second));
	countryLocalisations.insert(make_pair("japanese", englishLocalisations->second));
}


void HoI4::Localisation::copyFocusLocalisations(const std::string& oldKey, const std::string& newKey, bool debug)
{
	std::set<std::string> handled_languages;
	for (const auto& [language, localisations]: originalFocuses)
	{
		auto newLanguage = newFocuses.find(language);
		if (newLanguage == newFocuses.end())
		{
			keyToLocalisationMap newLocalisations;
			newFocuses.insert(make_pair(language, newLocalisations));
			newLanguage = newFocuses.find(language);
		}

		if (auto oldLocalisation = localisations.find(oldKey); oldLocalisation != localisations.end())
		{
			newLanguage->second[newKey] = oldLocalisation->second;
			handled_languages.insert(language);
		}
		else if (debug)
		{
			Log(LogLevel::Warning) << "Could not find original localisation for " << oldKey << " in " << language;
		}

		if (auto oldLocalisationDescription = localisations.find(oldKey + "_desc");
			 oldLocalisationDescription != localisations.end())
		{
			newLanguage->second[newKey + "_desc"] = oldLocalisationDescription->second;
		}
	}

	for (const auto& language: supported_languages)
	{
		if (handled_languages.contains(language))
		{
			continue;
		}

		const auto english_localisations = newFocuses.find("english");
		if (english_localisations == newFocuses.end())
		{
			break;
		}

		const auto english_localisation = english_localisations->second.find(newKey);
		if (english_localisation == english_localisations->second.end())
		{
			continue;
		}

		auto unhandled_language = newFocuses.find(language);
		if (unhandled_language == newFocuses.end())
		{
			keyToLocalisationMap new_localisations;
			newFocuses.insert(make_pair(language, new_localisations));
			unhandled_language = newFocuses.find(language);
		}
		unhandled_language->second[newKey] = english_localisation->second;

		const auto english_description = english_localisations->second.find(newKey + "_desc");
		if (english_description == english_localisations->second.end())
		{
			continue;
		}
		unhandled_language->second[newKey + "_desc"] = english_description->second;
	}
}


void HoI4::Localisation::copyEventLocalisations(const std::string& oldKey, const std::string& newKey, bool debug)
{
	std::set<std::string> handled_languages;
	for (const auto& [language, localisations]: originalEventLocalisations)
	{
		auto newLanguage = newEventLocalisations.find(language);
		if (newLanguage == newEventLocalisations.end())
		{
			keyToLocalisationMap newLocalisations;
			newEventLocalisations.insert(make_pair(language, newLocalisations));
			newLanguage = newEventLocalisations.find(language);
		}

		if (const auto& oldLocalisation = localisations.find(oldKey); oldLocalisation != localisations.end())
		{
			newLanguage->second[newKey] = oldLocalisation->second;
			handled_languages.insert(language);
		}
		else if (debug)
		{
			Log(LogLevel::Warning) << "Could not find original localisation for " << oldKey << " in " << language;
		}
	}

	for (const auto& language: supported_languages)
	{
		if (handled_languages.contains(language))
		{
			continue;
		}

		const auto english_localisations = newEventLocalisations.find("english");
		if (english_localisations == newEventLocalisations.end())
		{
			break;
		}

		const auto english_localisation = english_localisations->second.find(newKey);
		if (english_localisation == english_localisations->second.end())
		{
			continue;
		}

		auto unhandled_language = newEventLocalisations.find(language);
		if (unhandled_language == newEventLocalisations.end())
		{
			keyToLocalisationMap new_localisations;
			newEventLocalisations.insert(make_pair(language, new_localisations));
			unhandled_language = newEventLocalisations.find(language);
		}
		unhandled_language->second[newKey] = english_localisation->second;
	}
}


void HoI4::Localisation::addStateLocalisation(const State& hoi4State,
	 const Vic2::State& vic2State,
	 const std::set<int>& sourceProvinceNumbers,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const Vic2::Localisations& vic2Localisations,
	 const Mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<std::string, std::string>& grammarMappings)
{
	std::map<std::string, std::string> localisedNames;

	// Single province states get the Vic2 province name
	// This is either one province in HoI4 or one province in Vic2
	if (destinationStateHasOneProvince(hoi4State) || sourceProvinceNumbers.size() == 1)
	{
		const auto hoi4Province = *hoi4State.getProvinces().begin();
		if (const auto possibleVic2Provinces = theProvinceMapper.getHoI4ToVic2ProvinceMapping(hoi4Province);
			 !possibleVic2Provinces.empty())
		{
			const auto theProvince = possibleVic2Provinces[0];
			const auto provinceNameInLanguages =
				 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string(theProvince));
			if (provinceNameInLanguages.empty())
			{
				Log(LogLevel::Warning) << "Could not find localization for Vic2 province " << theProvince;
			}
			for (const auto& [language, provinceName]: provinceNameInLanguages)
			{
				localisedNames[language] = provinceName;
			}
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find localization for HoI4 province " << hoi4Province;
		}
	}

	// Complete states get the Vic2 state name
	else if (stateHasAllDefinedProvincesAfterConversion(hoi4State,
					 sourceProvinceNumbers,
					 theStateDefinitions,
					 theProvinceMapper))
	{
		for (const auto& [language, name]: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
		{
			localisedNames[language] = name;
		}
	}

	// States with only one missing province get the Vic2 state name
	else if (sourceStateHasAllButOneProvinceFromDefinition(vic2State,
					 *sourceProvinceNumbers.begin(),
					 theStateDefinitions) ||
				sourceProvincesHaveAllButOneProvinceFromDefinition(sourceProvinceNumbers, theStateDefinitions))
	{
		for (const auto& [language, name]: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
		{
			localisedNames[language] = name;
		}
	}

	// unowned states get the Vic2 state name
	else if (vic2State.getOwner().empty())
	{
		for (const auto& [language, name]: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
		{
			localisedNames[language] = name;
		}
	}

	/* SPLIT STATES AND GRAMMAR */
	/* Default: "French Guyana" */
	/* French, Spanish, Portuguese, Italian: "Guyana French" */
	/* Reason: Grammar rules */
	/* */
	/* German: "French-Guyana" */
	/* Reason: To avoid having to deal with German adjective declension */
	else if (vic2State.isPartialState())
	{
		for (auto& [language, name]: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
		{
			std::optional<std::string> possibleOwnerAdjective;
			if ((language == "french") || (language == "spanish") || (language == "braz_por") || (language == "italian"))
			{
				std::string adjectiveKey = hoi4State.getOwner() + "_neutrality" + "_ADJ";
				const auto& languageCategory = vic2State.getLanguageCategory();
				if (const auto& grammarMapping = grammarMappings.find(languageCategory);
					 grammarMapping != grammarMappings.end())
				{
					adjectiveKey += grammarMapping->second;
					if (language == "french")
					{
						adjectiveKey += "_FR";
					}
					else if (language == "spanish")
					{
						adjectiveKey += "_ES";
					}
					else if (language == "braz_por")
					{
						adjectiveKey += "_PT";
					}
					else // (language == "italian")
					{
						adjectiveKey += "_IT";
					}
				}
				if (const auto hoi4LocalisationsInLanguage = customLocalisations.find(language);
					 hoi4LocalisationsInLanguage != customLocalisations.end())
				{
					if (const auto hoi4Localisation = hoi4LocalisationsInLanguage->second.find(adjectiveKey);
						 hoi4Localisation != hoi4LocalisationsInLanguage->second.end())
					{
						possibleOwnerAdjective = hoi4Localisation->second;
					}
				}
			}

			if (!possibleOwnerAdjective)
			{
				// if the fancy localisations can't be found or doesn't apply, try to fall back to basic behavior
				possibleOwnerAdjective = vic2Localisations.getTextInLanguage(vic2State.getOwner() + "_ADJ", language);
			}

			if (!possibleOwnerAdjective)
			{
				// in the final case, just use the word "partial"
				Log(LogLevel::Warning) << "No localisation found for " << vic2State.getOwner() + "_ADJ" << " in "
											  << language;
				if (const auto& partial = vic2Localisations.getTextInLanguage("PARTIAL", language); partial)
				{
					possibleOwnerAdjective = *partial;
				}
				else
				{
					possibleOwnerAdjective = "Partial";
				}
			}

			if ((language == "french") || (language == "spanish") || (language == "braz_por") || (language == "italian"))
			{
				name += " " + *possibleOwnerAdjective;
			}
			else if (language == "german")
			{
				name = possibleOwnerAdjective->append("-").append(name);
			}
			else
			{
				name = possibleOwnerAdjective->append(" ").append(name);
			}

			localisedNames[language] = name;
		}
	}

	// states that were split by the converter and have the capital get the Vic2 state name
	else if (stateHasCapital(sourceProvinceNumbers, theStateDefinitions))
	{
		for (const auto& [language, name]: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
		{
			localisedNames[language] = name;
		}
	}

	// states split by the converter possibly get backup names
	else if (!hoi4State.isImpassable())
	{
		const auto& splitNameInLanguages = vic2Localisations.getTextInEachLanguage(vic2State.getStateID() + "_SPLIT");
		for (const auto& [language, localisation]: splitNameInLanguages)
		{
			localisedNames[language] = localisation;
		}
		if (splitNameInLanguages.empty())
		{
			Log(LogLevel::Warning) << vic2State.getStateID() << " had a split section with no localisation. Add "
										  << vic2State.getStateID()
										  << "_SPLIT to Configurables/Vic2Localisations.csv for better conversion.";
		}
	}

	// if wasteland localisations exist update or override other localisations
	if (hoi4State.isImpassable())
	{
		if (!stateHasAllDefinedProvincesAfterConversion(hoi4State,
				  sourceProvinceNumbers,
				  theStateDefinitions,
				  theProvinceMapper))
		{
			for (auto& localisation: localisedNames | std::ranges::views::values)
			{
				localisation += " Wasteland";
			}

			const auto& wastelandNameInLanguages =
				 vic2Localisations.getTextInEachLanguage(vic2State.getStateID() + "_WASTELAND");
			for (const auto& [language, localisation]: wastelandNameInLanguages)
			{
				localisedNames[language] = localisation;
			}
			if (wastelandNameInLanguages.empty())
			{
				Log(LogLevel::Warning) << vic2State.getStateID() << " had a wasteland section with no localisation. Add "
											  << vic2State.getStateID()
											  << "_WASTELAND to Configurables/Vic2Localisations.csv for better conversion.";
			}
		}
	}

	if (localisedNames.empty())
	{
		const auto hoi4Province = *hoi4State.getProvinces().begin();
		if (const auto possibleVic2Provinces = theProvinceMapper.getHoI4ToVic2ProvinceMapping(hoi4Province);
			 !possibleVic2Provinces.empty())
		{
			const auto theProvince = possibleVic2Provinces[0];
			const auto provinceNameInLanguages =
				 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string(theProvince));
			if (provinceNameInLanguages.empty())
			{
				Log(LogLevel::Warning) << "Could not find localization for Vic2 province " << theProvince;
			}
			for (const auto& [language, provinceName]: provinceNameInLanguages)
			{
				localisedNames[language] = provinceName;
			}
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find localization for HoI4 province " << hoi4Province;
		}
	}

	for (const auto& [language, localisation]: localisedNames)
	{
		getExistingStateLocalisation(language).insert(std::make_pair(hoi4State.getID(), localisation));
	}
}


void HoI4::Localisation::addStateLocalisations(const States& states,
	 const Vic2::Localisations& vic2Localisations,
	 const Mappers::ProvinceMapper& theProvinceMapper,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tAdding state localisations";
	for (const auto& state: states.getStates())
	{
		if (auto VPPositionInHoI4 = state.second.getVPLocation(); VPPositionInHoI4)
		{
			if (auto VPProvinceMapping = theProvinceMapper.getHoI4ToVic2ProvinceMapping(*VPPositionInHoI4);
				 !VPProvinceMapping.empty())
			{
				for (const auto& [language, name]:
					 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string(VPProvinceMapping[0])))
				{
					addVPLocalisationForLanguage(state.second, language, name);
				}
			}
		}

		if (theConfiguration.getDebug())
		{
			addDebugLocalisations(state, vic2Localisations, theProvinceMapper);
		}
	}

	addNonenglishStateLocalisations();
	addNonenglishVPLocalisations();
}


void HoI4::Localisation::addDebugLocalisations(const std::pair<const int, State>& state,
	 const Vic2::Localisations& vic2Localisations,
	 const Mappers::ProvinceMapper& theProvinceMapper)
{
	for (const auto VPPositionInHoI4: state.second.getDebugVPs())
	{
		if (auto VPProvinceMapping = theProvinceMapper.getHoI4ToVic2ProvinceMapping(VPPositionInHoI4);
			 !VPProvinceMapping.empty())
		{
			for (const auto& [language, name]:
				 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string(VPProvinceMapping[0])))
			{
				getExistingVPLocalisation(language).insert(
					 std::make_pair("VICTORY_POINTS_" + std::to_string(VPPositionInHoI4), name));
			}
		}
	}

	for (const auto VPPositionInHoI4: state.second.getSecondaryDebugVPs())
	{
		if (auto VPProvinceMapping = theProvinceMapper.getHoI4ToVic2ProvinceMapping(VPPositionInHoI4);
			 !VPProvinceMapping.empty())
		{
			for (const auto& [language, name]:
				 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string(VPProvinceMapping[0])))
			{
				getExistingVPLocalisation(language).insert(
					 make_pair("VICTORY_POINTS_" + std::to_string(VPPositionInHoI4), "_" + name));
			}
		}
	}
}


void HoI4::Localisation::addVPLocalisationForLanguage(const State& state,
	 const std::string& language,
	 const std::string& name)
{
	if (state.getVPLocation())
	{
		getExistingVPLocalisation(language).insert(
			 std::make_pair("VICTORY_POINTS_" + std::to_string(*state.getVPLocation()), name));
	}
}


std::map<HoI4::stateNumber, std::string>& HoI4::Localisation::getExistingStateLocalisation(const std::string& language)
{
	auto existingLocalisation = stateLocalisations.find(language);
	if (existingLocalisation == stateLocalisations.end())
	{
		addLanguageToStateLocalisations(language);
		existingLocalisation = stateLocalisations.find(language);
	}

	return existingLocalisation->second;
}


HoI4::keyToLocalisationMap& HoI4::Localisation::getExistingVPLocalisation(const std::string& language)
{
	auto existingLocalisation = VPLocalisations.find(language);
	if (existingLocalisation == VPLocalisations.end())
	{
		addLanguageToVPLocalisations(language);
		existingLocalisation = VPLocalisations.find(language);
	}

	return existingLocalisation->second;
}


void HoI4::Localisation::addLanguageToStateLocalisations(const std::string& language)
{
	const std::map<stateNumber, std::string> newLocalisation;
	stateLocalisations[language] = newLocalisation;
}


void HoI4::Localisation::addLanguageToVPLocalisations(const std::string& language)
{
	const keyToLocalisationMap newLocalisation;
	VPLocalisations[language] = newLocalisation;
}


void HoI4::Localisation::addNonenglishStateLocalisations()
{
	const auto& englishLocalisations = stateLocalisations.find("english")->second;
	stateLocalisations.insert(make_pair("braz_por", englishLocalisations));
	stateLocalisations.insert(make_pair("polish", englishLocalisations));
	stateLocalisations.insert(make_pair("russian", englishLocalisations));
	stateLocalisations.insert(make_pair("japanese", englishLocalisations));
}


void HoI4::Localisation::addNonenglishVPLocalisations()
{
	const auto& englishLocalisations = VPLocalisations.find("english")->second;
	VPLocalisations.insert(make_pair("braz_por", englishLocalisations));
	VPLocalisations.insert(make_pair("polish", englishLocalisations));
	VPLocalisations.insert(make_pair("russian", englishLocalisations));
	VPLocalisations.insert(make_pair("japanese", englishLocalisations));
}


void HoI4::Localisation::addEventLocalisation(const std::string& event, const std::string& localisation)
{
	for (const auto& language: newEventLocalisations | std::views::keys)
	{
		newEventLocalisations[language][event] = localisation;
	}
}


void HoI4::Localisation::addEventLocalisationFromVic2(const std::string& Vic2Key,
	 const std::string& HoI4Key,
	 const Vic2::Localisations& vic2Localisations)
{
	std::set<std::string> handled_languages;
	for (const auto& [language, text]: vic2Localisations.getTextInEachLanguage(Vic2Key))
	{
		auto existingLanguage = newEventLocalisations.find(language);
		if (existingLanguage == newEventLocalisations.end())
		{
			keyToLocalisationMap mappings;
			newEventLocalisations.insert(make_pair(language, mappings));
			existingLanguage = newEventLocalisations.find(language);
		}

		existingLanguage->second[HoI4Key] = text;
		handled_languages.insert(language);
	}

	for (const auto& language: supported_languages)
	{
		if (handled_languages.contains(language))
		{
			continue;
		}

		const auto english_localisations = newEventLocalisations.find("english");
		if (english_localisations == newEventLocalisations.end())
		{
			break;
		}

		const auto english_localisation = english_localisations->second.find(HoI4Key);
		if (english_localisation == english_localisations->second.end())
		{
			continue;
		}

		auto unhandled_language = newEventLocalisations.find(language);
		if (unhandled_language == newEventLocalisations.end())
		{
			keyToLocalisationMap new_localisations;
			newEventLocalisations.insert(make_pair(language, new_localisations));
			unhandled_language = newEventLocalisations.find(language);
		}
		unhandled_language->second[HoI4Key] = english_localisation->second;
	}
}


void HoI4::Localisation::addIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation)
{
	for (const auto& language: ideaLocalisations | std::views::keys)
	{
		if (localisation)
		{
			ideaLocalisations[language][idea] = *localisation;
		}
		else
		{
			if (auto genericLocalisationsInLanguage = genericIdeaLocalisations.find(language);
				 genericLocalisationsInLanguage != genericIdeaLocalisations.end())
			{
				auto genericIdeaStr = "generic" + idea.substr(3, idea.size());
				if (auto genericIdea = genericLocalisationsInLanguage->second.find(genericIdeaStr);
					 genericIdea != genericLocalisationsInLanguage->second.end())
				{
					ideaLocalisations[language][idea] = genericIdea->second;
				}
				else
				{
					Log(LogLevel::Warning) << "Could not find localisation for " << genericIdeaStr << " in " << language;
				}
			}
			else
			{
				Log(LogLevel::Warning) << "No generic idea localisations found for " << language;
			}
		}
	}
}


void HoI4::Localisation::addIdeaLocalisation(const std::string& idea,
	 const std::string& localisation,
	 const std::string& language)
{
	if (const auto& localisationInLanguage = ideaLocalisations.find(language);
		 localisationInLanguage != ideaLocalisations.end())
	{
		localisationInLanguage->second[idea] = localisation;
		return;
	}

	ideaLocalisations[language].emplace(idea, localisation);
}


void HoI4::Localisation::addPoliticalPartyLocalisation(const std::string& Vic2Key,
	 const std::string& HoI4Key,
	 const Vic2::Localisations& vic2Localisations)
{
	std::set<std::string> handled_languages;
	for (const auto& [language, text]: vic2Localisations.getTextInEachLanguage(Vic2Key))
	{
		auto existingLanguage = politicalPartyLocalisations.find(language);
		if (existingLanguage == politicalPartyLocalisations.end())
		{
			keyToLocalisationMap mappings;
			politicalPartyLocalisations.insert(make_pair(language, mappings));
			existingLanguage = politicalPartyLocalisations.find(language);
		}

		existingLanguage->second[HoI4Key] = text;
		handled_languages.insert(language);
	}

	for (const auto& language: supported_languages)
	{
		if (handled_languages.contains(language))
		{
			continue;
		}

		const auto english_localisations = politicalPartyLocalisations.find("english");
		if (english_localisations == politicalPartyLocalisations.end())
		{
			break;
		}

		const auto english_localisation = english_localisations->second.find(HoI4Key);
		if (english_localisation == english_localisations->second.end())
		{
			continue;
		}

		auto unhandled_language = politicalPartyLocalisations.find(language);
		if (unhandled_language == politicalPartyLocalisations.end())
		{
			keyToLocalisationMap new_localisations;
			politicalPartyLocalisations.insert(make_pair(language, new_localisations));
			unhandled_language = politicalPartyLocalisations.find(language);
		}
		unhandled_language->second[HoI4Key] = english_localisation->second;
	}
}


void HoI4::Localisation::addRulingHouseLocalisations(const std::string& rulingParty, const std::string& lastDynasty)
{
	const auto& utf8Dynasty = commonItems::convertWin1252ToUTF8(lastDynasty);
	politicalPartyLocalisations["english"][rulingParty] = "House of " + utf8Dynasty;
	politicalPartyLocalisations["braz_por"][rulingParty] = "Casa de " + utf8Dynasty;
	politicalPartyLocalisations["french"][rulingParty] = "Dynastie " + utf8Dynasty;
	politicalPartyLocalisations["german"][rulingParty] = "Dynastie der " + utf8Dynasty;
	politicalPartyLocalisations["polish"][rulingParty] = "Dynastia " + utf8Dynasty + "ów";
	politicalPartyLocalisations["russian"][rulingParty] = "Династия " + utf8Dynasty;
	politicalPartyLocalisations["spanish"][rulingParty] = "Casa de " + utf8Dynasty;
	politicalPartyLocalisations["japanese"][rulingParty] = utf8Dynasty + "家";
}


void HoI4::Localisation::addDecisionLocalisation(const std::string& key, const std::optional<std::string>& localisation)
{
	for (const auto& language: decisionLocalisations | std::views::keys)
	{
		if (localisation)
		{
			decisionLocalisations[language][key] = *localisation;
		}
		else
		{
			auto genericLocalisationsInLanguage = genericIdeaLocalisations.find(language);
			if (genericLocalisationsInLanguage != genericIdeaLocalisations.end())
			{
				auto genericIdeaStr = "generic" + key.substr(3, key.size());
				auto genericIdea = genericLocalisationsInLanguage->second.find(genericIdeaStr);
				if (genericIdea != genericLocalisationsInLanguage->second.end())
				{
					ideaLocalisations[language][key] = genericIdea->second;
				}
				else
				{
					Log(LogLevel::Warning) << "Could not find localisation for " << genericIdeaStr << " in " << language;
				}
			}
			else
			{
				Log(LogLevel::Warning) << "No generic idea localisations found for " << language;
			}
		}
	}
}


void HoI4::Localisation::generateCustomLocalisations(ScriptedLocalisations& scriptedLocalisations,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tGenerating custom localisations";

	std::ifstream languageReplacementsFile("Configurables/languageReplacements.txt");
	if (!languageReplacementsFile.is_open())
	{
		return;
	}
	AllReplacementRules replacementRules(languageReplacementsFile);
	languageReplacementsFile.close();

	for (const auto& localisationsInLanguage: countryLocalisations)
	{
		ScriptedLocalisation masculineSingular;
		masculineSingular.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjMS");
		ScriptedLocalisation masculinePlural;
		masculinePlural.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjMP");
		ScriptedLocalisation feminineSingular;
		feminineSingular.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjFS");
		ScriptedLocalisation femininePlural;
		femininePlural.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjFP");

		auto rules = replacementRules.getRulesForLanguage(localisationsInLanguage.first);
		if (!rules)
		{
			continue;
		}

		for (const auto& localisation: localisationsInLanguage.second)
		{
			if (localisation.first.find("_ADJ") == std::string::npos)
			{
				continue;
			}

			std::smatch match;
			for (const auto& rule: rules->getTheRules())
			{
				if (std::regex_match(localisation.second, match, rule.getMatcher()))
				{
					for (const auto& replacement: rule.getReplacements())
					{
						customLocalisations[localisationsInLanguage.first][localisation.first + replacement.first] =
							 std::regex_replace(localisation.second, rule.getMatcher(), replacement.second);

						if (replacement.first == "_MS_" + getLanguageCode(localisationsInLanguage.first))
						{
							insertScriptedLocalisation(localisation.first,
								 replacement.first,
								 masculineSingular,
								 majorIdeologies);
						}
						else if (replacement.first == "_MP_" + getLanguageCode(localisationsInLanguage.first))
						{
							insertScriptedLocalisation(localisation.first,
								 replacement.first,
								 masculinePlural,
								 majorIdeologies);
						}
						else if (replacement.first == "_FS_" + getLanguageCode(localisationsInLanguage.first))
						{
							insertScriptedLocalisation(localisation.first,
								 replacement.first,
								 feminineSingular,
								 majorIdeologies);
						}
						else if (replacement.first == "_FP_" + getLanguageCode(localisationsInLanguage.first))
						{
							insertScriptedLocalisation(localisation.first, replacement.first, femininePlural, majorIdeologies);
						}
					}
					break;
				}
			}
		}

		scriptedLocalisations.giveAdjectiveLocalisation(getLanguageCode(localisationsInLanguage.first),
			 std::move(masculineSingular));
		scriptedLocalisations.giveAdjectiveLocalisation(getLanguageCode(localisationsInLanguage.first),
			 std::move(masculinePlural));
		scriptedLocalisations.giveAdjectiveLocalisation(getLanguageCode(localisationsInLanguage.first),
			 std::move(feminineSingular));
		scriptedLocalisations.giveAdjectiveLocalisation(getLanguageCode(localisationsInLanguage.first),
			 std::move(femininePlural));
	}
}


void HoI4::Localisation::updateLocalisationText(const std::string& key,
	 const std::string& oldText,
	 const std::string& newText)
{
	for (const auto& language: newFocuses | std::views::keys)
	{
		if (auto focusesInLanguage = newFocuses.find(language); focusesInLanguage != newFocuses.end())
		{
			if (auto focusText = focusesInLanguage->second.find(key); focusText != focusesInLanguage->second.end())
			{
				if (const auto position = focusText->second.find(oldText); position != std::string::npos)
				{
					focusText->second.replace(position, oldText.size(), newText);
				}
			}
		}
	}
}


void HoI4::Localisation::addCharacterLocalisation(const std::string& id, const std::string& name)
{
	characterLocalisations_["braz_por"].emplace(id, name);
	characterLocalisations_["czech"].emplace(id, name);
	characterLocalisations_["dutch"].emplace(id, name);
	characterLocalisations_["english"].emplace(id, name);
	characterLocalisations_["finnish"].emplace(id, name);
	characterLocalisations_["french"].emplace(id, name);
	characterLocalisations_["german"].emplace(id, name);
	characterLocalisations_["hungarian"].emplace(id, name);
	characterLocalisations_["italian"].emplace(id, name);
	characterLocalisations_["polish"].emplace(id, name);
	characterLocalisations_["russian"].emplace(id, name);
	characterLocalisations_["spanish"].emplace(id, name);
	characterLocalisations_["swedish"].emplace(id, name);
	characterLocalisations_["japanese"].emplace(id, name);
}