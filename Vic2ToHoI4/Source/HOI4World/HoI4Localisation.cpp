#include "HoI4Localisation.h"
#include "../Configuration.h"
#include "../Mappers/GovernmentMapper.h"
#include "../V2World/Country.h"
#include "../V2World/Province.h"
#include "../V2World/State.h"
#include "../V2World/StateDefinitions.h"
#include "../V2World/Vic2Localisations.h"
#include "Localisations/AllReplacementRules.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "States/HoI4State.h"
#include "States/HoI4States.h"
#include <fstream>



HoI4Localisation::HoI4Localisation() noexcept
{
	importLocalisations();
	prepareBlankLocalisations();
}


void HoI4Localisation::importLocalisations()
{
	std::set<std::string> fileNames;
	Utils::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/localisation", fileNames);
	for (const auto& fileName: fileNames)
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

	fileNames.clear();
	Utils::GetAllFilesInFolder("blankmod/output/localisation", fileNames);
	for (const auto& fileName: fileNames)
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


void HoI4Localisation::importFocusLocalisations(const std::string& filename)
{
	importLocalisationFile(filename, originalFocuses);
}


void HoI4Localisation::importGenericIdeaLocalisations(const std::string& filename)
{
	importLocalisationFile(filename, genericIdeaLocalisations);
}


void HoI4Localisation::importEventLocalisations(const std::string& filename)
{
	importLocalisationFile(filename, originalEventLocalisations);
}


void HoI4Localisation::importLocalisationFile(const std::string& filename, languageToLocalisationsMap& localisations)
{
	keyToLocalisationMap newLocalisations;

	std::ifstream file(filename);
	if (!file.is_open())
	{
		LOG(LogLevel::Error) << "Could not open " << filename;
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


void HoI4Localisation::prepareBlankLocalisations()
{
	for (const auto& genericLocalisationsInLanguage: genericIdeaLocalisations)
	{
		keyToLocalisationMap newLocalisationsMap;
		ideaLocalisations.insert(make_pair(genericLocalisationsInLanguage.first, newLocalisationsMap));
		decisionLocalisations.insert(make_pair(genericLocalisationsInLanguage.first, newLocalisationsMap));
	}
}


void HoI4Localisation::createCountryLocalisations(const std::pair<const std::string&, const std::string&>& tags,
	 const governmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations)
{
	addLocalisationsForAllGovernments(tags,
		 std::make_pair(std::string(), std::string("_DEF")),
		 governmentMap,
		 vic2Localisations);
	addLocalisationsForAllGovernments(tags,
		 std::make_pair(std::string("_ADJ"), std::string()),
		 governmentMap,
		 vic2Localisations);

	if (!addNeutralLocalisation(tags, std::make_pair(std::string(), std::string("_DEF")), vic2Localisations))
	{
		LOG(LogLevel::Warning) << "Could not find plain localisation for " << tags.first;
	}
	if (!addNeutralLocalisation(tags, std::make_pair(std::string("_ADJ"), std::string()), vic2Localisations))
	{
		LOG(LogLevel::Warning) << "Could not find plain adjective localisation for " << tags.first;
	}
}


void HoI4Localisation::addLocalisationsForAllGovernments(const std::pair<const std::string&, const std::string&>& tags,
	 const std::pair<const std::string&, const std::string&>& suffixes,
	 const governmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations)
{
	for (const auto& mapping: governmentMap.getGovernmentMappings())
	{
		auto localisationForGovernment =
			 vic2Localisations.getTextInEachLanguage(tags.first + "_" + mapping.vic2Government + suffixes.first);
		addLocalisationsInAllLanguages(tags.second, suffixes, mapping.HoI4GovernmentIdeology, localisationForGovernment);
		if (localisationForGovernment.size() == 0)
		{
			addLocalisationsInAllLanguages(tags.second,
				 suffixes,
				 mapping.HoI4GovernmentIdeology,
				 vic2Localisations.getTextInEachLanguage(tags.first + suffixes.first));
		}
	}
}


void HoI4Localisation::addLocalisationsInAllLanguages(const std::string& destTag,
	 const std::pair<const std::string&, const std::string&>& suffixes,
	 const std::string& HoI4GovernmentIdeology,
	 const keyToLocalisationMap& namesInLanguage)
{
	for (const auto& nameInLanguage: namesInLanguage)
	{
		auto existingLanguage = getExistingLocalisationsInLanguage(nameInLanguage.first);

		auto newKey = destTag + "_" + HoI4GovernmentIdeology + suffixes.first;
		addLocalisation(newKey, existingLanguage->second, nameInLanguage.second, suffixes.second);
	}
}


bool HoI4Localisation::addNeutralLocalisation(const std::pair<const std::string&, const std::string&>& tags,
	 const std::pair<const std::string&, const std::string&>& suffixes,
	 const Vic2::Localisations& vic2Localisations)
{
	auto plainLocalisation = vic2Localisations.getTextInEachLanguage(tags.first + suffixes.first);
	if (plainLocalisation.size() > 0)
	{
		for (const auto& nameInLanguage: plainLocalisation)
		{
			auto existingLanguage = getExistingLocalisationsInLanguage(nameInLanguage.first);

			auto newKey = tags.second + "_neutrality" + suffixes.first;
			addLocalisation(newKey, existingLanguage->second, nameInLanguage.second, suffixes.second);
		}
		return true;
	}

	return false;
}


languageToLocalisationsMap::iterator HoI4Localisation::getExistingLocalisationsInLanguage(const std::string& language)
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


void HoI4Localisation::addLocalisation(const std::string& newKey,
	 keyToLocalisationMap& existingLanguage,
	 const std::string& localisation,
	 const std::string& HoI4Suffix)
{
	if (const auto existingLocalisation = existingLanguage.find(newKey); existingLocalisation == existingLanguage.end())
	{
		existingLanguage.insert(std::make_pair(newKey, localisation));
		if (!HoI4Suffix.empty())
		{
			existingLanguage.insert(std::make_pair(newKey + HoI4Suffix, localisation));
		}
	}
	else
	{
		existingLanguage[newKey] = localisation;
		if (!HoI4Suffix.empty())
		{
			existingLanguage[newKey + HoI4Suffix] = localisation;
		}
	}
}


void HoI4Localisation::updateMainCountryLocalisation(const std::string& HoI4Key,
	 const std::string& Vic2Tag,
	 const std::string& Vic2Government,
	 const Vic2::Localisations& vic2Localisations)
{
	if (!attemptToUpdateMainCountryLocalisation(HoI4Key, Vic2Tag + "_" + Vic2Government, vic2Localisations))
	{
		attemptToUpdateMainCountryLocalisation(HoI4Key, Vic2Tag, vic2Localisations);
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


bool HoI4Localisation::attemptToUpdateMainCountryLocalisation(const std::string& HoI4Key,
	 const std::string& Vic2Key,
	 const Vic2::Localisations& vic2Localisations)
{
	if (auto Vic2Text = vic2Localisations.getTextInEachLanguage(Vic2Key); Vic2Text.size() > 0)
	{
		for (const auto& textInLanguage: Vic2Text)
		{
			auto HoI4Localisations = getExistingLocalisationsInLanguage(textInLanguage.first);
			if (auto HoI4Localisation = HoI4Localisations->second.find(HoI4Key);
				 HoI4Localisation != HoI4Localisations->second.end())
			{
				HoI4Localisation->second = textInLanguage.second;
			}
		}

		return true;
	}

	return false;
}


void HoI4Localisation::addNonenglishCountryLocalisations()
{
	auto englishLocalisations = countryLocalisations.find("english");
	countryLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	countryLocalisations.insert(make_pair("polish", englishLocalisations->second));
	countryLocalisations.insert(make_pair("russian", englishLocalisations->second));
}


void HoI4Localisation::copyFocusLocalisations(const std::string& oldKey, const std::string& newKey)
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
			LOG(LogLevel::Warning) << "Could not find original localisation for " << oldKey << " in "
										  << languageLocalisations.first;
		}

		auto oldLocalisationDescription = languageLocalisations.second.find(oldKey + "_desc");
		if (oldLocalisationDescription != languageLocalisations.second.end())
		{
			newLanguage->second[newKey + "_desc"] = oldLocalisationDescription->second;
		}
	}
}


void HoI4Localisation::copyEventLocalisations(const std::string& oldKey, const std::string& newKey)
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
			LOG(LogLevel::Warning) << "Could not find original localisation for " << oldKey << " in "
										  << languageLocalisations.first;
		}
	}
}


void HoI4Localisation::addStateLocalisation(const HoI4::State& hoi4State,
	 const Vic2::State& vic2State,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const Vic2::Localisations& vic2Localisations)
{
	for (const auto& Vic2NameInLanguage: vic2Localisations.getTextInEachLanguage(vic2State.getStateID()))
	{
		addStateLocalisationForLanguage(hoi4State, vic2State, Vic2NameInLanguage, theStateDefinitions, vic2Localisations);
	}
}


void HoI4Localisation::addStateLocalisations(const HoI4::States& states, const Vic2::Localisations& vic2Localisations)
{
	LOG(LogLevel::Info) << "\tAdding state localisations";
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
			addDebugLocalisations(state, vic2Localisations);
		}
	}

	addNonenglishStateLocalisations();
	addNonenglishVPLocalisations();
}


void HoI4Localisation::addDebugLocalisations(const std::pair<const int, HoI4::State>& state,
	 const Vic2::Localisations& vic2Localisations)
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


bool HoI4Localisation::sourceStateHasOneProvince(const Vic2::State& sourceState)
{
	return sourceState.getProvinces().size() == 1;
}


bool HoI4Localisation::sourceStateHasAllButOneProvinceFromDefinition(const Vic2::State& sourceState,
	 const Vic2::StateDefinitions& theStateDefinitions)
{
	return sourceState.getProvinces().size() ==
			 theStateDefinitions.getAllProvinces((*sourceState.getProvinces().begin())->getNumber()).size() - 1;
}


bool HoI4Localisation::stateHasAllDefinedProvincesAfterConversion(const HoI4::State& state,
	 const Vic2::State& sourceState,
	 const Vic2::StateDefinitions& theStateDefinitions)
{
	std::set<int> stateDefinitionDefinitionProvinces;

	auto stateDefinitionSourceProvinces =
		 theStateDefinitions.getAllProvinces((*sourceState.getProvinces().begin())->getNumber());
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


void HoI4Localisation::addStateLocalisationForLanguage(const HoI4::State& hoi4State,
	 const Vic2::State& vic2State,
	 const std::pair<const std::string, std::string>& Vic2NameInLanguage,
	 const Vic2::StateDefinitions& theStateDefinitions,
	 const Vic2::Localisations& vic2Localisations)
{
	std::string localisedName = "";
	if (sourceStateHasOneProvince(vic2State))
	{
		const auto theProvince = *vic2State.getProvinces().begin();
		auto possibleProvinceName = vic2Localisations.getTextInLanguage("PROV" + std::to_string(theProvince->getNumber()),
			 Vic2NameInLanguage.first);
		if (possibleProvinceName)
		{
			localisedName = *possibleProvinceName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not find localization for Vic2 province " << theProvince->getNumber();
		}
	}
	else if (sourceStateHasAllButOneProvinceFromDefinition(vic2State, theStateDefinitions))
	{
		localisedName = Vic2NameInLanguage.second;
	}
	else if (stateHasAllDefinedProvincesAfterConversion(hoi4State, vic2State, theStateDefinitions))
	{
		localisedName = Vic2NameInLanguage.second;
	}
	else if (vic2State.isPartialState())
	{
		auto possibleOwnerAdjective =
			 vic2Localisations.getTextInLanguage(vic2State.getOwner() + "_ADJ", Vic2NameInLanguage.first);
		if (possibleOwnerAdjective)
		{
			localisedName = *possibleOwnerAdjective + " " + Vic2NameInLanguage.second;
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
			LOG(LogLevel::Warning) << Vic2NameInLanguage.second << " had a wasteland section with no localisation. Add "
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


void HoI4Localisation::addVPLocalisationForLanguage(const HoI4::State& state,
	 const std::pair<const std::string, std::string>& Vic2NameInLanguage)
{
	if (state.getVPLocation())
	{
		getExistingVPLocalisation(Vic2NameInLanguage.first)
			 .insert(
				  std::make_pair("VICTORY_POINTS_" + std::to_string(*state.getVPLocation()), Vic2NameInLanguage.second));
	}
}


std::map<stateNumber, std::string>& HoI4Localisation::getExistingStateLocalisation(const std::string& language)
{
	auto existingLocalisation = stateLocalisations.find(language);
	if (existingLocalisation == stateLocalisations.end())
	{
		addLanguageToStateLocalisations(language);
		existingLocalisation = stateLocalisations.find(language);
	}

	return existingLocalisation->second;
}


keyToLocalisationMap& HoI4Localisation::getExistingVPLocalisation(const std::string& language)
{
	auto existingLocalisation = VPLocalisations.find(language);
	if (existingLocalisation == VPLocalisations.end())
	{
		addLanguageToVPLocalisations(language);
		existingLocalisation = VPLocalisations.find(language);
	}

	return existingLocalisation->second;
}


void HoI4Localisation::addLanguageToStateLocalisations(const std::string& language)
{
	const std::map<stateNumber, std::string> newLocalisation;
	stateLocalisations[language] = newLocalisation;
}


void HoI4Localisation::addLanguageToVPLocalisations(const std::string& language)
{
	const keyToLocalisationMap newLocalisation;
	VPLocalisations[language] = newLocalisation;
}


void HoI4Localisation::addNonenglishStateLocalisations()
{
	auto englishLocalisations = stateLocalisations.find("english");
	stateLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	stateLocalisations.insert(make_pair("polish", englishLocalisations->second));
	stateLocalisations.insert(make_pair("russian", englishLocalisations->second));
}


void HoI4Localisation::addNonenglishVPLocalisations()
{
	auto englishLocalisations = VPLocalisations.find("english");
	VPLocalisations.insert(make_pair("braz_por", englishLocalisations->second));
	VPLocalisations.insert(make_pair("polish", englishLocalisations->second));
	VPLocalisations.insert(make_pair("russian", englishLocalisations->second));
}


void HoI4Localisation::addEventLocalisation(const std::string& event, const std::string& localisation)
{
	for (const auto& localisationInLanguage: newEventLocalisations)
	{
		newEventLocalisations[localisationInLanguage.first][event] = localisation;
	}
}


void HoI4Localisation::addEventLocalisationFromVic2(const std::string& Vic2Key,
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


void HoI4Localisation::addIdeaLocalisation(const std::string& idea, const std::optional<std::string>& localisation)
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
					LOG(LogLevel::Warning) << "Could not find localisation for " << genericIdeaStr << " in "
												  << localisationInLanguage.first;
				}
			}
			else
			{
				LOG(LogLevel::Warning) << "No generic idea localisations found for " << localisationInLanguage.first;
			}
		}
	}
}


void HoI4Localisation::addPoliticalPartyLocalisation(const std::string& Vic2Key,
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


void HoI4Localisation::addDecisionLocalisation(const std::string& key, const std::optional<std::string>& localisation)
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
					LOG(LogLevel::Warning) << "Could not find localisation for " << genericIdeaStr << " in "
												  << localisationInLanguage.first;
				}
			}
			else
			{
				LOG(LogLevel::Warning) << "No generic idea localisations found for " << localisationInLanguage.first;
			}
		}
	}
}


void HoI4Localisation::generateCustomLocalisations(HoI4::ScriptedLocalisations& scriptedLocalisations,
	 const std::set<std::string>& majorIdeologies)
{
	LOG(LogLevel::Info) << "\tGenerating custom localisations";

	std::ifstream languageReplacementsFile("DataFiles/languageReplacements.txt");
	if (!languageReplacementsFile.is_open())
	{
		return;
	}
	HoI4::AllReplacementRules replacementRules(languageReplacementsFile);
	languageReplacementsFile.close();

	for (const auto& localisationsInLanguage: countryLocalisations)
	{
		HoI4::ScriptedLocalisation masculineSingular;
		masculineSingular.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjMS");
		HoI4::ScriptedLocalisation masculinePlural;
		masculinePlural.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjMP");
		HoI4::ScriptedLocalisation feminineSingular;
		feminineSingular.setName(getLanguageCode(localisationsInLanguage.first) + "GetAdjFS");
		HoI4::ScriptedLocalisation femininePlural;
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


void HoI4Localisation::updateLocalisationText(const std::string& key,
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


std::string HoI4Localisation::getLanguageCode(const std::string& language)
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


void HoI4Localisation::insertScriptedLocalisation(const std::string& localisationKey,
	 const std::string& replacementKey,
	 HoI4::ScriptedLocalisation& scriptedLocalisation,
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
	text += "\t\ttrigger = {\n";
	text += "\t\t\tOR = { tag = " + tag + " original_tag = " + tag + " }\n";
	text += "\t\t\thas_government = " + ideology + "\n";
	text += "\t\t}\n";
	text += "\t\tlocalization_key = " + localisationKey + replacementKey + "\n";
	scriptedLocalisation.addText(text);
}