#include "src/HOI4World/HoI4FocusTree.h"
#include "external/common_items/CommonRegexes.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/HoI4Focus.h"
#include "src/HOI4World/HoI4Localisation.h"
#include "src/HOI4World/HoI4World.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/SharedFocus.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/Politics/Party.h"
#include <ranges>



namespace
{

// this is used to cache focuses that can be just loaded from a file
static std::map<std::string, HoI4Focus> loadedFocuses;


const HoI4Focus& GetLoadedFocus(std::string_view focusName)
{
	if (const auto& originalFocus = loadedFocuses.find(std::string(focusName)); originalFocus != loadedFocuses.end())
	{
		return originalFocus->second;
	}
	else
	{
		throw std::runtime_error(std::string("Could not load focus ").append(focusName));
	}
}


constexpr bool hasMaxNeighborWars(const int numWarsWithNeighbors)
{
	return numWarsWithNeighbors >= 5;
}


std::set<std::string> extractIds(const std::string& prerequisiteStr)
{
	std::set<std::string> ids;

	const std::regex prerequisite("(focus\\s*=\\s*)([A-Za-z0-9_]+)");
	const std::sregex_iterator end;
	std::sregex_iterator matchItr(prerequisiteStr.begin(), prerequisiteStr.end(), prerequisite);
	while (matchItr != end)
	{
		ids.insert((*matchItr)[2].str());
		++matchItr;
	}

	return ids;
}


size_t calculateNumCollectivistIdeologies(const std::set<std::string>& majorIdeologies)
{
	size_t numCollectivistIdeologies = 0;
	numCollectivistIdeologies += majorIdeologies.count("radical");
	numCollectivistIdeologies += majorIdeologies.count("absolutist");
	numCollectivistIdeologies += majorIdeologies.count("communism");
	numCollectivistIdeologies += majorIdeologies.count("fascism");
	return numCollectivistIdeologies;
}


std::string getMutualExclusions(const std::string& ideology, const std::set<std::string>& majorIdeologies)
{
	static const std::map<std::string, std::string> ideologyFocuses = {{"fascism", "nationalism_focus"},
		 {"communism", "internationalism_focus"},
		 {"absolutist", "absolutism_focus"},
		 {"radical", "radical_focus"}};


	std::string returnString = "= {";
	for (const auto& majorIdeology: majorIdeologies)
	{
		if (majorIdeology == ideology)
		{
			continue;
		}
		if (!ideologyFocuses.contains(majorIdeology))
		{
			continue;
		}
		returnString += " focus = " + ideologyFocuses.at(majorIdeology);
	}
	returnString += " }";
	return returnString;
}


int calculateNumEnemyOwnedCores(const std::set<int>& coreStates, const std::map<int, HoI4::State>& states)
{
	int sumUnownedCores = 0;

	for (const auto& stateId: coreStates)
	{
		const auto& stateItr = states.find(stateId);
		if (stateItr == states.end())
		{
			continue;
		}
		const auto& state = stateItr->second;
		sumUnownedCores += std::min(static_cast<int>(state.getProvinces().size()), 10);
	}

	return sumUnownedCores;
}


std::map<std::string, std::set<int>> determineWarTargets(const HoI4::Country& theCountry,
	 const std::set<int>& stateIds,
	 const std::map<int, HoI4::State>& states)
{
	std::map<std::string, std::set<int>> targets;

	for (const auto& stateID: stateIds)
	{
		const auto& stateItr = states.find(stateID);
		if (stateItr == states.end())
		{
			continue;
		}
		const auto& state = stateItr->second;
		if (const auto& owner = state.getOwner(); owner != theCountry.getTag())
		{
			if (theCountry.isEligibleEnemy(owner))
			{
				targets[owner].emplace(stateID);
			}
		}
	}

	return targets;
}


double getMaxConquerValue(const std::vector<HoI4::AIStrategy>& conquerStrategies)
{
	const auto& maxConquerValueItr =
		 std::ranges::max_element(conquerStrategies, [](const HoI4::AIStrategy& a, const HoI4::AIStrategy& b) {
			 return a.getValue() < b.getValue();
		 });
	return maxConquerValueItr->getValue();
}

} // namespace



HoI4FocusTree::HoI4FocusTree(const HoI4::Country& country): dstCountryTag(country.getTag())
{
}


void HoI4FocusTree::addGenericFocusTree(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\t\tCreating generic focus tree";
	confirmLoadedFocuses();

	auto numCollectivistIdeologies = static_cast<int>(calculateNumCollectivistIdeologies(majorIdeologies));

	auto politicalEffortFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("political_effort"));
	politicalEffortFocus->xPos = static_cast<int>((numCollectivistIdeologies * 1.5) + 16);
	sharedFocuses.push_back(politicalEffortFocus);

	if (numCollectivistIdeologies > 0)
	{
		auto collectivistEthosFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("collectivist_ethos"));
		std::string governments;
		for (const auto& majorIdeology: majorIdeologies)
		{
			if (majorIdeology == "democratic")
			{
				continue;
			}
			if (majorIdeology == *majorIdeologies.begin())
			{
				governments += "has_government = " + majorIdeology + "\n";
			}
			else
			{
				governments += "\t\t\thas_government = " + majorIdeology + "\n";
			}
		}
		collectivistEthosFocus->updateFocusElement(collectivistEthosFocus->available, "$GOVERNMENTS", governments);
		collectivistEthosFocus->xPos = -(numCollectivistIdeologies / 2) - 1;
		std::string idea;
		if (majorIdeologies.contains("democratic"))
		{
			idea = "collectivist_ethos_focus_democratic";
		}
		else
		{
			idea = "collectivist_ethos_focus_neutral";
		}
		collectivistEthosFocus->updateFocusElement(collectivistEthosFocus->completionReward, "$IDEA", idea);
		sharedFocuses.push_back(collectivistEthosFocus);

		std::string ideologicalFanaticismPrerequisites;
		int relativePosition = 1 - numCollectivistIdeologies;
		if (majorIdeologies.contains("fascism"))
		{
			addFascistGenericFocuses(relativePosition, majorIdeologies);
			ideologicalFanaticismPrerequisites += " focus = paramilitarism";
			relativePosition += 2;
		}
		if (majorIdeologies.contains("communism"))
		{
			addCommunistGenericFocuses(relativePosition, majorIdeologies);
			ideologicalFanaticismPrerequisites += " focus = political_commissars";
			relativePosition += 2;
		}
		if (majorIdeologies.contains("absolutist"))
		{
			addAbsolutistGenericFocuses(relativePosition, majorIdeologies);
			ideologicalFanaticismPrerequisites += " focus = historical_claims_focus";
			relativePosition += 2;
		}
		if (majorIdeologies.contains("radical"))
		{
			addRadicalGenericFocuses(relativePosition, majorIdeologies);
			ideologicalFanaticismPrerequisites += " focus = army_provides_focus";
		}

		auto ideologicalFanaticismFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("ideological_fanaticism"));
		ideologicalFanaticismFocus->prerequisites.clear();
		ideologicalFanaticismFocus->prerequisites.push_back("= {" + ideologicalFanaticismPrerequisites + " }");
		ideologicalFanaticismFocus->xPos = 0;
		ideologicalFanaticismFocus->yPos = 5;
		ideologicalFanaticismFocus->relativePositionId = "collectivist_ethos";
		sharedFocuses.push_back(ideologicalFanaticismFocus);
	}

	auto libertyEthosFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("liberty_ethos"));
	if (numCollectivistIdeologies == 0)
	{
		libertyEthosFocus->mutuallyExclusive.clear();
	}
	if (!majorIdeologies.contains("democratic"))
	{
		libertyEthosFocus->available = "= {\n";
		libertyEthosFocus->available += "\t\t\thas_government = neutrality\n";
		libertyEthosFocus->available += "\t\t}";

		libertyEthosFocus->completionReward = "= {\n";
		libertyEthosFocus->completionReward += "\tadd_ideas = liberty_ethos_focus_neutral\n";
		libertyEthosFocus->completionReward += "}";
	}
	libertyEthosFocus->xPos = (numCollectivistIdeologies + 1) / 2;
	std::string governments;
	for (const auto& majorIdeology: majorIdeologies)
	{
		if (majorIdeology == *majorIdeologies.begin())
		{
			governments += "has_government = " + majorIdeology + "\n";
		}
		else
		{
			governments += "\t\t\t\t\thas_government = " + majorIdeology + "\n";
		}
	}
	libertyEthosFocus->updateFocusElement(libertyEthosFocus->aiWillDo, "$GOVERNMENTS", governments);
	std::string noMajorDemocraticNeighbor;
	noMajorDemocraticNeighbor += "NOT = {\n";
	noMajorDemocraticNeighbor += "\t\t\t\tany_neighbor_country = {\n";
	noMajorDemocraticNeighbor += "\t\t\t\t\tis_major = yes\n";
	noMajorDemocraticNeighbor += "\t\t\t\t\thas_government = democratic\n";
	noMajorDemocraticNeighbor += "\t\t\t\t}\n";
	noMajorDemocraticNeighbor += "\t\t\t}\n";
	libertyEthosFocus->updateFocusElement(libertyEthosFocus->aiWillDo,
		 "#NO_MAJOR_DEMOCRATIC_NEIGHBOR",
		 noMajorDemocraticNeighbor,
		 majorIdeologies.contains("democratic"));
	sharedFocuses.push_back(libertyEthosFocus);

	auto neutralityFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("neutrality_focus"));
	if (!majorIdeologies.contains("democratic"))
	{
		neutralityFocus->mutuallyExclusive.clear();
	}
	neutralityFocus->aiWillDo = "= {\n";
	neutralityFocus->aiWillDo += "\t\t\tfactor = 1\n";
	neutralityFocus->aiWillDo += "\t\t}";
	sharedFocuses.push_back(neutralityFocus);

	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("deterrence")));

	if (majorIdeologies.contains("democratic"))
	{
		sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("interventionism_focus")));
		sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("volunteer_corps")));
		sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("foreign_expeditions")));
	}

	auto whyWeFightFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("why_we_fight"));
	if (!majorIdeologies.contains("democratic"))
	{
		whyWeFightFocus->prerequisites.clear();
		whyWeFightFocus->prerequisites.push_back("= { focus = deterrence }");
	}
	sharedFocuses.push_back(whyWeFightFocus);

	auto technologySharingFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("technology_sharing"));
	if (numCollectivistIdeologies == 0)
	{
		technologySharingFocus->prerequisites.clear();
		technologySharingFocus->prerequisites.push_back("= { focus = why_we_fight }");
	}
	technologySharingFocus->xPos = numCollectivistIdeologies;
	sharedFocuses.push_back(technologySharingFocus);

	nextFreeColumn = static_cast<int>(numCollectivistIdeologies * 1.5) + ((numCollectivistIdeologies + 1) / 2) + 20;
}


void HoI4FocusTree::confirmLoadedFocuses()
{
	if (loadedFocuses.empty())
	{
		registerKeyword("focus_tree", [this](std::istream& theStream) {
		});
		registerRegex("focus|shared_focus", [this](const std::string& unused, std::istream& theStream) {
			HoI4Focus newFocus(theStream);
			loadedFocuses.insert(make_pair(newFocus.id, newFocus));
		});
		registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

		parseFile("Configurables/converterFocuses.txt");
		for (const auto& file: commonItems::GetAllFilesInFolder("Configurables/CustomizedFocusBranches"))
		{
			parseFile("Configurables/CustomizedFocusBranches/" + file);
		}
		clearRegisteredKeywords();

		createBranches();
	}
}


void HoI4FocusTree::loadFocuses(const std::string& branch)
{
	registerKeyword("focus_tree", [this](std::istream& theStream) {
	});
	registerRegex("focus|shared_focus", [this](const std::string& unused, std::istream& theStream) {
		HoI4Focus newFocus(theStream);
		loadedFocuses.insert(make_pair(newFocus.id, newFocus));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("Configurables/CustomizedFocusBranches/" + branch + ".txt");
	clearRegisteredKeywords();

	createBranches();
}


void HoI4FocusTree::addBranch(const std::string& tag, const std::string& branch, HoI4::OnActions& onActions)
{
	loadFocuses(branch);

	if (!branches.contains(branch))
	{
		return;
	}
	const auto& branchFocuses = branches.at(branch);
	std::map<int, std::vector<std::string>> branchLevels;
	for (const auto& [focus, level]: branchFocuses)
	{
		branchLevels[level].push_back(focus);
	}

	int branchWidth = 0;
	for (const auto& levelFocuses: branchLevels | std::views::values)
	{
		for (const auto& focus: levelFocuses)
		{
			const auto& newFocus = std::make_shared<HoI4Focus>(GetLoadedFocus(focus));
			if (focus == branch)
			{
				branchWidth = newFocus->xPos;
				newFocus->xPos = nextFreeColumn + branchWidth / 2;
				onActions.addFocusEvent(tag, focus);
			}
			focuses.push_back(newFocus);
		}
	}
	nextFreeColumn += branchWidth + 2;
}


void HoI4FocusTree::createBranches()
{
	int branchLevel = 0;
	for (const auto& [id, focus]: loadedFocuses)
	{
		if (!focus.prerequisites.empty())
		{
			continue;
		}
		branches[id].insert(std::make_pair(id, branchLevel));
		addChildrenToBranch(id, id, branchLevel);
	}
}


void HoI4FocusTree::addChildrenToBranch(const std::string& head, const std::string& id, int branchLevel)
{
	branchLevel++;
	for (const auto& [childId, childFocus]: loadedFocuses)
	{
		if (branches[head].contains(childId))
		{
			continue;
		}
		for (const auto& prerequisiteStr: childFocus.prerequisites)
		{
			const auto& prerequisites = extractIds(prerequisiteStr);
			if (prerequisites.contains(id))
			{
				branches[head].insert(std::make_pair(childId, branchLevel));
				addChildrenToBranch(head, childId, branchLevel);
			}
		}
	}
}


void HoI4FocusTree::addFascistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies)
{
	const auto nationalismFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("nationalism_focus"));
	nationalismFocus->mutuallyExclusive = getMutualExclusions("fascism", majorIdeologies);
	nationalismFocus->xPos = relativePosition;
	sharedFocuses.push_back(nationalismFocus);

	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("militarism")));

	auto militaryYouthFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("military_youth"));
	militaryYouthFocus->completionReward = "= {\n";
	militaryYouthFocus->completionReward += "\t\t\tadd_ideas = military_youth_focus\n";
	for (const auto& ideology: majorIdeologies)
	{
		militaryYouthFocus->completionReward += "\t\t\tif = {\n";
		militaryYouthFocus->completionReward += "\t\t\t\tlimit = { has_government = " + ideology + " }\n";
		militaryYouthFocus->completionReward += "\t\t\t\tadd_popularity = {\n";
		militaryYouthFocus->completionReward += "\t\t\t\t\tideology = " + ideology + "\n";
		militaryYouthFocus->completionReward += "\t\t\t\t\tpopularity = 0.2\n";
		militaryYouthFocus->completionReward += "\t\t\t\t}\n";
		militaryYouthFocus->completionReward += "\t\t\t}\n";
	}
	militaryYouthFocus->completionReward += "\t\t}";
	sharedFocuses.push_back(militaryYouthFocus);

	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("paramilitarism")));
}


void HoI4FocusTree::addCommunistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies)
{
	const auto internationalismFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("internationalism_focus"));
	internationalismFocus->mutuallyExclusive = getMutualExclusions("communism", majorIdeologies);
	internationalismFocus->xPos = relativePosition;
	sharedFocuses.push_back(internationalismFocus);

	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("political_correctness")));
	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("indoctrination_focus")));
	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("political_commissars")));
}


void HoI4FocusTree::addAbsolutistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies)
{
	const auto absolutismFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("absolutism_focus"));
	absolutismFocus->mutuallyExclusive = getMutualExclusions("absolutist", majorIdeologies);
	absolutismFocus->xPos = relativePosition;
	sharedFocuses.push_back(absolutismFocus);

	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("royal_dictatorship_focus")));
	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("royal_army_tradition_focus")));
	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("historical_claims_focus")));
}


void HoI4FocusTree::addRadicalGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies)
{
	const auto radicalFocus = std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("radical_focus"));
	radicalFocus->mutuallyExclusive = getMutualExclusions("radical", majorIdeologies);
	radicalFocus->xPos = relativePosition;
	sharedFocuses.push_back(radicalFocus);

	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("private_channels_focus")));
	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("hardfought_market_focus")));
	sharedFocuses.push_back(std::make_shared<HoI4::SharedFocus>(GetLoadedFocus("army_provides_focus")));
}


std::unique_ptr<HoI4FocusTree> HoI4FocusTree::makeCustomizedCopy(const HoI4::Country& country) const
{
	HoI4FocusTree newFocusTree(country);

	for (const auto& focus: focuses)
	{
		newFocusTree.addFocus(focus->makeCustomizedCopy(newFocusTree.dstCountryTag));
	}
	newFocusTree.setNextFreeColumn(nextFreeColumn);
	newFocusTree.emptyFocusTree = emptyFocusTree;

	return std::make_unique<HoI4FocusTree>(std::move(newFocusTree));
}


void HoI4FocusTree::addDemocracyNationalFocuses(const HoI4::Country& home,
	 const std::vector<std::shared_ptr<HoI4::Country>>& countriesToContain,
	 HoI4::Localisation& hoi4Localisations)
{
	double WTModifier = 1;
	if (home.getGovernmentIdeology() == "democratic")
	{
		if (const auto& rulingParty = home.getRulingParty(); rulingParty != std::nullopt)
		{
			const auto warPolicy = rulingParty->getWarPolicy();
			if (warPolicy == "jingoism")
			{
				WTModifier = 0;
			}
			if (warPolicy == "pro_military")
			{
				WTModifier = 0.25;
			}
			if (warPolicy == "anti_military")
			{
				WTModifier = 0.5;
			}
			if (warPolicy == "pacifism" || warPolicy == "pacifist")
			{
				WTModifier = 0.5;
			}
		}
	}

	auto warPropFocus = GetLoadedFocus("WarProp").makeCustomizedCopy(home.getTag());
	warPropFocus->updateFocusElement(warPropFocus->available, "$WTMODIFIER", std::to_string(0.20 * WTModifier / 1000));
	warPropFocus->xPos = nextFreeColumn + static_cast<int>(countriesToContain.size()) - 1;
	focuses.push_back(warPropFocus);

	auto prepInterFocus = GetLoadedFocus("PrepInter").makeCustomizedCopy(home.getTag());
	prepInterFocus->updateFocusElement(prepInterFocus->available,
		 "$WTMODIFIER",
		 std::to_string(0.30 * WTModifier / 1000));
	focuses.push_back(prepInterFocus);

	auto limFocus = GetLoadedFocus("Lim").makeCustomizedCopy(home.getTag());
	limFocus->updateFocusElement(limFocus->available, "$WTMODIFIER", std::to_string(0.50 * WTModifier / 1000));
	focuses.push_back(limFocus);

	auto relativePos = 1 - static_cast<int>(countriesToContain.size());
	for (const auto& country: countriesToContain)
	{
		const auto tag = country->getTag();

		const auto& truceUntil = home.getTruceUntil(tag);
		auto warPlanFocus = GetLoadedFocus("WarPlan").makeTargetedCopy(home.getTag(), tag, hoi4Localisations);
		warPlanFocus->updateFocusElement(warPlanFocus->bypass, "$TARGET", tag);
		warPlanFocus->xPos = relativePos;
		warPlanFocus->updateFocusElement(warPlanFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		warPlanFocus->updateFocusElement(warPlanFocus->available, "$TARGET", tag);
		focuses.push_back(warPlanFocus);

		auto embargoFocus = GetLoadedFocus("Embargo").makeTargetedCopy(home.getTag(), tag, hoi4Localisations);
		embargoFocus->prerequisites.clear();
		embargoFocus->prerequisites.push_back("= { focus =  WarPlan" + home.getTag() + tag + " }");
		embargoFocus->updateFocusElement(embargoFocus->bypass, "$TARGET", tag);
		embargoFocus->relativePositionId += tag;
		embargoFocus->updateFocusElement(embargoFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		embargoFocus->updateFocusElement(embargoFocus->available, "$TARGET", tag);
		embargoFocus->updateFocusElement(embargoFocus->completionReward, "$TARGET", tag);
		focuses.push_back(embargoFocus);

		auto warFocus = GetLoadedFocus("WAR").makeTargetedCopy(home.getTag(), tag, hoi4Localisations);
		warFocus->prerequisites.clear();
		warFocus->prerequisites.push_back("= { focus =  Embargo" + home.getTag() + tag + " }");
		warFocus->updateFocusElement(warFocus->bypass, "$TARGET", tag);
		warFocus->relativePositionId += tag;
		warFocus->updateFocusElement(warFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		warFocus->updateFocusElement(warFocus->available, "$TARGET", tag);
		warFocus->updateFocusElement(warFocus->completionReward, "$TARGET", tag);
		focuses.push_back(warFocus);

		relativePos += 2;
	}
	nextFreeColumn += 2 * static_cast<int>(countriesToContain.size());
}


void HoI4FocusTree::addAbsolutistEmpireNationalFocuses(const HoI4::Country& home,
	 const std::vector<std::shared_ptr<HoI4::Country>>& targetColonies,
	 const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets,
	 HoI4::Localisation& hoi4Localisations)
{
	const auto& homeTag = home.getTag();

	auto empireGloryFocus = GetLoadedFocus("EmpireGlory").makeCustomizedCopy(homeTag);
	empireGloryFocus->xPos = nextFreeColumn + 5;
	empireGloryFocus->yPos = 0;
	focuses.push_back(empireGloryFocus);

	auto strengthenColoniesFocus = GetLoadedFocus("StrengthenColonies").makeCustomizedCopy(homeTag);
	strengthenColoniesFocus->relativePositionId = "EmpireGlory" + homeTag;
	strengthenColoniesFocus->xPos = -1;
	strengthenColoniesFocus->yPos = 1;
	if (targetColonies.empty() && !annexationTargets.empty())
	{
		strengthenColoniesFocus->aiWillDo = "= { factor = 0 }";
	}
	focuses.push_back(strengthenColoniesFocus);

	auto strengthenHomeFocus = GetLoadedFocus("StrengthenHome").makeCustomizedCopy(homeTag);
	strengthenHomeFocus->relativePositionId = "EmpireGlory" + homeTag;
	strengthenHomeFocus->xPos = 1;
	strengthenHomeFocus->yPos = 1;
	if (annexationTargets.empty() && !targetColonies.empty())
	{
		strengthenHomeFocus->aiWillDo = "= { factor = 0 }";
	}
	focuses.push_back(strengthenHomeFocus);

	auto colonialIndFocus = GetLoadedFocus("ColonialInd").makeCustomizedCopy(homeTag);
	colonialIndFocus->relativePositionId = "StrengthenColonies" + homeTag;
	colonialIndFocus->xPos = -2;
	colonialIndFocus->yPos = 1;
	focuses.push_back(colonialIndFocus);

	auto colonialHwyFocus = GetLoadedFocus("ColonialHwy").makeCustomizedCopy(homeTag);
	colonialHwyFocus->relativePositionId = "ColonialInd" + homeTag;
	colonialHwyFocus->xPos = -2;
	colonialHwyFocus->yPos = 1;
	focuses.push_back(colonialHwyFocus);

	auto resourceFacFocus = GetLoadedFocus("ResourceFac").makeCustomizedCopy(homeTag);
	resourceFacFocus->relativePositionId = "ColonialInd" + homeTag;
	resourceFacFocus->xPos = 0;
	resourceFacFocus->yPos = 1;
	focuses.push_back(resourceFacFocus);

	auto colonialArmyFocus = GetLoadedFocus("ColonialArmy").makeCustomizedCopy(homeTag);
	colonialArmyFocus->relativePositionId = "StrengthenColonies" + homeTag;
	colonialArmyFocus->xPos = 0;
	colonialArmyFocus->yPos = 1;
	focuses.push_back(colonialArmyFocus);

	// establish protectorate
	if (targetColonies.size() >= 1)
	{
		const auto& target = targetColonies.front();

		auto protectorateFocus =
			 GetLoadedFocus("Protectorate").makeTargetedCopy(homeTag, target->getTag(), hoi4Localisations);
		protectorateFocus->id = "Protectorate" + homeTag + target->getTag();
		const auto& truceUntil = home.getTruceUntil(target->getTag());
		protectorateFocus->updateFocusElement(protectorateFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		protectorateFocus->updateFocusElement(protectorateFocus->available, "$TARGET", target->getTag());
		protectorateFocus->prerequisites.push_back("= { focus = ColonialArmy" + homeTag + " }");
		protectorateFocus->relativePositionId = "ColonialArmy" + homeTag;
		protectorateFocus->xPos = 0;
		protectorateFocus->yPos = 1;
		protectorateFocus->updateFocusElement(protectorateFocus->bypass, "$TARGET", target->getTag());
		protectorateFocus->updateFocusElement(protectorateFocus->aiWillDo, "$TARGET", target->getTag());
		protectorateFocus->updateFocusElement(protectorateFocus->completionReward, "$TARGET", target->getTag());
		focuses.push_back(protectorateFocus);
	}
	if (targetColonies.size() >= 2)
	{
		const auto& target = targetColonies.back();

		auto protectorateFocus =
			 GetLoadedFocus("Protectorate").makeTargetedCopy(homeTag, target->getTag(), hoi4Localisations);
		protectorateFocus->id = "Protectorate" + homeTag + target->getTag();
		const auto& truceUntil = home.getTruceUntil(target->getTag());
		protectorateFocus->updateFocusElement(protectorateFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		protectorateFocus->updateFocusElement(protectorateFocus->available, "$TARGET", target->getTag());
		protectorateFocus->prerequisites.push_back(
			 "= { focus = Protectorate" + homeTag + targetColonies.front()->getTag() + " }");
		protectorateFocus->relativePositionId = "Protectorate" + homeTag + targetColonies.front()->getTag();
		protectorateFocus->xPos = 0;
		protectorateFocus->yPos = 1;
		protectorateFocus->updateFocusElement(protectorateFocus->bypass, "$TARGET", target->getTag());
		protectorateFocus->updateFocusElement(protectorateFocus->aiWillDo, "$TARGET", target->getTag());
		protectorateFocus->updateFocusElement(protectorateFocus->aiWillDo, "factor = 10", "factor = 5");
		protectorateFocus->updateFocusElement(protectorateFocus->completionReward, "$TARGET", target->getTag());
		focuses.push_back(protectorateFocus);
	}

	auto tradeEmpireFocus = GetLoadedFocus("TradeEmpire").makeCustomizedCopy(homeTag);
	tradeEmpireFocus->relativePositionId = "ColonialInd" + homeTag;
	tradeEmpireFocus->xPos = -1;
	tradeEmpireFocus->yPos = 2;
	focuses.push_back(tradeEmpireFocus);

	auto indHomeFocus = GetLoadedFocus("IndHome").makeCustomizedCopy(homeTag);
	indHomeFocus->relativePositionId = "StrengthenHome" + homeTag;
	indHomeFocus->xPos = 1;
	indHomeFocus->yPos = 1;
	focuses.push_back(indHomeFocus);

	auto nationalHwyFocus = GetLoadedFocus("NationalHwy").makeCustomizedCopy(homeTag);
	nationalHwyFocus->relativePositionId = "IndHome" + homeTag;
	nationalHwyFocus->xPos = -1;
	nationalHwyFocus->yPos = 1;
	focuses.push_back(nationalHwyFocus);

	auto natCollegeFocus = GetLoadedFocus("NatCollege").makeCustomizedCopy(homeTag);
	natCollegeFocus->relativePositionId = "IndHome" + homeTag;
	natCollegeFocus->xPos = 1;
	natCollegeFocus->yPos = 1;
	focuses.push_back(natCollegeFocus);

	auto militaryBuildupFocus = GetLoadedFocus("MilitaryBuildup").makeCustomizedCopy(homeTag);
	militaryBuildupFocus->relativePositionId = "IndHome" + homeTag;
	militaryBuildupFocus->xPos = 2;
	militaryBuildupFocus->yPos = 2;
	focuses.push_back(militaryBuildupFocus);

	auto prepTheBorderFocus = GetLoadedFocus("PrepTheBorder").makeCustomizedCopy(homeTag);
	prepTheBorderFocus->relativePositionId = "StrengthenHome" + homeTag;
	prepTheBorderFocus->xPos = 4;
	prepTheBorderFocus->yPos = 1;
	focuses.push_back(prepTheBorderFocus);

	auto natSpiritFocus = GetLoadedFocus("NatSpirit").makeCustomizedCopy(homeTag);
	natSpiritFocus->relativePositionId = "PrepTheBorder" + homeTag;
	natSpiritFocus->xPos = 0;
	natSpiritFocus->yPos = 1;
	focuses.push_back(natSpiritFocus);

	// ANNEX
	if (annexationTargets.size() >= 1)
	{
		const auto& target = annexationTargets.front();

		auto annexFocus = GetLoadedFocus("Annex").makeTargetedCopy(homeTag, target->getTag(), hoi4Localisations);
		annexFocus->id = "Annex" + homeTag + target->getTag();
		const auto& truceUntil = home.getTruceUntil(target->getTag());
		annexFocus->updateFocusElement(annexFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		annexFocus->updateFocusElement(annexFocus->available, "$TARGET", target->getTag());
		annexFocus->prerequisites.push_back("= { focus = PrepTheBorder" + homeTag + " }");
		annexFocus->relativePositionId = "PrepTheBorder" + homeTag;
		annexFocus->xPos = 2;
		annexFocus->yPos = 1;
		annexFocus->updateFocusElement(annexFocus->bypass, "$TARGET", target->getTag());
		annexFocus->updateFocusElement(annexFocus->aiWillDo, "$TARGET", target->getTag());
		annexFocus->updateFocusElement(annexFocus->completionReward, "$TARGET", target->getTag());
		focuses.push_back(annexFocus);
	}
	if (annexationTargets.size() >= 2)
	{
		const auto& target = annexationTargets.back();

		auto annexFocus = GetLoadedFocus("Annex").makeTargetedCopy(homeTag, target->getTag(), hoi4Localisations);
		annexFocus->id = "Annex" + homeTag + target->getTag();
		const auto& truceUntil = home.getTruceUntil(target->getTag());
		annexFocus->updateFocusElement(annexFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		annexFocus->updateFocusElement(annexFocus->available, "$TARGET", target->getTag());
		annexFocus->prerequisites.push_back("= { focus = NatSpirit" + home.getTag() + " }");
		annexFocus->relativePositionId = "NatSpirit" + homeTag;
		annexFocus->xPos = 1;
		annexFocus->yPos = 1;
		annexFocus->updateFocusElement(annexFocus->available, "$TARGET", target->getTag());
		annexFocus->updateFocusElement(annexFocus->bypass, "$TARGET", target->getTag());
		annexFocus->updateFocusElement(annexFocus->aiWillDo, "$TARGET", target->getTag());
		annexFocus->updateFocusElement(annexFocus->completionReward, "$TARGET", target->getTag());
		focuses.push_back(annexFocus);
	}
	nextFreeColumn += 2;
}


void HoI4FocusTree::addCommunistCoupBranch(const HoI4::Country& home,
	 const std::vector<std::shared_ptr<HoI4::Country>>& coupTargets,
	 const std::set<std::string>& majorIdeologies,
	 HoI4::Localisation& hoi4Localisations)
{
	if (coupTargets.empty())
	{
		return;
	}

	const auto& homeTag = home.getTag();

	const int coupTargetsNum = std::min(static_cast<int>(coupTargets.size()), 2);

	auto homeOfTheRevolutionFocus = GetLoadedFocus("Home_of_Revolution").makeCustomizedCopy(homeTag);
	homeOfTheRevolutionFocus->xPos = nextFreeColumn + coupTargetsNum - 1;
	homeOfTheRevolutionFocus->yPos = 0;
	focuses.push_back(homeOfTheRevolutionFocus);

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i >= coupTargets.size())
		{
			continue;
		}

		auto influenceFocus =
			 GetLoadedFocus("Influence_").makeTargetedCopy(homeTag, coupTargets[i]->getTag(), hoi4Localisations);
		influenceFocus->id = "Influence_" + coupTargets[i]->getTag() + "_" + homeTag;
		influenceFocus->xPos = nextFreeColumn + i * 2;
		influenceFocus->yPos = 1;
		influenceFocus->completionReward += "= {\n";
		influenceFocus->completionReward += "\t\t\t" + coupTargets[i]->getTag() + " = {\n";
		std::map<std::string, std::string> ideologyIdeas = {{"fascism", "fascist_influence"},
			 {"communism", "communist_influence"},
			 {"democratic", "democratic_influence"},
			 {"absolutist", "absolutist_influence"},
			 {"radical", "radical_influence"}};
		for (const auto& majorIdeology: majorIdeologies)
		{
			if (!ideologyIdeas.contains(majorIdeology))
			{
				continue;
			}
			influenceFocus->completionReward += "\t\t\t\tif = {\n";
			influenceFocus->completionReward += "\t\t\t\t\tlimit = {\n";
			influenceFocus->completionReward += "\t\t\t\t\t\tROOT = {\n";
			influenceFocus->completionReward += "\t\t\t\t\t\t\thas_government = " + majorIdeology + "\n";
			influenceFocus->completionReward += "\t\t\t\t\t\t}\n";
			influenceFocus->completionReward += "\t\t\t\t\t}\n";
			influenceFocus->completionReward += "\t\t\t\t\tadd_ideas = " + ideologyIdeas[majorIdeology] + "\n";
			influenceFocus->completionReward += "\t\t\t\t}\n";
		}
		influenceFocus->completionReward += "\t\t\t\tcountry_event = { id = generic.1 }\n";
		influenceFocus->completionReward += "\t\t\t}\n";
		influenceFocus->completionReward += "\t\t}";
		focuses.push_back(influenceFocus);

		auto coupFocus = GetLoadedFocus("Coup_").makeTargetedCopy(homeTag, coupTargets[i]->getTag(), hoi4Localisations);
		coupFocus->id = "Coup_" + coupTargets[i]->getTag() + "_" + homeTag;
		coupFocus->prerequisites.push_back("= { focus = Influence_" + coupTargets[i]->getTag() + "_" + homeTag + " }");
		coupFocus->relativePositionId = "Influence_" + coupTargets[i]->getTag() + "_" + homeTag;
		coupFocus->xPos = 0;
		coupFocus->yPos = 1;
		coupFocus->updateFocusElement(coupFocus->available, "$TARGET", coupTargets[i]->getTag());
		coupFocus->updateFocusElement(coupFocus->completionReward, "$TARGET", coupTargets[i]->getTag());
		focuses.push_back(coupFocus);
	}
	nextFreeColumn += 2 * coupTargetsNum;
}


void HoI4FocusTree::addCommunistWarBranch(const HoI4::Country& home,
	 std::vector<std::shared_ptr<HoI4::Country>> warTargets,
	 HoI4::Events& events,
	 HoI4::Localisation& hoi4Localisations)
{
	if (warTargets.empty())
	{
		return;
	}

	const auto& tag = home.getTag();

	if (warTargets.size() > 3)
	{
		warTargets.resize(3);
	}
	const int warTargetsNum = static_cast<int>(warTargets.size());

	auto strengthComFocus = GetLoadedFocus("StrengthCom").makeCustomizedCopy(tag);
	strengthComFocus->xPos = nextFreeColumn + warTargetsNum - 1;
	strengthComFocus->yPos = 0;
	focuses.push_back(strengthComFocus);

	auto interComPresFocus = GetLoadedFocus("Inter_Com_Pres").makeCustomizedCopy(tag);
	interComPresFocus->relativePositionId = "StrengthCom" + tag;
	interComPresFocus->xPos = 0;
	interComPresFocus->yPos = 1;
	interComPresFocus->updateFocusElement(interComPresFocus->completionReward, "$TEXT", interComPresFocus->text);
	// FIXME
	// maybe add some claims?
	focuses.push_back(interComPresFocus);

	for (const auto& warTarget: warTargets)
	{
		const auto& possibleWarTargetCountryName = warTarget->getName();
		std::string warTargetCountryName;
		if (possibleWarTargetCountryName)
		{
			warTargetCountryName = *possibleWarTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine war target country name for communist war focuses";
			warTargetCountryName.clear();
		}

		const auto& warTargetTag = warTarget->getTag();

		auto warFocus = GetLoadedFocus("War").makeTargetedCopy(tag, warTargetTag, hoi4Localisations);
		warFocus->id = std::string("War").append(warTargetTag).append(tag);
		auto dateAvailable = date("1938.1.1");
		if (const auto& relations = home.getRelations(warTargetTag); relations)
		{
			dateAvailable.increaseByMonths((200 + relations->getRelations()) / 16);
		}
		if (const auto& truceUntil = home.getTruceUntil(warTargetTag); truceUntil && *truceUntil > dateAvailable)
		{
			warFocus->updateFocusElement(warFocus->available, "#DATE", "date > " + truceUntil->toString());
		}
		else
		{
			warFocus->updateFocusElement(warFocus->available, "#DATE", "date > " + dateAvailable.toString() + "\n");
		}
		warFocus->xPos = nextFreeColumn;
		warFocus->yPos = 2;
		warFocus->updateFocusElement(warFocus->bypass, "$TARGET", warTargetTag);
		warFocus->updateFocusElement(warFocus->aiWillDo, "$TARGET", warTargetTag);
		std::string warWithTargets;
		if (warTargets.size() > 1)
		{
			for (const auto& otherTarget: warTargets)
			{
				if (otherTarget->getTag() == warTargetTag)
				{
					continue;
				}
				if (warWithTargets.empty())
				{
					warWithTargets = "has_war_with = " + otherTarget->getTag() + "\n";
				}
				else
				{
					warWithTargets += "\t\t\t\thas_war_with = " + otherTarget->getTag() + "\n";
				}
			}
		}
		warFocus->updateFocusElement(warFocus->aiWillDo, "#WAR_WITH_TARGETS", warWithTargets);
		warFocus->updateFocusElement(warFocus->completionReward, "$TARGETNAME", warTargetCountryName);
		warFocus->updateFocusElement(warFocus->completionReward, "$TARGET", warTargetTag);
		focuses.push_back(warFocus);
		nextFreeColumn += 2;
	}
}


void HoI4FocusTree::addFascistAnnexationBranch(const HoI4::Country& home,
	 const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets,
	 const size_t numSudetenTargets,
	 HoI4::Events& events,
	 HoI4::Localisation& hoi4Localisations)
{
	const auto& homeTag = home.getTag();

	// The Following 'if' statement prevents converter from generating focuses if annexationTargets.size > 1
	// Keep this 'if' statement off until we figure out how to handle Fascist NF's
	auto theThirdWayFocus = GetLoadedFocus("The_third_way").makeCustomizedCopy(homeTag);
	const auto& maxWidth = static_cast<int>(std::max(annexationTargets.size(), numSudetenTargets));
	theThirdWayFocus->xPos = nextFreeColumn + maxWidth - 1;
	theThirdWayFocus->yPos = 0;
	nextFreeColumn += 2 * maxWidth;
	// FIXME
	// Need to get Drift Defense to work
	// in modified generic focus? (tk)
	// theThirdWayFocus->completionReward += "\t\t\tdrift_defence_factor = 0.5\n";
	theThirdWayFocus->updateFocusElement(theThirdWayFocus->completionReward, "$TEXT", theThirdWayFocus->text);
	focuses.push_back(theThirdWayFocus);

	auto milMarchFocus = GetLoadedFocus("mil_march").makeCustomizedCopy(homeTag);
	milMarchFocus->relativePositionId = "The_third_way" + homeTag;
	milMarchFocus->xPos = 0;
	milMarchFocus->yPos = 1;
	focuses.push_back(milMarchFocus);

	int annexationFreeColumn = 1 - static_cast<int>(annexationTargets.size());
	for (const auto& target: annexationTargets)
	{
		const auto& possibleAnnexationTargetCountryName = target->getName();
		std::string annexationTargetCountryName;
		if (possibleAnnexationTargetCountryName)
		{
			annexationTargetCountryName = *possibleAnnexationTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine annexation target country name for fascist annexation focuses";
			annexationTargetCountryName.clear();
		}

		const auto& targetTag = target->getTag();

		auto anschlussFocus = GetLoadedFocus("_anschluss_").makeTargetedCopy(homeTag, targetTag, hoi4Localisations);
		anschlussFocus->id = homeTag + "_anschluss_" + targetTag;
		date dateAvailable = date("1937.1.1");
		if (const auto& relations = home.getRelations(targetTag); relations)
		{
			dateAvailable.increaseByMonths((200 + relations->getRelations()) / 16);
		}
		if (const auto& truceUntil = home.getTruceUntil(targetTag); truceUntil && *truceUntil > dateAvailable)
		{
			anschlussFocus->updateFocusElement(anschlussFocus->available, "#DATE", "date > " + truceUntil->toString());
		}
		else
		{
			anschlussFocus->updateFocusElement(anschlussFocus->available,
				 "#DATE",
				 "date > " + dateAvailable.toString() + "\n");
		}
		anschlussFocus->updateFocusElement(anschlussFocus->available, "$TARGET", targetTag);
		anschlussFocus->xPos = annexationFreeColumn;
		anschlussFocus->yPos = 1;
		anschlussFocus->updateFocusElement(anschlussFocus->completionReward, "$TARGETNAME", annexationTargetCountryName);
		anschlussFocus->updateFocusElement(anschlussFocus->completionReward, "$TARGET", targetTag);
		anschlussFocus->updateFocusElement(anschlussFocus->completionReward,
			 "$EVENTID",
			 std::to_string(events.getCurrentNationFocusEventNum()));
		focuses.push_back(anschlussFocus);
		annexationFreeColumn += 2;

		events.createAnnexEvent(home, *target);
	}
}


void HoI4FocusTree::addFascistSudetenBranch(const HoI4::Country& home,
	 const std::vector<std::shared_ptr<HoI4::Country>>& anschlussTargets,
	 const std::vector<std::shared_ptr<HoI4::Country>>& sudetenTargets,
	 const std::map<std::string, std::vector<int>>& demandedStates,
	 HoI4::Events& events,
	 HoI4::Localisation& hoi4Localisations)
{
	const auto& homeTag = home.getTag();

	// if it can easily take these targets as they are not in an alliance, you can get annexation event
	auto expandTheReichFocus = GetLoadedFocus("expand_the_reich").makeCustomizedCopy(homeTag);
	if (!anschlussTargets.empty())
	{
		// if there are anschlusses, make this event require at least 1 anschluss, else, its the start of a tree
		std::string prereq = "= {";
		for (const auto& target: anschlussTargets)
		{
			prereq += " focus = " + homeTag + "_anschluss_" + target->getTag();
		}
		expandTheReichFocus->prerequisites.push_back(prereq + " }\n");
		expandTheReichFocus->relativePositionId = "The_third_way" + homeTag;
		expandTheReichFocus->xPos = 0;
		expandTheReichFocus->yPos = 3;
	}
	else
	{
		expandTheReichFocus->xPos = nextFreeColumn;
		nextFreeColumn += 2;
		expandTheReichFocus->yPos = 0;
	}
	expandTheReichFocus->updateFocusElement(expandTheReichFocus->completionReward, "$TEXT", expandTheReichFocus->text);
	addFocus(expandTheReichFocus);

	int sudetenFreeColumn = 1 - static_cast<int>(sudetenTargets.size());
	for (const auto& target: sudetenTargets)
	{
		const auto& possibleSudetenTargetCountryName = target->getName();
		std::string sudetenTargetCountryName;
		if (possibleSudetenTargetCountryName)
		{
			sudetenTargetCountryName = *possibleSudetenTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine annexation target country name for fascist sudeten focuses";
			sudetenTargetCountryName.clear();
		}

		const auto& targetTag = target->getTag();

		auto sudetenFocus = GetLoadedFocus("_sudeten_").makeTargetedCopy(homeTag, targetTag, hoi4Localisations);
		sudetenFocus->id = homeTag + "_sudeten_" + targetTag;
		date dateAvailable = date("1938.1.1");
		if (const auto& relations = home.getRelations(targetTag); relations)
		{
			dateAvailable.increaseByMonths((200 + relations->getRelations()) / 16);
		}
		sudetenFocus->updateFocusElement(sudetenFocus->available, "#DATE", "date > " + dateAvailable.toString() + "\n");
		sudetenFocus->relativePositionId = "expand_the_reich" + homeTag;
		sudetenFocus->xPos = sudetenFreeColumn;
		sudetenFocus->yPos = 1;
		sudetenFocus->updateFocusElement(sudetenFocus->bypass, "$TARGET", targetTag);
		sudetenFocus->updateFocusElement(sudetenFocus->completionReward, "$TARGETNAME", sudetenTargetCountryName);
		sudetenFocus->updateFocusElement(sudetenFocus->completionReward, "$TARGET", targetTag);
		sudetenFocus->updateFocusElement(sudetenFocus->completionReward,
			 "$EVENTID",
			 std::to_string(events.getCurrentNationFocusEventNum()));
		addFocus(sudetenFocus);
		sudetenFreeColumn += 2;

		// FINISH HIM
		auto finishFocus = GetLoadedFocus("_finish_").makeTargetedCopy(homeTag, targetTag, hoi4Localisations);
		finishFocus->id = homeTag + "_finish_" + targetTag;
		const auto& truceUntil = home.getTruceUntil(targetTag);
		finishFocus->updateFocusElement(finishFocus->available,
			 "#DATE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		finishFocus->updateFocusElement(finishFocus->available, "$TARGET", targetTag);
		finishFocus->prerequisites.push_back("= { focus =  " + homeTag + "_sudeten_" + targetTag + " }");
		finishFocus->relativePositionId = homeTag + "_sudeten_" + targetTag;
		finishFocus->xPos = 0;
		finishFocus->yPos = 1;
		finishFocus->updateFocusElement(finishFocus->bypass, "$TARGET", targetTag);
		finishFocus->updateFocusElement(finishFocus->completionReward, "$TARGETNAME", sudetenTargetCountryName);
		finishFocus->updateFocusElement(finishFocus->completionReward, "$TARGET", targetTag);
		addFocus(finishFocus);

		// events
		if (demandedStates.contains(targetTag))
		{
			events.createSudetenEvent(homeTag, targetTag, demandedStates.at(targetTag));
		}
	}
}


void HoI4FocusTree::addGPWarBranch(const HoI4::Country& home,
	 const std::vector<std::shared_ptr<HoI4::Country>>& newAllies,
	 const std::vector<std::shared_ptr<HoI4::Country>>& GCTargets,
	 const std::string& ideology,
	 const std::set<std::string>& majorIdeologies,
	 HoI4::Events& events,
	 Mappers::FactionNameMapper& factionNameMapper,
	 HoI4::Localisation& hoi4Localisations)
{
	const auto& homeTag = home.getTag();

	const auto& ideologyShort = ideology.substr(0, 3);
	if (!newAllies.empty())
	{
		auto summitFocus = GetLoadedFocus("_Summit").makeCustomizedCopy(homeTag);
		summitFocus->id = ideologyShort + "_Summit" + homeTag;
		summitFocus->text = ideology + "_Summit";
		summitFocus->xPos = nextFreeColumn + static_cast<int>(newAllies.size()) - 1;
		summitFocus->yPos = 0;
		summitFocus->updateFocusElement(summitFocus->completionReward, "$IDEOLOGY", ideology);

		events.createSummitNewsEvents(majorIdeologies);
		auto eventIds = events.getSummitNewsEventsIds();
		std::string hiddenEffect = "hidden_effect = {\n";
		hiddenEffect += "\t\t\tif = {\n";
		hiddenEffect += "\t\t\t\tlimit = { has_government = fascism }\n";
		hiddenEffect += "\t\t\t\tevery_other_country = {\n";
		hiddenEffect += "\t\t\t\t\tlimit = { is_major = yes }\n";
		hiddenEffect += "\t\t\t\t\tnews_event = { id = " + eventIds["fascism"] + " }\n";
		hiddenEffect += "\t\t\t\t}\n";
		hiddenEffect += "\t\t\t}\n";
		hiddenEffect += "\t\t}\n";
		summitFocus->updateFocusElement(summitFocus->completionReward,
			 "#FASC_NEWS",
			 hiddenEffect,
			 majorIdeologies.contains("fascism"));
		hiddenEffect = "hidden_effect = {\n";
		hiddenEffect += "\t\t\tif = {\n";
		hiddenEffect += "\t\t\t\tlimit = { has_government = communism }\n";
		hiddenEffect += "\t\t\t\tevery_other_country = {\n";
		hiddenEffect += "\t\t\t\t\tlimit = { is_major = yes }\n";
		hiddenEffect += "\t\t\t\t\tnews_event = { id = " + eventIds["communism"] + " }\n";
		hiddenEffect += "\t\t\t\t}\n";
		hiddenEffect += "\t\t\t}\n";
		hiddenEffect += "\t\t}\n";
		summitFocus->updateFocusElement(summitFocus->completionReward,
			 "#COMM_NEWS",
			 hiddenEffect,
			 majorIdeologies.contains("communism"));
		focuses.push_back(summitFocus);
		hoi4Localisations.copyFocusLocalisations("_Summit", summitFocus->text);
		hoi4Localisations.updateLocalisationText(summitFocus->text, "$TARGET", ideology);
		hoi4Localisations.updateLocalisationText(summitFocus->text + "_desc", "$TARGET", ideology);
	}

	int allianceFreeColumn = 1 - static_cast<int>(newAllies.size());
	for (const auto& newAlly: newAllies)
	{
		auto allianceFocus = GetLoadedFocus("Alliance_").makeTargetedCopy(homeTag, newAlly->getTag(), hoi4Localisations);
		allianceFocus->id = "Alliance_" + newAlly->getTag() + homeTag;
		allianceFocus->prerequisites.push_back("= { focus = " + ideologyShort + "_Summit" + homeTag + " }");
		allianceFocus->relativePositionId = ideologyShort + "_Summit" + homeTag;
		allianceFocus->xPos = allianceFreeColumn;
		allianceFocus->yPos = 1;
		allianceFocus->updateFocusElement(allianceFocus->available, "$ALLY", newAlly->getTag());
		allianceFocus->updateFocusElement(allianceFocus->bypass, "$ALLY", newAlly->getTag());
		allianceFocus->updateFocusElement(allianceFocus->completionReward, "$ALLY", newAlly->getTag());
		allianceFocus->updateFocusElement(allianceFocus->completionReward,
			 "$EVENTID",
			 std::to_string(events.getCurrentNationFocusEventNum()));
		focuses.push_back(allianceFocus);
		allianceFreeColumn += 2;

		events.createFactionEvents(home, factionNameMapper);
	}

	int freeColumn = 1 - static_cast<int>(GCTargets.size());
	for (const auto& greatPower: GCTargets)
	{
		const auto& possibleWarTargetCountryName = greatPower->getName();
		std::string warTargetCountryName;
		if (possibleWarTargetCountryName)
		{
			warTargetCountryName = *possibleWarTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine war target country name for GP war focuses";
			warTargetCountryName.clear();
		}

		const auto& greatPowerTag = greatPower->getTag();
		// figuring out location of WG
		auto gpWarFocus = GetLoadedFocus("GP_War").makeCustomizedCopy(homeTag);
		for (const auto& ally: newAllies)
		{
			gpWarFocus->prerequisites.push_back("= { focus = Alliance_" + ally->getTag() + homeTag + " }");
		}
		gpWarFocus->id = "GP_War" + greatPowerTag + homeTag;
		gpWarFocus->text += greatPowerTag;
		auto dateAvailable = date("1939.1.1");
		if (const auto& relations = home.getRelations(greatPowerTag); relations)
		{
			dateAvailable.increaseByMonths((200 + relations->getRelations()) / 16);
		}
		if (const auto& truceUntil = home.getTruceUntil(greatPowerTag); truceUntil && *truceUntil > dateAvailable)
		{
			gpWarFocus->updateFocusElement(gpWarFocus->available, "#DATE", "date > " + truceUntil->toString());
		}
		else
		{
			gpWarFocus->updateFocusElement(gpWarFocus->available, "#DATE", "date > " + dateAvailable.toString());
		}
		if (!newAllies.empty())
		{
			gpWarFocus->relativePositionId = ideologyShort + "_Summit" + homeTag;
			gpWarFocus->xPos = freeColumn;
			gpWarFocus->yPos = 2;
		}
		else
		{
			gpWarFocus->xPos = nextFreeColumn;
			gpWarFocus->yPos = 0;
		}
		gpWarFocus->updateFocusElement(gpWarFocus->bypass, "$TARGET", greatPowerTag);
		gpWarFocus->updateFocusElement(gpWarFocus->aiWillDo, "$FACTOR", std::to_string(10 - GCTargets.size() * 5));
		gpWarFocus->updateFocusElement(gpWarFocus->aiWillDo, "$TARGET", greatPowerTag);
		std::string warWithTargets;
		for (const auto& otherTarget: GCTargets)
		{
			if (otherTarget->getTag() == greatPowerTag)
			{
				continue;
			}
			if (warWithTargets.empty())
			{
				warWithTargets = "has_war_with = " + otherTarget->getTag() + "\n";
			}
			else
			{
				warWithTargets += "\t\t\t\thas_war_with = " + otherTarget->getTag() + "\n";
			}
		}
		gpWarFocus->updateFocusElement(gpWarFocus->aiWillDo, "#WAR_WITH_TARGETS", warWithTargets);
		gpWarFocus->updateFocusElement(gpWarFocus->completionReward, "$TARGETNAME", warTargetCountryName);
		gpWarFocus->updateFocusElement(gpWarFocus->completionReward, "$TARGET", greatPowerTag);
		focuses.push_back(gpWarFocus);
		freeColumn += 2;
		hoi4Localisations.copyFocusLocalisations("GPWar", gpWarFocus->text);
		hoi4Localisations.updateLocalisationText(gpWarFocus->text, "$TARGET", greatPowerTag);
		hoi4Localisations.updateLocalisationText(gpWarFocus->text + "_desc", "$TARGET", greatPowerTag);
	}
	nextFreeColumn += 2 * static_cast<int>(std::max(newAllies.size(), GCTargets.size()));
}


std::map<std::string, std::set<int>> HoI4FocusTree::addReconquestBranch(const HoI4::Country& theCountry,
	 int& numWarsWithNeighbors,
	 const std::set<std::string>& majorIdeologies,
	 const std::map<int, HoI4::State>& states,
	 HoI4::Localisation& hoi4Localisations)
{
	const auto& coreHolders = determineWarTargets(theCountry, theCountry.getCoreStates(), states);
	if (coreHolders.empty())
	{
		return coreHolders;
	}

	const auto& theTag = theCountry.getTag();

	int sumUnownedCores = 0;
	std::map<std::string, int> provinceCount;
	for (const auto& [tag, coreStates]: coreHolders)
	{
		const auto& numProvinces = calculateNumEnemyOwnedCores(coreStates, states);
		provinceCount[tag] = numProvinces;
		sumUnownedCores += numProvinces;
	}

	numWarsWithNeighbors = std::min(static_cast<int>(coreHolders.size()), 4);

	std::shared_ptr<HoI4Focus> reclaimCoresFocus = GetLoadedFocus("reclaim_cores").makeCustomizedCopy(theTag);
	reclaimCoresFocus->selectEffect = "= {\n";
	for (const auto& tag: coreHolders | std::views::keys)
	{
		const auto& numProvinces = provinceCount.at(tag);
		reclaimCoresFocus->selectEffect +=
			 "\t\t\tset_variable = { unowned_cores_@" + tag + " = " + std::to_string(numProvinces) + " }\n";
	}
	reclaimCoresFocus->selectEffect +=
		 "\t\t\tset_variable = { revanchism = " + std::to_string(0.00001 * sumUnownedCores) + " }\n";
	reclaimCoresFocus->selectEffect +=
		 "\t\t\tset_variable = { revanchism_stab = " + std::to_string(-0.000001 * sumUnownedCores) + " }\n";
	reclaimCoresFocus->selectEffect += "\t\t\tadd_dynamic_modifier = { modifier = revanchism }\n";
	if (majorIdeologies.contains("fascism"))
	{
		reclaimCoresFocus->selectEffect += "\t\t\tadd_dynamic_modifier = { modifier = revanchism_fasc }\n";
	}
	reclaimCoresFocus->selectEffect += "\t\t}\n";
	reclaimCoresFocus->xPos = nextFreeColumn + static_cast<int>(coreHolders.size()) - 1;
	focuses.push_back(reclaimCoresFocus);

	std::string fascistGovernmentCheck;
	fascistGovernmentCheck = "modifier = {\n";
	fascistGovernmentCheck += "\t\t\t\tfactor = 5\n";
	fascistGovernmentCheck += "\t\t\t\thas_government = fascism\n";
	fascistGovernmentCheck += "\t\t\t}";

	for (const auto& [target, coreStates]: coreHolders)
	{
		const auto& numProvinces = provinceCount.at(target);
		const auto& aiChance = std::to_string(std::max(static_cast<int>(0.1 * numProvinces), 1));
		const auto& truceUntil = theCountry.getTruceUntil(target);

		std::shared_ptr<HoI4Focus> raiseMatterFocus =
			 GetLoadedFocus("raise_matter").makeTargetedCopy(theTag, target, hoi4Localisations);
		raiseMatterFocus->xPos = nextFreeColumn;
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		std::string fascismPopularityCheck;
		fascismPopularityCheck = "modifier = {\n";
		fascismPopularityCheck += "\t\t\t\tfactor = 0\n";
		fascismPopularityCheck += "\t\t\t\tNOT = { has_government = fascism }\n";
		fascismPopularityCheck += "\t\t\t\tNOT = { fascism > 0.35 }\n";
		fascismPopularityCheck += "\t\t\t}";
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->aiWillDo,
			 "#FASCPOP",
			 fascismPopularityCheck,
			 majorIdeologies.contains("fascism"));
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->aiWillDo,
			 "#FASCGOV",
			 fascistGovernmentCheck,
			 majorIdeologies.contains("fascism"));
		if (!majorIdeologies.contains("fascism"))
		{
			raiseMatterFocus->completionReward = "= {\n";
			raiseMatterFocus->completionReward += "\t\t\tadd_stability = 0.0001\n";
			raiseMatterFocus->completionReward += "\t\t\tadd_political_power = 150\n";
			raiseMatterFocus->completionReward +=
				 "\t\t\tadd_timed_idea = { idea = generic_military_industry days = 180 }\n";
			raiseMatterFocus->completionReward += "\t\t}";
		}
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->available, "$TARGET", target);
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->completionReward,
			 "$POPULARITY",
			 std::to_string(0.000001 * numProvinces));
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->bypass, "$TARGET", target);
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->aiWillDo, "$TARGET", target);
		raiseMatterFocus->updateFocusElement(raiseMatterFocus->aiWillDo, "$REVANCHISM", aiChance);
		focuses.push_back(raiseMatterFocus);
		nextFreeColumn += 2;

		std::shared_ptr<HoI4Focus> buildPublicSupportFocus =
			 GetLoadedFocus("build_public_support").makeTargetedCopy(theTag, target, hoi4Localisations);
		buildPublicSupportFocus->prerequisites.clear();
		buildPublicSupportFocus->prerequisites.push_back(
			 std::string("= { focus = raise_matter").append(theTag).append(target).append(" }"));
		buildPublicSupportFocus->relativePositionId += target;
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		fascismPopularityCheck = "modifier = {\n";
		fascismPopularityCheck += "\t\t\t\tfactor = 0\n";
		fascismPopularityCheck += "\t\t\t\tNOT = { has_government = fascism }\n";
		fascismPopularityCheck += "\t\t\t\tNOT = { fascism > 0.4 }\n";
		fascismPopularityCheck += "\t\t\t}";
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->aiWillDo,
			 "#FASCPOP",
			 fascismPopularityCheck,
			 majorIdeologies.contains("fascism"));
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->aiWillDo,
			 "#FASCGOV",
			 fascistGovernmentCheck,
			 majorIdeologies.contains("fascism"));
		if (!majorIdeologies.contains("fascism"))
		{
			buildPublicSupportFocus->completionReward = " = {\n";
			buildPublicSupportFocus->completionReward += "\t\t\tadd_stability = 0.0001\n";
			buildPublicSupportFocus->completionReward += "\t\t\tadd_war_support = $WARSUPPORT\n";
			buildPublicSupportFocus->completionReward +=
				 "\t\t\tadd_timed_idea = { idea = generic_rapid_mobilization days = 180 }\n";
			buildPublicSupportFocus->completionReward += "\t\t}";
		}
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->available, "$TARGET", target);
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->completionReward,
			 "$POPULARITY",
			 std::to_string(0.000001 * numProvinces));
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->completionReward,
			 "$WARSUPPORT",
			 std::to_string(0.00001 * numProvinces));
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->bypass, "$TARGET", target);
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->aiWillDo, "$TARGET", target);
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->aiWillDo, "$TAG", theTag);
		buildPublicSupportFocus->updateFocusElement(buildPublicSupportFocus->aiWillDo, "$REVANCHISM", aiChance);
		focuses.push_back(buildPublicSupportFocus);

		std::shared_ptr<HoI4Focus> territoryOrWarFocus =
			 GetLoadedFocus("territory_or_war").makeTargetedCopy(theTag, target, hoi4Localisations);
		territoryOrWarFocus->prerequisites.clear();
		territoryOrWarFocus->prerequisites.push_back("= { focus = build_public_support" + theTag + target + " }");
		territoryOrWarFocus->relativePositionId += target;
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->aiWillDo,
			 "#FASCGOV",
			 fascistGovernmentCheck,
			 majorIdeologies.contains("fascism"));
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->available, "$TARGET", target);
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->completionReward, "$TARGET", target);
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->bypass, "$TARGET", target);
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->aiWillDo, "$TARGET", target);
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->aiWillDo, "$TAG", theTag);
		territoryOrWarFocus->updateFocusElement(territoryOrWarFocus->aiWillDo, "$REVANCHISM", aiChance);
		focuses.push_back(territoryOrWarFocus);

		std::shared_ptr<HoI4Focus> warPlanFocus =
			 GetLoadedFocus("war_plan").makeTargetedCopy(theTag, target, hoi4Localisations);
		warPlanFocus->prerequisites.clear();
		warPlanFocus->prerequisites.push_back("= { focus = territory_or_war" + theTag + target + " }");
		warPlanFocus->relativePositionId += target;
		warPlanFocus->updateFocusElement(warPlanFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		warPlanFocus->updateFocusElement(warPlanFocus->aiWillDo,
			 "#FASCGOV",
			 fascistGovernmentCheck,
			 majorIdeologies.contains("fascism"));
		warPlanFocus->updateFocusElement(warPlanFocus->available, "$TARGET", target);
		warPlanFocus->updateFocusElement(warPlanFocus->completionReward, "$TARGET", target);
		warPlanFocus->updateFocusElement(warPlanFocus->bypass, "$TARGET", target);
		warPlanFocus->updateFocusElement(warPlanFocus->aiWillDo, "$TARGET", target);
		warPlanFocus->updateFocusElement(warPlanFocus->aiWillDo, "$TAG", theTag);
		warPlanFocus->updateFocusElement(warPlanFocus->aiWillDo, "$REVANCHISM", aiChance);
		focuses.push_back(warPlanFocus);

		std::shared_ptr<HoI4Focus> declareWarFocus =
			 GetLoadedFocus("declare_war").makeTargetedCopy(theTag, target, hoi4Localisations);
		declareWarFocus->prerequisites.clear();
		declareWarFocus->prerequisites.push_back("= { focus = war_plan" + theTag + target + " }");
		declareWarFocus->relativePositionId += target;
		declareWarFocus->updateFocusElement(declareWarFocus->available,
			 "#TRUCE",
			 "date > " + truceUntil->toString(),
			 truceUntil.has_value());
		declareWarFocus->updateFocusElement(declareWarFocus->aiWillDo,
			 "#FASCGOV",
			 fascistGovernmentCheck,
			 majorIdeologies.contains("fascism"));
		declareWarFocus->updateFocusElement(declareWarFocus->available, "$TARGET", target);
		declareWarFocus->updateFocusElement(declareWarFocus->completionReward, "$TARGET", target);
		std::string coresString;
		for (const auto& stateId: coreStates)
		{
			coresString += std::to_string(stateId) + " ";
		}
		declareWarFocus->updateFocusElement(declareWarFocus->completionReward, "$CORE_STATES", coresString);
		declareWarFocus->updateFocusElement(declareWarFocus->bypass, "$TARGET", target);
		declareWarFocus->updateFocusElement(declareWarFocus->aiWillDo, "$TARGET", target);
		declareWarFocus->updateFocusElement(declareWarFocus->aiWillDo, "$TAG", theTag);
		declareWarFocus->updateFocusElement(declareWarFocus->aiWillDo,
			 "$REVANCHISM",
			 std::to_string(std::max(static_cast<int>(numProvinces), 1)));
		focuses.push_back(declareWarFocus);

		std::shared_ptr<HoI4Focus> cleanupRevanchismFocus =
			 GetLoadedFocus("cleanup_revanchism").makeTargetedCopy(theTag, target, hoi4Localisations);
		cleanupRevanchismFocus->prerequisites.clear();
		cleanupRevanchismFocus->prerequisites.push_back("= { focus = declare_war" + theTag + target + " }");
		cleanupRevanchismFocus->relativePositionId += target;
		cleanupRevanchismFocus->updateFocusElement(cleanupRevanchismFocus->available, "$TARGET", target);
		cleanupRevanchismFocus->updateFocusElement(cleanupRevanchismFocus->completionReward, "$TARGET", target);
		cleanupRevanchismFocus->updateFocusElement(cleanupRevanchismFocus->completionReward,
			 "$REVANCHISM",
			 std::to_string(0.000005 * numProvinces));
		cleanupRevanchismFocus->updateFocusElement(cleanupRevanchismFocus->completionReward,
			 "$STABILITY",
			 std::to_string(0.0000005 * numProvinces));
		focuses.push_back(cleanupRevanchismFocus);
	}

	return coreHolders;
}


std::set<std::string> HoI4FocusTree::addConquerBranch(const HoI4::Country& theCountry,
	 int& numWarsWithNeighbors,
	 const std::set<std::string>& majorIdeologies,
	 const std::map<std::string, std::set<int>>& coreHolders,
	 const std::map<int, HoI4::State>& states,
	 HoI4::Localisation& hoi4Localisations)
{
	// less than this % of highest strategy value means theCountry doesn't get a focus on this target
	// compensating for the Vic2 AI error of wanting to conquer provinces across ocean(s)
	constexpr double strategyValueThreshold = 0.1;
	const auto& tag = theCountry.getTag();
	std::set<std::string> conquerTags;

	const auto& conquerStrategies = theCountry.getConquerStrategies();
	if (conquerStrategies.empty())
	{
		return conquerTags;
	}

	for (const auto& strategy: conquerStrategies)
	{
		if (strategy.getID() == tag)
		{
			continue;
		}

		const double relativeValue = strategy.getValue() / getMaxConquerValue(conquerStrategies);
		if (hasMaxNeighborWars(numWarsWithNeighbors) || relativeValue < strategyValueThreshold)
		{
			break;
		}
		if (!theCountry.isEligibleEnemy(strategy.getID()))
		{
			continue;
		}
		if (coreHolders.contains(strategy.getID()))
		{
			continue;
		}
		const auto& claimsHolders = determineWarTargets(theCountry, theCountry.getClaimedStates(), states);
		std::optional<int> newClaim;
		if (!claimsHolders.contains(strategy.getID()))
		{
			newClaim = strategy.getClaimedState();
		}
		if (!newClaim)
		{
			continue;
		}
		const auto& claimStateId = std::to_string(*newClaim);

		conquerTags.insert(strategy.getID());
		numWarsWithNeighbors++;

		const auto& borderDisputesTruceUntil = theCountry.getTruceUntil(strategy.getID());
		auto borderDisputesFocus =
			 GetLoadedFocus("border_disputes").makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
		borderDisputesFocus->relativePositionId.clear();
		borderDisputesFocus->updateFocusElement(borderDisputesFocus->available, "$TARGET", strategy.getID());
		borderDisputesFocus->updateFocusElement(borderDisputesFocus->available,
			 "#TRUCE",
			 "date > " + borderDisputesTruceUntil->toString(),
			 !!borderDisputesTruceUntil);
		borderDisputesFocus->updateFocusElement(borderDisputesFocus->available,
			 "#OWNSCLAIM",
			 "owns_state = " + claimStateId);
		borderDisputesFocus->xPos = nextFreeColumn;
		borderDisputesFocus->yPos = 0;
		borderDisputesFocus->updateFocusElement(borderDisputesFocus->aiWillDo, "$TARGET", strategy.getID());
		focuses.push_back(borderDisputesFocus);

		auto assertClaimsFocus =
			 GetLoadedFocus("assert_claims").makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
		assertClaimsFocus->prerequisites.clear();
		assertClaimsFocus->prerequisites.push_back("= { focus = border_disputes" + tag + strategy.getID() + " }");
		assertClaimsFocus->relativePositionId += strategy.getID();
		assertClaimsFocus->updateFocusElement(assertClaimsFocus->available, "$TARGET", strategy.getID());
		auto dateAvailable = date("1936.1.1");
		if (const auto& relations = theCountry.getRelations(strategy.getID()); relations)
		{
			dateAvailable.increaseByMonths((200 + relations->getRelations()) / 8);
		}
		if (const auto& assertClaimsTruceUntil = theCountry.getTruceUntil(strategy.getID());
			 assertClaimsTruceUntil && *assertClaimsTruceUntil > dateAvailable)
		{
			assertClaimsFocus->updateFocusElement(assertClaimsFocus->available,
				 "#DATE",
				 "date > " + assertClaimsTruceUntil->toString());
		}
		else
		{
			assertClaimsFocus->updateFocusElement(assertClaimsFocus->available,
				 "#DATE",
				 "date > " + dateAvailable.toString());
		}
		assertClaimsFocus->updateFocusElement(assertClaimsFocus->available, "#OWNSCLAIM", "owns_state = " + claimStateId);
		assertClaimsFocus->updateFocusElement(assertClaimsFocus->completionReward, "$TARGET", strategy.getID());
		assertClaimsFocus->updateFocusElement(assertClaimsFocus->completionReward,
			 "#ADDCLAIM",
			 "add_state_claim = " + claimStateId);
		assertClaimsFocus->updateFocusElement(assertClaimsFocus->aiWillDo, "$TARGET", strategy.getID());
		focuses.push_back(assertClaimsFocus);

		auto prepareForWarFocus =
			 GetLoadedFocus("prepare_for_war").makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
		prepareForWarFocus->prerequisites.clear();
		prepareForWarFocus->prerequisites.push_back("= { focus = assert_claims" + tag + strategy.getID() + " }");
		prepareForWarFocus->relativePositionId += strategy.getID();
		prepareForWarFocus->updateFocusElement(prepareForWarFocus->available, "$TARGET", strategy.getID());
		prepareForWarFocus->updateFocusElement(prepareForWarFocus->available,
			 "#OWNSCLAIM",
			 "owns_state = " + claimStateId);
		prepareForWarFocus->updateFocusElement(prepareForWarFocus->bypass, "$TARGET", strategy.getID());
		focuses.push_back(prepareForWarFocus);

		auto neighborWarFocus = GetLoadedFocus("neighbor_war").makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
		neighborWarFocus->prerequisites.clear();
		neighborWarFocus->prerequisites.push_back("= { focus = prepare_for_war" + tag + strategy.getID() + " }");
		neighborWarFocus->relativePositionId += strategy.getID();
		neighborWarFocus->updateFocusElement(neighborWarFocus->available, "$TARGET", strategy.getID());
		neighborWarFocus->updateFocusElement(neighborWarFocus->available, "#OWNSCLAIM", "owns_state = " + claimStateId);
		neighborWarFocus->updateFocusElement(neighborWarFocus->completionReward, "$TARGET", strategy.getID());

		std::string claimsString = "claimed_states";
		if (const auto& claimedStatesItr = claimsHolders.find(strategy.getID()); claimedStatesItr != claimsHolders.end())
		{
			claimsString = "{ ";
			for (const auto& stateId: claimedStatesItr->second)
			{
				claimsString += std::to_string(stateId) + " ";
			}
			claimsString += "}";
		}
		else if (newClaim)
		{
			claimsString = "{ " + std::to_string(*newClaim) + " }";
		}
		neighborWarFocus->updateFocusElement(neighborWarFocus->completionReward, "$CLAIMED_STATES", claimsString);

		neighborWarFocus->updateFocusElement(neighborWarFocus->bypass, "$TARGET", strategy.getID());
		focuses.push_back(neighborWarFocus);

		nextFreeColumn += 2;
	}

	return conquerTags;
}


void HoI4FocusTree::addIntegratePuppetsBranch(const std::string& tag,
	 const std::map<std::string, std::string>& puppets,
	 HoI4::Localisation& hoi4Localisations)
{
	int yPos = 0;
	const auto& originalFocus = GetLoadedFocus("integrate_satellite");
	for (const auto& puppet: puppets | std::views::keys)
	{
		std::shared_ptr<HoI4Focus> newFocus = originalFocus.makeTargetedCopy(tag, puppet, hoi4Localisations);
		newFocus->xPos = nextFreeColumn;
		newFocus->yPos = yPos;
		newFocus->updateFocusElement(newFocus->selectEffect, "#TARGET", puppet);
		newFocus->updateFocusElement(newFocus->bypass, "#TARGET", puppet);
		newFocus->updateFocusElement(newFocus->completionReward, "#TARGET", puppet);
		focuses.push_back(newFocus);

		yPos++;
	}

	nextFreeColumn += 2;
}


void HoI4FocusTree::removeFocus(const std::string& id)
{
	focuses.erase(std::remove_if(focuses.begin(),
							focuses.end(),
							[id](std::shared_ptr<HoI4Focus> focus) {
								return focus->id == id;
							}),
		 focuses.end());
}