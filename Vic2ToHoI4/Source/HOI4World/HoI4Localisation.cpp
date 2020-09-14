#include "HoI4Localisation.h"
#include "../Configuration.h"
#include "../Mappers/GovernmentMapper.h"
#include "../V2World/Country.h"
#include "../V2World/States/State.h"
#include "../V2World/States/StateDefinitions.h"
#include "../V2World/Vic2Localisations.h"
#include "Localisations/AllReplacementRules.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "States/HoI4State.h"
#include "States/HoI4States.h"
#include <fstream>



std::unique_ptr<HoI4::Localisation> HoI4::Localisation::Importer::generateLocalisations(
	 const Configuration& theConfiguration)
{
	importLocalisations(theConfiguration);
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
		 customLocalisations);
}


void HoI4::Localisation::Importer::importLocalisations(const Configuration& theConfiguration)
{
	for (const auto& fileName: Utils::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/localisation"))
	{
		if (fileName.substr(0, 5) == "focus")
		{
			importFocusLocalisations(theConfiguration.getHoI4Path() + "/localisation/" + fileName);
		}
		else if (fileName.substr(0, 5) == "ideas")
		{
			importGenericIdeaLocalisations(theConfiguration.getHoI4Path() + "/localisation/" + fileName);
		}
		else if (fileName.substr(0, 6) == "events")
		{
			importEventLocalisations(theConfiguration.getHoI4Path() + "/localisation/" + fileName);
		}
	}

	for (const auto& fileName: Utils::GetAllFilesInFolder("blankmod/output/localisation"))
	{
		if (fileName.substr(0, 5) == "focus")
		{
			importFocusLocalisations("blankmod/output/localisation/" + fileName);
		}
		else if (fileName.substr(0, 5) == "ideas")
		{
			importGenericIdeaLocalisations("blankmod/output/localisation/" + fileName);
		}
		else if (fileName.substr(0, 6) == "events")
		{
			importEventLocalisations("blankmod/output/localisation/" + fileName);
		}
	}
}


void HoI4::Localisation::Importer::importFocusLocalisations(const std::string& filename)
{
	importLocalisationFile(filename, originalFocuses);
}


void HoI4::Localisation::Importer::importGenericIdeaLocalisations(const std::string& filename)
{
	importLocalisationFile(filename, genericIdeaLocalisations);
}


void HoI4::Localisation::Importer::importEventLocalisations(const std::string& filename)
{
	importLocalisationFile(filename, originalEventLocalisations);
}


void HoI4::Localisation::Importer::importLocalisationFile(const std::string& filename,
	 languageToLocalisationsMap& localisations)
{
	keyToLocalisationMap newLocalisations;

	std::ifstream file(filename);
	if (!file.is_open())
	{
		Log(LogLevel::Error) << "Could not open " << filename;
		exit(-1);
	}
	char bitBucket[3];
	file.read(bitBucket, sizeof bitBucket);

	std::string language;
	while (!file.eof())
	{
		char buffer[2048];
		file.getline(buffer, sizeof buffer);
		std::string line(buffer);
		if (line.substr(0, 2) == "l_")
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

	auto localisationsInLanguage = localisations.find(language);
	if (localisationsInLanguage == localisations.end())
	{
		localisations[language] = newLocalisations;
	}
	else
	{
		for (const auto& localisation: newLocalisations)
		{
			localisationsInLanguage->second.insert(localisation);
		}
	}

	file.close();
}


void HoI4::Localisation::Importer::prepareBlankLocalisations()
{
	for (const auto& genericLocalisationsInLanguage: genericIdeaLocalisations)
	{
		keyToLocalisationMap newLocalisationsMap;
		ideaLocalisations.insert(make_pair(genericLocalisationsInLanguage.first, newLocalisationsMap));
		decisionLocalisations.insert(make_pair(genericLocalisationsInLanguage.first, newLocalisationsMap));
	}
}


void HoI4::Localisation::createCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags,
	 const governmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	addLocalisationsForAllGovernments(tags, "", "_DEF", governmentMap, vic2Localisations, articleRules);
	addLocalisationsForAllGovernments(tags, "_ADJ", "", governmentMap, vic2Localisations, articleRules);

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
	 const governmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	for (const auto& mapping: governmentMap.getGovernmentMappings())
	{
		auto localisationForGovernment =
			 vic2Localisations.getTextInEachLanguage(tags.first + "_" + mapping.vic2Government + vic2Suffix);
		addLocalisationsInAllLanguages(tags.second,
			 vic2Suffix,
			 hoi4Suffix,
			 mapping.HoI4GovernmentIdeology,
			 localisationForGovernment,
			 articleRules);
		if (localisationForGovernment.empty())
		{
			addLocalisationsInAllLanguages(tags.second,
				 vic2Suffix,
				 hoi4Suffix,
				 mapping.HoI4GovernmentIdeology,
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
	for (const auto& nameInLanguage: namesInLanguage)
	{
		auto existingLanguage = getExistingLocalisationsInLanguage(nameInLanguage.first);

		auto newKey = destTag + "_" + HoI4GovernmentIdeology + vic2Suffix;
		addLocalisation(newKey,
			 nameInLanguage.first,
			 existingLanguage->second,
			 nameInLanguage.second,
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
	auto plainLocalisation = vic2Localisations.getTextInEachLanguage(tags.first + vic2Suffix);
	if (!plainLocalisation.empty())
	{
		for (const auto& nameInLanguage: plainLocalisation)
		{
			auto existingLanguage = getExistingLocalisationsInLanguage(nameInLanguage.first);

			auto newKey = tags.second + "_neutrality" + vic2Suffix;
			addLocalisation(newKey,
				 nameInLanguage.first,
				 existingLanguage->second,
				 nameInLanguage.second,
				 hoi4Suffix,
				 articleRules);
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


void HoI4::Localisation::addLocalisation(const std::string& newKey,
	 const std::string& language,
	 keyToLocalisationMap& existingLanguage,
	 const std::string& localisation,
	 const std::string& HoI4Suffix,
	 const ArticleRules& articleRules)
{
	if (const auto existingLocalisation = existingLanguage.find(newKey); existingLocalisation == existingLanguage.end())
	{
		existingLanguage.insert(std::make_pair(newKey, articleRules.updateArticles(language, localisation)));
		if (!HoI4Suffix.empty())
		{
			existingLanguage.insert(std::make_pair(newKey + HoI4Suffix, localisation));
		}
	}
	else
	{
		existingLanguage[newKey] = articleRules.updateArticles(language, localisation);
		if (!HoI4Suffix.empty())
		{
			existingLanguage[newKey + HoI4Suffix] = localisation;
		}
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
	if (auto Vic2Text = vic2Localisations.getTextInEachLanguage(Vic2Key); Vic2Text.empty())
	{
		for (const auto& textInLanguage: Vic2Text)
		{
			auto localisations = getExistingLocalisationsInLanguage(textInLanguage.first);
			if (auto localisation = localisations->second.find(HoI4Key); localisation != localisations->second.end())
			{
				localisation->second = textInLanguage.second;
			}
		}

		return true;
	}

	return false;
}


bool HoI4::Localisation::attemptToUpdateMainCountryLocalisationChangingArticles(const std::string& HoI4Key,
	 const std::string& Vic2Key,
	 const Vic2::Localisations& vic2Localisations,
	 const ArticleRules& articleRules)
{
	if (auto Vic2Text = vic2Localisations.getTextInEachLanguage(Vic2Key); Vic2Text.empty())
	{
		for (const auto& textInLanguage: Vic2Text)
		{
			auto localisations = getExistingLocalisationsInLanguage(textInLanguage.first);
			if (auto localisation = localisations->second.find(HoI4Key); localisation != localisations->second.end())
			{
				localisation->second = articleRules.updateArticles(textInLanguage.first, textInLanguage.second);
			}
		}

		return true;
	}

	return false;
}


void HoI4::Localisation::addNonenglishCountryLocalisations()
{
	auto englishLocalisations = countryLocalisations.find("english");
	countryLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	countryLocalisations.insert(make_pair("polish", englishLocalisations->second));
	countryLocalisations.insert(make_pair("russian", englishLocalisations->second));
}


void HoI4::Localisation::copyFocusLocalisations(const std::string& oldKey, const std::string& newKey)
{
	for (auto languageLocalisations: originalFocuses)
	{
		auto newLanguage = newFocuses.find(languageLocalisations.first);
		if (newLanguage == newFocuses.end())
		{
			keyToLocalisationMap newLocalisations;
			newFocuses.insert(make_pair(languageLocalisations.first, newLocalisations));
			newLanguage = newFocuses.find(languageLocalisations.first);
		}

		auto oldLocalisation = languageLocalisations.second.find(oldKey);
		if (oldLocalisation != languageLocalisations.second.end())
		{
			newLanguage->second[newKey] = oldLocalisation->second;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find original localisation for " << oldKey << " in "
										  << languageLocalisations.first;
		}

		auto oldLocalisationDescription = languageLocalisations.second.find(oldKey + "_desc");
		if (oldLocalisationDescription != languageLocalisations.second.end())
		{
			newLanguage->second[newKey + "_desc"] = oldLocalisationDescription->second;
		}
	}
}


void HoI4::Localisation::copyEventLocalisations(const std::string& oldKey, const std::string& newKey)
{
	for (auto languageLocalisations: originalEventLocalisations)
	{
		auto newLanguage = newEventLocalisations.find(languageLocalisations.first);
		if (newLanguage == newEventLocalisations.end())
		{
			keyToLocalisationMap newLocalisations;
			newEventLocalisations.insert(make_pair(languageLocalisations.first, newLocalisations));
			newLanguage = newEventLocalisations.find(languageLocalisations.first);
		}

		auto oldLocalisation = languageLocalisations.second.find(oldKey);
		if (oldLocalisation != languageLocalisations.second.end())
		{
			newLanguage->second[newKey] = oldLocalisation->second;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find original localisation for " << oldKey << " in "
										  << languageLocalisations.first;
		}
	}
}


void HoI4::Localisation::addStateLocalisation(const State& hoi4State,
	 const Vic2::State& vic2State,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const Vic2::Localisations& vic2Localisations,
	 const mappers::ProvinceMapper& theProvinceMapper)
{
	for (const auto& Vic2NameInLanguage: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
	{
		addStateLocalisationForLanguage(hoi4State,
			 vic2State,
			 Vic2NameInLanguage,
			 theStateDefinitions,
			 vic2Localisations,
			 theProvinceMapper);
	}
}


void HoI4::Localisation::addStateLocalisations(const States& states,
	 const Vic2::Localisations& vic2Localisations,
	 const mappers::ProvinceMapper& theProvinceMapper,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tAdding state localisations";
	for (const auto& state: states.getStates())
	{
		auto VPPositionInHoI4 = state.second.getVPLocation();
		if (VPPositionInHoI4)
		{
			auto VPProvinceMapping = theProvinceMapper.getHoI4ToVic2ProvinceMapping(*VPPositionInHoI4);
			if (VPProvinceMapping && !VPProvinceMapping->empty())
			{
				for (const auto& Vic2NameInLanguage:
					 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string((*VPProvinceMapping)[0])))
				{
					addVPLocalisationForLanguage(state.second, Vic2NameInLanguage);
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
	 const mappers::ProvinceMapper& theProvinceMapper)
{
	for (auto VPPositionInHoI4: state.second.getDebugVPs())
	{
		auto VPProvinceMapping = theProvinceMapper.getHoI4ToVic2ProvinceMapping(VPPositionInHoI4);
		if (VPProvinceMapping && !VPProvinceMapping->empty())
		{
			for (const auto& Vic2NameInLanguage:
				 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string((*VPProvinceMapping)[0])))
			{
				getExistingVPLocalisation(Vic2NameInLanguage.first)
					 .insert(
						  std::make_pair("VICTORY_POINTS_" + std::to_string(VPPositionInHoI4), Vic2NameInLanguage.second));
			}
		}
	}

	for (auto VPPositionInHoI4: state.second.getSecondaryDebugVPs())
	{
		auto VPProvinceMapping = theProvinceMapper.getHoI4ToVic2ProvinceMapping(VPPositionInHoI4);
		if (VPProvinceMapping && !VPProvinceMapping->empty())
		{
			for (const auto& Vic2NameInLanguage:
				 vic2Localisations.getTextInEachLanguage("PROV" + std::to_string((*VPProvinceMapping)[0])))
			{
				getExistingVPLocalisation(Vic2NameInLanguage.first)
					 .insert(
						  make_pair("VICTORY_POINTS_" + std::to_string(VPPositionInHoI4), "_" + Vic2NameInLanguage.second));
			}
		}
	}
}


bool HoI4::Localisation::sourceStateHasOneProvince(const State& hoi4State,
	 const mappers::ProvinceMapper& theProvinceMapper)
{
	std::set<int> allVic2Provinces;
	for (const auto& hoi4Province: hoi4State.getProvinces())
	{
		const auto Vic2Provinces = theProvinceMapper.getHoI4ToVic2ProvinceMapping(hoi4Province);
		allVic2Provinces.insert(Vic2Provinces->begin(), Vic2Provinces->end());
	}
	return allVic2Provinces.size() == 1;
}


bool HoI4::Localisation::destinationStateHasOneProvince(const State& hoi4State)
{
	return hoi4State.getProvinces().size() == 1;
}


bool HoI4::Localisation::sourceStateHasAllButOneProvinceFromDefinition(const Vic2::State& sourceState,
	 const Vic2::StateDefinitions& theStateDefinitions)
{
	return sourceState.getProvinces().size() ==
			 theStateDefinitions.getAllProvinces(*sourceState.getProvinceNumbers().begin()).size() - 1;
}


bool HoI4::Localisation::stateHasAllDefinedProvincesAfterConversion(const State& state,
	 const Vic2::State& sourceState,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const mappers::ProvinceMapper& theProvinceMapper)
{
	std::set<int> stateDefinitionDefinitionProvinces;

	auto stateDefinitionSourceProvinces = theStateDefinitions.getAllProvinces(*sourceState.getProvinceNumbers().begin());
	for (auto sourceProvince: stateDefinitionSourceProvinces)
	{
		auto possibleMappedProvinces = theProvinceMapper.getVic2ToHoI4ProvinceMapping(sourceProvince);
		if (possibleMappedProvinces)
		{
			for (auto HoI4Province: *possibleMappedProvinces)
			{
				stateDefinitionDefinitionProvinces.insert(HoI4Province);
			}
		}
	}

	for (auto definedProvince: stateDefinitionDefinitionProvinces)
	{
		if (state.getProvinces().count(definedProvince) == 0)
		{
			return false;
		}
	}

	return true;
}


void HoI4::Localisation::addStateLocalisationForLanguage(const State& hoi4State,
	 const Vic2::State& vic2State,
	 const std::pair<const std::string, std::string>& Vic2NameInLanguage,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const Vic2::Localisations& vic2Localisations,
	 const mappers::ProvinceMapper& theProvinceMapper)
{
	std::string localisedName;
	if (destinationStateHasOneProvince(hoi4State) || sourceStateHasOneProvince(hoi4State, theProvinceMapper))
	{
		const auto hoi4Province = *hoi4State.getProvinces().begin();
		const auto possibleVic2Provinces = theProvinceMapper.getHoI4ToVic2ProvinceMapping(hoi4Province);
		if (possibleVic2Provinces && !possibleVic2Provinces->empty())
		{
			const auto theProvince = *possibleVic2Provinces->begin();
			auto possibleProvinceName =
				 vic2Localisations.getTextInLanguage("PROV" + std::to_string(theProvince), Vic2NameInLanguage.first);
			if (possibleProvinceName)
			{
				localisedName = *possibleProvinceName;
			}
			else
			{
				Log(LogLevel::Warning) << "Could not find localization for Vic2 province " << theProvince;
			}
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find localization for HoI4 province " << hoi4Province;
		}
	}
	else if (sourceStateHasAllButOneProvinceFromDefinition(vic2State, theStateDefinitions))
	{
		localisedName = Vic2NameInLanguage.second;
	}
	else if (stateHasAllDefinedProvincesAfterConversion(hoi4State, vic2State, theStateDefinitions, theProvinceMapper))
	{
		localisedName = Vic2NameInLanguage.second;
	}
	/* SPLIT STATES AND GRAMMAR */
	/* Default: "French Guyana" */
	/* French, Spanish, Portugese(sic), Italian: "Guyana French" */
	/* Reason: Grammar rules */
	/* */
	/* German: "French-Guyana" */
	/* Reason: To avoid having to deal with German adjective declension */
	else if (vic2State.isPartialState())
	{
		auto possibleOwnerAdjective =
			 vic2Localisations.getTextInLanguage(vic2State.getOwner() + "_ADJ", Vic2NameInLanguage.first);
		if (possibleOwnerAdjective)
		{
			if ((Vic2NameInLanguage.first == "french") || (Vic2NameInLanguage.first == "spanish") || (Vic2NameInLanguage.first == "portugese") ||
				 (Vic2NameInLanguage.first == "italian"))
			{
				localisedName = Vic2NameInLanguage.second + " " + *possibleOwnerAdjective;
			}
			else
			{
				if (Vic2NameInLanguage.first == "german" )
				{
					localisedName = *possibleOwnerAdjective + "-" + Vic2NameInLanguage.second;
				}
				else
				{
					localisedName = *possibleOwnerAdjective + " " + Vic2NameInLanguage.second;
				}
			}
		}
	}
	else if (hoi4State.isImpassable())
	{
		auto possibleWastelandName =
			 vic2Localisations.getTextInLanguage(vic2State.getStateID() + "_WASTELAND", Vic2NameInLanguage.first);
		if (possibleWastelandName)
		{
			localisedName = *possibleWastelandName;
		}
		else
		{
			localisedName = Vic2NameInLanguage.second + " Wasteland";
			Log(LogLevel::Warning) << Vic2NameInLanguage.second << " had a wasteland section with no localisation. Add "
										  << vic2State.getStateID()
										  << "_WASTELAND to DataFiles/Vic2Localisations.csv for better conversion.";
		}
	}
	else
	{
		localisedName = Vic2NameInLanguage.second;
	}

	getExistingStateLocalisation(Vic2NameInLanguage.first).insert(std::make_pair(hoi4State.getID(), localisedName));
}


void HoI4::Localisation::addVPLocalisationForLanguage(const State& state,
	 const std::pair<const std::string, std::string>& Vic2NameInLanguage)
{
	if (state.getVPLocation())
	{
		getExistingVPLocalisation(Vic2NameInLanguage.first)
			 .insert(
				  std::make_pair("VICTORY_POINTS_" + std::to_string(*state.getVPLocation()), Vic2NameInLanguage.second));
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
	auto englishLocalisations = stateLocalisations.find("english");
	stateLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	stateLocalisations.insert(make_pair("polish", englishLocalisations->second));
	stateLocalisations.insert(make_pair("russian", englishLocalisations->second));
}


void HoI4::Localisation::addNonenglishVPLocalisations()
{
	auto englishLocalisations = VPLocalisations.find("english");
	VPLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	VPLocalisations.insert(make_pair("polish", englishLocalisations->second));
	VPLocalisations.insert(make_pair("russian", englishLocalisations->second));
}


void HoI4::Localisation::addEventLocalisation(const std::string& event, const std::string& localisation)
{
	for (const auto& localisationInLanguage: newEventLocalisations)
	{
		newEventLocalisations[localisationInLanguage.first][event] = localisation;
	}
}


void HoI4::Localisation::addEventLocalisationFromVic2(const std::string& Vic2Key,
	 const std::string& HoI4Key,
	 const Vic2::Localisations& vic2Localisations)
{
	for (const auto& textInLanguage: vic2Localisations.getTextInEachLanguage(Vic2Key))
	{
		auto language = textInLanguage.first;
		auto existingLanguage = newEventLocalisations.find(language);
		if (existingLanguage == newEventLocalisations.end())
		{
			keyToLocalisationMap mappings;
			newEventLocalisations.insert(make_pair(language, mappings));
			existingLanguage = newEventLocalisations.find(language);
		}

		existingLanguage->second[HoI4Key] = textInLanguage.second;
	}
}


void HoI4::Localisation::addIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation)
{
	for (const auto& localisationInLanguage: ideaLocalisations)
	{
		if (localisation)
		{
			ideaLocalisations[localisationInLanguage.first][idea] = *localisation;
		}
		else
		{
			auto genericLocalisationsInLanguage = genericIdeaLocalisations.find(localisationInLanguage.first);
			if (genericLocalisationsInLanguage != genericIdeaLocalisations.end())
			{
				auto genericIdeaStr = "generic" + idea.substr(3, idea.size());
				auto genericIdea = genericLocalisationsInLanguage->second.find(genericIdeaStr);
				if (genericIdea != genericLocalisationsInLanguage->second.end())
				{
					ideaLocalisations[localisationInLanguage.first][idea] = genericIdea->second;
				}
				else
				{
					Log(LogLevel::Warning) << "Could not find localisation for " << genericIdeaStr << " in "
												  << localisationInLanguage.first;
				}
			}
			else
			{
				Log(LogLevel::Warning) << "No generic idea localisations found for " << localisationInLanguage.first;
			}
		}
	}
}


void HoI4::Localisation::addPoliticalPartyLocalisation(const std::string& Vic2Key,
	 const std::string& HoI4Key,
	 const Vic2::Localisations& vic2Localisations)
{
	for (const auto& textInLanguage: vic2Localisations.getTextInEachLanguage(Vic2Key))
	{
		auto language = textInLanguage.first;
		auto existingLanguage = politicalPartyLocalisations.find(language);
		if (existingLanguage == politicalPartyLocalisations.end())
		{
			keyToLocalisationMap mappings;
			politicalPartyLocalisations.insert(make_pair(language, mappings));
			existingLanguage = politicalPartyLocalisations.find(language);
		}

		existingLanguage->second[HoI4Key] = textInLanguage.second;
	}
}


void HoI4::Localisation::addDecisionLocalisation(const std::string& key, const std::optional<std::string>& localisation)
{
	for (const auto& localisationInLanguage: decisionLocalisations)
	{
		if (localisation)
		{
			decisionLocalisations[localisationInLanguage.first][key] = *localisation;
		}
		else
		{
			auto genericLocalisationsInLanguage = genericIdeaLocalisations.find(localisationInLanguage.first);
			if (genericLocalisationsInLanguage != genericIdeaLocalisations.end())
			{
				auto genericIdeaStr = "generic" + key.substr(3, key.size());
				auto genericIdea = genericLocalisationsInLanguage->second.find(genericIdeaStr);
				if (genericIdea != genericLocalisationsInLanguage->second.end())
				{
					ideaLocalisations[localisationInLanguage.first][key] = genericIdea->second;
				}
				else
				{
					Log(LogLevel::Warning) << "Could not find localisation for " << genericIdeaStr << " in "
												  << localisationInLanguage.first;
				}
			}
			else
			{
				Log(LogLevel::Warning) << "No generic idea localisations found for " << localisationInLanguage.first;
			}
		}
	}
}


void HoI4::Localisation::generateCustomLocalisations(ScriptedLocalisations& scriptedLocalisations,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tGenerating custom localisations";

	std::ifstream languageReplacementsFile("DataFiles/languageReplacements.txt");
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
	for (const auto& localisationsInLanguage: newFocuses)
	{
		if (auto focusesInLanguage = newFocuses.find(localisationsInLanguage.first);
			 focusesInLanguage != newFocuses.end())
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


std::string HoI4::Localisation::getLanguageCode(const std::string& language)
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


void HoI4::Localisation::insertScriptedLocalisation(const std::string& localisationKey,
	 const std::string& replacementKey,
	 ScriptedLocalisation& scriptedLocalisation,
	 const std::set<std::string>& majorIdeologies) const
{
	const std::regex extractRegex("([A-Z0-9]{3})_([a-z]+)_ADJ");

	std::smatch match;
	std::regex_match(localisationKey, match, extractRegex);
	const std::string tag = match[1];
	const std::string ideology = match[2];
	if (!majorIdeologies.count(ideology))
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
