#include "HoI4FocusTree.h"
#include "CommonRegexes.h"
#include "HoI4Country.h"
#include "HoI4Focus.h"
#include "HoI4Localisation.h"
#include "HoI4World.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "SharedFocus.h"
#include "V2World/Countries/Country.h"
#include "V2World/Politics/Party.h"
using namespace std;



// this is used to cache focuses that can be just loaded from a file
static std::map<std::string, HoI4Focus> loadedFocuses;



HoI4FocusTree::HoI4FocusTree(const HoI4::Country& country): dstCountryTag(country.getTag())
{
}


constexpr bool hasMaxNeighborWars(const int numWarsWithNeighbors)
{
	return numWarsWithNeighbors >= 5;
}

void HoI4FocusTree::addGenericFocusTree(const set<string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\t\tCreating generic focus tree";
	confirmLoadedFocuses();

	auto numCollectovistIdeologies = static_cast<int>(calculateNumCollectovistIdeologies(majorIdeologies));

	if (const auto& originalFocus = loadedFocuses.find("political_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->xPos = static_cast<int>((numCollectovistIdeologies * 1.5) + 16);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus political_effort");
	}

	if (numCollectovistIdeologies > 0)
	{
		if (const auto& originalFocus = loadedFocuses.find("collectivist_ethos"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\tOR = {\n";
			for (auto majorIdeology: majorIdeologies)
			{
				if (majorIdeology == "democratic")
				{
					continue;
				}
				newFocus->available += "\t\t\t\thas_government = " + majorIdeology + "\n";
			}
			newFocus->available += "\t\t\t}\n";
			newFocus->available += "\t\t}";
			newFocus->xPos = -(numCollectovistIdeologies / 2) - 1;
			newFocus->completionReward = "= {\n";
			if (majorIdeologies.contains("democratic"))
			{
				newFocus->completionReward += "\t\t\tadd_ideas = collectivist_ethos_focus_democratic\n";
			}
			else
			{
				newFocus->completionReward += "\t\t\tadd_ideas = collectivist_ethos_focus_neutral\n";
			}
			newFocus->completionReward += "\t\t}";
			sharedFocuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus collectivist_ethos");
		}

		determineMutualExclusions(majorIdeologies);

		string ideolgicalFanaticsmPrereqs;
		int relativePosition = 1 - numCollectovistIdeologies;
		if (majorIdeologies.contains("fascism"))
		{
			addFascistGenericFocuses(relativePosition, majorIdeologies);
			ideolgicalFanaticsmPrereqs += " ";
			ideolgicalFanaticsmPrereqs += "focus = paramilitarism";
			relativePosition += 2;
		}
		if (majorIdeologies.contains("communism"))
		{
			addCommunistGenericFocuses(relativePosition);
			if (ideolgicalFanaticsmPrereqs.size() > 0)
			{
				ideolgicalFanaticsmPrereqs += " ";
			}
			ideolgicalFanaticsmPrereqs += "focus = political_commissars";
			relativePosition += 2;
		}
		if (majorIdeologies.contains("absolutist"))
		{
			addAbsolutistGenericFocuses(relativePosition);
			if (ideolgicalFanaticsmPrereqs.size() > 0)
			{
				ideolgicalFanaticsmPrereqs += " ";
			}
			ideolgicalFanaticsmPrereqs += "focus = historical_claims_focus";
			relativePosition += 2;
		}
		if (majorIdeologies.contains("radical"))
		{
			addRadicalGenericFocuses(relativePosition);
			if (ideolgicalFanaticsmPrereqs.size() > 0)
			{
				ideolgicalFanaticsmPrereqs += " ";
			}
			ideolgicalFanaticsmPrereqs += "focus = army_provides_focus";
		}

		if (const auto& originalFocus = loadedFocuses.find("ideological_fanaticism");
			 originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { " + ideolgicalFanaticsmPrereqs + " }");
			newFocus->xPos = 0;
			newFocus->yPos = 5;
			newFocus->relativePositionId = "collectivist_ethos";
			sharedFocuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus ideological_fanaticism");
		}
	}

	if (const auto& originalFocus = loadedFocuses.find("liberty_ethos"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		if (numCollectovistIdeologies == 0)
		{
			newFocus->mutuallyExclusive.clear();
		}
		if (!majorIdeologies.contains("democratic"))
		{
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\thas_government = neutrality\n";
			newFocus->available += "\t\t}";

			newFocus->completionReward = "= {\n";
			newFocus->completionReward += "\tadd_ideas = liberty_ethos_focus_neutral\n";
			newFocus->completionReward += "}";
		}
		newFocus->xPos = (numCollectovistIdeologies + 1) / 2;
		newFocus->aiWillDo = "= {\n";
		newFocus->aiWillDo += "\t\t\tfactor = 95\n";
		newFocus->aiWillDo += "\t\t\tmodifier = {\n";
		newFocus->aiWillDo += "\t\t\t\tfactor = 0.1\n";
		newFocus->aiWillDo += "\t\t\t\tany_neighbor_country = {\n";
		newFocus->aiWillDo += "\t\t\t\t\tis_major = yes\n";
		newFocus->aiWillDo += "\t\t\t\t\tOR = {\n";
		for (auto majorIdeology: majorIdeologies)
		{
			newFocus->aiWillDo += "\t\t\t\t\t\thas_government = " + majorIdeology + "\n";
		}
		newFocus->aiWillDo += "\t\t\t\t\t}\n";
		newFocus->aiWillDo += "\t\t\t\t}\n";
		if (majorIdeologies.contains("democratic"))
		{
			newFocus->aiWillDo += "\t\t\t\tNOT = {\n";
			newFocus->aiWillDo += "\t\t\t\t\tany_neighbor_country = {\n";
			newFocus->aiWillDo += "\t\t\t\t\t\tis_major = yes\n";
			newFocus->aiWillDo += "\t\t\t\t\t\thas_government = democratic\n";
			newFocus->aiWillDo += "\t\t\t\t\t}\n";
			newFocus->aiWillDo += "\t\t\t\t}\n";
		}
		newFocus->aiWillDo += "\t\t\t}\n";
		newFocus->aiWillDo += "\t\t}";
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus liberty_ethos");
	}

	if (const auto& originalFocus = loadedFocuses.find("neutrality_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		if (!majorIdeologies.contains("democratic"))
		{
			newFocus->mutuallyExclusive.clear();
		}
		newFocus->aiWillDo = "= {\n";
		newFocus->aiWillDo += "\t\t\tfactor = 1\n";
		newFocus->aiWillDo += "\t\t}";
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus neutrality_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("deterrence"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus deterrence");
	}

	if (majorIdeologies.contains("democratic"))
	{
		if (const auto& originalFocus = loadedFocuses.find("interventionism_focus"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
			sharedFocuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus interventionism_focus");
		}

		if (const auto& originalFocus = loadedFocuses.find("volunteer_corps"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
			sharedFocuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus volunteer_corps");
		}

		if (const auto& originalFocus = loadedFocuses.find("foreign_expeditions"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
			sharedFocuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus foreign_expeditions");
		}
	}

	if (const auto& originalFocus = loadedFocuses.find("why_we_fight"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		if (!majorIdeologies.contains("democratic"))
		{
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = deterrence }");
		}
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus why_we_fight");
	}

	if (const auto& originalFocus = loadedFocuses.find("technology_sharing"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		if (numCollectovistIdeologies == 0)
		{
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = why_we_fight }");
		}
		newFocus->xPos = numCollectovistIdeologies;
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus technology_sharing");
	}

	if (const auto& originalFocus = loadedFocuses.find("border_disputes_shared"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		if (majorIdeologies.contains("communism"))
		{
			std::string comm;
			comm = "if = {\n";
			comm += "\t\t\t\t\t\tlimit = { ROOT = { has_government = communism } }\n";
			comm += "\t\t\t\t\t\tpotential_communist_puppet_target = yes\n";
			comm += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#COMMUNISM", comm);
			newFocus->updateFocusElement(newFocus->selectEffect, "#COMMUNISM", "potential_communist_puppet_target = yes");
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#COMMUNISM");
			newFocus->removePlaceholder(newFocus->selectEffect, "#COMMUNISM");
		}
		if (majorIdeologies.contains("fascism"))
		{
			std::string fasc;
			if (!majorIdeologies.contains("communism"))
			{
				fasc = "if = {\n";
			}
			else
			{
				fasc = "else_if = {\n";
			}
			fasc += "\t\t\t\t\t\tlimit = { ROOT = { has_government = fascism } }\n";
			fasc += "\t\t\t\t\t\tpotential_fascist_annex_target = yes\n";
			fasc += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#FASCISM", fasc);
			newFocus->updateFocusElement(newFocus->selectEffect, "#FASCISM", "potential_fascist_annex_target = yes");
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#FASCISM");
			newFocus->removePlaceholder(newFocus->selectEffect, "#FASCISM");
		}
		if (majorIdeologies.contains("radical"))
		{
			std::string rad;
			if (!majorIdeologies.contains("communism") && !majorIdeologies.contains("fascism"))
			{
				rad = "if = {\n";
			}
			else
			{
				rad = "else_if = {\n";
			}
			rad += "\t\t\t\t\t\tlimit = { ROOT = { has_government = radical } }\n";
			rad += "\t\t\t\t\t\tpotential_radical_annex_target = yes\n";
			rad += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#RADICAL", rad);
			newFocus->updateFocusElement(newFocus->selectEffect, "#RADICAL", "potential_radical_annex_target = yes");
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#RADICAL");
			newFocus->removePlaceholder(newFocus->selectEffect, "#RADICAL");
		}
		if (majorIdeologies.contains("communism") || majorIdeologies.contains("fascism") || majorIdeologies.contains("radical"))
		{
			std::string els;
			els = "else = {\n";
			els += "\t\t\t\t\t\thidden_trigger = { always = no }\n";
			els += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#ELSE", els);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#ELSE");
		}
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus border_disputes");
	}

	if (const auto& originalFocus = loadedFocuses.find("prepare_for_war_shared"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus prepare_for_war");
	}

	if (const auto& originalFocus = loadedFocuses.find("neighbor_war_shared"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		if (majorIdeologies.contains("communism"))
		{
			std::string comm;
			comm = "else_if = {\n";
			comm += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_communist_puppet_target = yes } }\n";
			comm += "\t\t\t\tdeclare_war_on = {\n";
			comm += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
			comm += "\t\t\t\t\ttype = puppet_wargoal_focus\n";
			comm += "\t\t\t\t}\n";
			comm += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
			comm += "\t\t\t}";
			newFocus->updateFocusElement(newFocus->completionReward, "#COMMUNISM", comm);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->completionReward, "#COMMUNISM");
		}
		if (majorIdeologies.contains("fascism"))
		{
			std::string fasc;
			fasc = "else_if = {\n";
			fasc += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_fascist_annex_target = yes } }\n";
			fasc += "\t\t\t\tdeclare_war_on = {\n";
			fasc += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
			fasc += "\t\t\t\t\ttype = annex_everything\n";
			fasc += "\t\t\t\t}\n";
			fasc += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
			fasc += "\t\t\t}";
			newFocus->updateFocusElement(newFocus->completionReward, "#FASCISM", fasc);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->completionReward, "#FASCISM");
		}
		if (majorIdeologies.contains("radical"))
		{
			std::string rad;
			rad = "else_if = {\n";
			rad += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_radical_annex_target = yes } }\n";
			rad += "\t\t\t\tdeclare_war_on = {\n";
			rad += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
			rad += "\t\t\t\t\ttype = annex_everything\n";
			rad += "\t\t\t\t}\n";
			rad += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
			rad += "\t\t\t}";
			newFocus->updateFocusElement(newFocus->completionReward, "#RADICAL", rad);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->completionReward, "#RADICAL");
		}
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus neighbor_war");
	}

	nextFreeColumn = static_cast<int>(numCollectovistIdeologies * 1.5) + ((numCollectovistIdeologies + 1) / 2) + 20;
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
		for (const auto& file: commonItems::GetAllFilesInFolderRecursive("Configurables/ConverterFocuses"))
		{
			parseFile("Configurables/ConverterFocuses/" + file);
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

	parseFile("Configurables/ConverterFocuses/" + branch + ".txt");
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

	int branchWidth;
	for (const auto& [level, levelFocuses]: branchLevels)
	{
		for (const auto& focus: levelFocuses)
		{
			if (const auto& originalFocus = loadedFocuses.find(focus); originalFocus != loadedFocuses.end())
			{
				const auto& newFocus = std::make_shared<HoI4Focus>(originalFocus->second);
				if (focus == branch)
				{
					branchWidth = newFocus->xPos;
					newFocus->xPos = nextFreeColumn + branchWidth/2;
					onActions.addFocusEvent(tag, focus);
				}
				focuses.push_back(newFocus);
			}
			else
			{
				throw std::runtime_error("Could not load focus " + focus);
			}
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


std::set<std::string> HoI4FocusTree::extractIds(const std::string& prerequisiteStr)
{
	std::set<std::string> ids;
	std::regex prereq("(focus\\s*=\\s*)([A-Za-z0-9_]+)");
	std::sregex_iterator end;
	std::sregex_iterator matchItr(prerequisiteStr.begin(), prerequisiteStr.end(), prereq);
	while (matchItr != end)
	{
		ids.insert((*matchItr)[2].str());
		++matchItr;
	}
	return ids;
}


size_t HoI4FocusTree::calculateNumCollectovistIdeologies(const set<string>& majorIdeologies)
{
	size_t numCollectovistIdeologies = 0;
	numCollectovistIdeologies += majorIdeologies.count("radical");
	numCollectovistIdeologies += majorIdeologies.count("absolutist");
	numCollectovistIdeologies += majorIdeologies.count("communism");
	numCollectovistIdeologies += majorIdeologies.count("fascism");
	return numCollectovistIdeologies;
}


void HoI4FocusTree::determineMutualExclusions(const set<string>& majorIdeologies)
{
	if (majorIdeologies.contains("fascism"))
	{
		communistMutualExclusions += "focus = nationalism_focus";
		absolutistMutualExlusions += "focus = nationalism_focus";
		radicalMutualExclusions += "focus = nationalism_focus";
	}
	if (majorIdeologies.contains("communism"))
	{
		if (fascistMutualExlusions.size() > 0)
		{
			fascistMutualExlusions += " ";
		}
		if (absolutistMutualExlusions.size() > 0)
		{
			absolutistMutualExlusions += " ";
		}
		if (radicalMutualExclusions.size() > 0)
		{
			radicalMutualExclusions += " ";
		}
		fascistMutualExlusions += "focus = internationalism_focus";
		absolutistMutualExlusions += "focus = internationalism_focus";
		radicalMutualExclusions += "focus = internationalism_focus";
	}
	if (majorIdeologies.contains("absolutist"))
	{
		if (fascistMutualExlusions.size() > 0)
		{
			fascistMutualExlusions += " ";
		}
		if (communistMutualExclusions.size() > 0)
		{
			communistMutualExclusions += " ";
		}
		if (radicalMutualExclusions.size() > 0)
		{
			radicalMutualExclusions += " ";
		}
		fascistMutualExlusions += "focus = absolutism_focus";
		communistMutualExclusions += "focus = absolutism_focus";
		radicalMutualExclusions += "focus = absolutism_focus";
	}
	if (majorIdeologies.contains("radical"))
	{
		if (fascistMutualExlusions.size() > 0)
		{
			fascistMutualExlusions += " ";
		}
		if (communistMutualExclusions.size() > 0)
		{
			communistMutualExclusions += " ";
		}
		if (absolutistMutualExlusions.size() > 0)
		{
			absolutistMutualExlusions += " ";
		}
		fascistMutualExlusions += "focus = radical_focus";
		communistMutualExclusions += "focus = radical_focus";
		absolutistMutualExlusions += "focus = radical_focus";
	}
}


void HoI4FocusTree::addFascistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies)
{
	if (const auto& originalFocus = loadedFocuses.find("nationalism_focus"); originalFocus != loadedFocuses.end())
	{
		const auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + fascistMutualExlusions + " }";
		newFocus->xPos = relativePosition;
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus nationalism_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("militarism"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus militarism");
	}

	if (const auto& originalFocus = loadedFocuses.find("military_youth"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->completionReward = "= {\n";
		newFocus->completionReward += "\t\t\tadd_ideas = military_youth_focus\n";
		for (auto ideology: majorIdeologies)
		{
			newFocus->completionReward += "\t\t\tif = {\n";
			newFocus->completionReward += "\t\t\t\tlimit = { has_government = " + ideology + " }\n";
			newFocus->completionReward += "\t\t\t\tadd_popularity = {\n";
			newFocus->completionReward += "\t\t\t\t\tideology = " + ideology + "\n";
			newFocus->completionReward += "\t\t\t\t\tpopularity = 0.2\n";
			newFocus->completionReward += "\t\t\t\t}\n";
			newFocus->completionReward += "\t\t\t}\n";
		}
		newFocus->completionReward += "\t\t}";
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus military_youth");
	}

	if (const auto& originalFocus = loadedFocuses.find("paramilitarism"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus paramilitarism");
	}
}


void HoI4FocusTree::addCommunistGenericFocuses(int relativePosition)
{
	if (const auto& originalFocus = loadedFocuses.find("internationalism_focus"); originalFocus != loadedFocuses.end())
	{
		const auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + communistMutualExclusions + " }";
		newFocus->available = "= {\n";
		newFocus->available += "\t\t\tOR = {\n";
		newFocus->available += "\t\t\t\thas_government = communism\n";
		newFocus->available += "\t\t\t\thas_government = neutrality\n";
		newFocus->available += "\t\t\t}\n";
		newFocus->available += "\t\t}";
		newFocus->xPos = relativePosition;
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus internationalism_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("political_correctness"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus political_correctness");
	}

	if (const auto& originalFocus = loadedFocuses.find("indoctrination_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus indoctrination_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("political_commissars"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->completionReward = "= {\n";
		newFocus->completionReward += "\t\t\tadd_ideas = political_commissars_focus\n";
		newFocus->completionReward += "\t\t\tif = {\n";
		newFocus->completionReward += "\t\t\t\tlimit = { has_government = communism }\n";
		newFocus->completionReward += "\t\t\t\tadd_popularity = {\n";
		newFocus->completionReward += "\t\t\t\t\tideology = communism\n";
		newFocus->completionReward += "\t\t\t\t\tpopularity = 0.2\n";
		newFocus->completionReward += "\t\t\t\t}\n";
		newFocus->completionReward += "\t\t\t}\n";
		newFocus->completionReward += "\t\t\tadd_political_power = 200\n";
		newFocus->completionReward += "\t\t}";
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus political_commissars");
	}
}


void HoI4FocusTree::addAbsolutistGenericFocuses(int relativePosition)
{
	if (const auto& originalFocus = loadedFocuses.find("absolutism_focus"); originalFocus != loadedFocuses.end())
	{
		const auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + absolutistMutualExlusions + " }";
		newFocus->xPos = relativePosition;
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus absolutism_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("royal_dictatorship_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus royal_dictatorship_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("royal_army_tradition_focus");
		 originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus royal_army_tradition_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("historical_claims_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus historical_claims_focus");
	}
}


void HoI4FocusTree::addRadicalGenericFocuses(int relativePosition)
{
	if (const auto& originalFocus = loadedFocuses.find("radical_focus"); originalFocus != loadedFocuses.end())
	{
		const auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + radicalMutualExclusions + " }";
		newFocus->xPos = relativePosition;
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus radical_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("private_channels_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus private_channels_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("hardfought_market_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus hardfought_market_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("army_provides_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4::SharedFocus>(originalFocus->second);
		sharedFocuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus army_provides_focus");
	}
}


std::unique_ptr<HoI4FocusTree> HoI4FocusTree::makeCustomizedCopy(const HoI4::Country& country) const
{
	HoI4FocusTree newFocusTree(country);

	for (auto focus: focuses)
	{
		auto newFocus = focus->makeCustomizedCopy(newFocusTree.dstCountryTag);
		newFocusTree.addFocus(newFocus);
	}
	newFocusTree.setNextFreeColumn(nextFreeColumn);

	return std::make_unique<HoI4FocusTree>(std::move(newFocusTree));
}


void HoI4FocusTree::addDemocracyNationalFocuses(shared_ptr<HoI4::Country> Home,
	 vector<shared_ptr<HoI4::Country>>& CountriesToContain,
	 HoI4::Localisation& hoi4Localisations)
{
	double WTModifier = 1;
	if (Home->getGovernmentIdeology() == "democratic")
	{
		if (const auto& rulingParty = Home->getRulingParty(); rulingParty != std::nullopt)
		{
			string warPol = rulingParty->getWarPolicy();
			if (warPol == "jingoism")
			{
				WTModifier = 0;
			}
			if (warPol == "pro_military")
			{
				WTModifier = 0.25;
			}
			if (warPol == "anti_military")
			{
				WTModifier = 0.5;
			}
			if (warPol == "pacifism" || warPol == "pacifist")
			{
				WTModifier = 0.5;
			}
		}
	}

	if (const auto& originalFocus = loadedFocuses.find("WarProp"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->available = "= {\n";
		newFocus->available += "\t\t\tthreat > " + to_string(0.20 * WTModifier / 1000) + "\n";
		newFocus->available += "\t\t}";
		newFocus->xPos = nextFreeColumn + static_cast<int>(CountriesToContain.size()) - 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus WarProp");
	}

	if (const auto& originalFocus = loadedFocuses.find("PrepInter"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->available = "= {\n";
		newFocus->available += "\t\t\tthreat > " + to_string(0.30 * WTModifier / 1000) + "\n";
		newFocus->available += "\t\t}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus PrepInter");
	}

	if (const auto& originalFocus = loadedFocuses.find("Lim"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->available = "= {\n";
		newFocus->available += "\t\t\tthreat > " + to_string(0.50 * WTModifier / 1000) + "\n";
		newFocus->available += "\t\t}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus Lim");
	}

	auto relativePos = 1 - static_cast<int>(CountriesToContain.size());
	for (auto country: CountriesToContain)
	{
		auto possibleContainedCountryName = country->getName();
		string containedCountryName;
		if (possibleContainedCountryName)
		{
			containedCountryName = *possibleContainedCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine contained country name for democratic focuses";
			containedCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("WarPlan"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), country->getTag(), hoi4Localisations);
			newFocus->bypass = "= {\n";
			newFocus->bypass += "\t\t\thas_war_with = " + country->getTag() + "\n";
			newFocus->bypass += "\t\t}";
			newFocus->xPos = relativePos;
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\tany_other_country = {\n";
			newFocus->available += "\t\t\t\toriginal_tag = " + country->getTag() + "\n";
			newFocus->available += "\t\t\t\texists = yes\n";
			newFocus->available += "\t\t\t\tNOT = { has_government = democratic } \n";
			newFocus->available += "\t\t\t\tNOT = { is_in_faction_with = " + Home->getTag() + " }\n";
			newFocus->available += "\t\t\t\tOR = {\n";
			newFocus->available += "\t\t\t\t\thas_offensive_war = yes\n";
			newFocus->available += "\t\t\t\t\thas_added_tension_amount > 30\n";
			newFocus->available += "\t\t\t\t}\n";
			newFocus->available += "\t\t\t}\n";
			newFocus->available += "\t\t}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus WarPlan");
		}

		if (const auto& originalFocus = loadedFocuses.find("Embargo"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), country->getTag(), hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus =  WarPlan" + Home->getTag() + country->getTag() + " }");
			newFocus->bypass = "= {\n";
			newFocus->bypass += "\t\t\thas_war_with = " + country->getTag() + "\n";
			newFocus->bypass += "\t\t}";
			newFocus->relativePositionId += country->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\tany_other_country = {\n";
			newFocus->available += "\t\t\t\toriginal_tag = " + country->getTag() + "\n";
			newFocus->available += "\t\t\t\texists = yes\n";
			newFocus->available += "\t\t\t\tNOT = { has_government = democratic } \n";
			newFocus->available += "\t\t\t\tNOT = { is_in_faction_with = " + Home->getTag() + " }\n";
			newFocus->available += "\t\t\t\tOR = {\n";
			newFocus->available += "\t\t\t\t\thas_offensive_war = yes\n";
			newFocus->available += "\t\t\t\t\thas_added_tension_amount > 30\n";
			newFocus->available += "\t\t\t\t\tthreat > 0.6\n";
			newFocus->available += "\t\t\t\t}\n";
			newFocus->available += "\t\t\t}\n";
			newFocus->available += "\t\t}";
			newFocus->completionReward = "= {\n";
			newFocus->completionReward += "\t\t\t" + country->getTag() + " = {\n";
			newFocus->completionReward +=
				 "\t\t\t\tadd_opinion_modifier = { target = " + Home->getTag() + " modifier = embargo }\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Embargo");
		}

		if (const auto& originalFocus = loadedFocuses.find("WAR"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), country->getTag(), hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus =  Embargo" + Home->getTag() + country->getTag() + " }");
			newFocus->bypass = "= {\n";
			newFocus->bypass += "\t\t\thas_war_with = " + country->getTag() + "\n";
			newFocus->bypass += "\t\t}";
			newFocus->relativePositionId += country->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\thas_war = no\n";
			newFocus->available += "\t\t\tany_other_country = {\n";
			newFocus->available += "\t\t\t\toriginal_tag = " + country->getTag() + "\n";
			newFocus->available += "\t\t\t\texists = yes\n";
			newFocus->available += "\t\t\t\tNOT = { has_government = democratic } \n";
			newFocus->available += "\t\t\t\tNOT = { is_in_faction_with = " + Home->getTag() + " }\n";
			newFocus->available += "\t\t\t\tOR = {\n";
			newFocus->available += "\t\t\t\t\thas_offensive_war = yes\n";
			newFocus->available += "\t\t\t\t\thas_added_tension_amount > 30\n";
			newFocus->available += "\t\t\t\t\tthreat > 0.6\n";
			newFocus->available += "\t\t\t\t}\n";
			newFocus->available += "\t\t\t}\n";
			newFocus->available += "\t\t}";
			newFocus->aiWillDo = "= {\n";
			newFocus->aiWillDo += "\t\t\tfactor = 10\n";
			newFocus->aiWillDo += "\t\t}";
			newFocus->completionReward = "= {\n";
			newFocus->completionReward += "\t\t\tdeclare_war_on = {\n";
			newFocus->completionReward += "\t\t\t\ttype = puppet_wargoal_focus\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + country->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);

			relativePos += 2;
		}
		else
		{
			throw std::runtime_error("Could not load focus WAR");
		}
	}
	nextFreeColumn += 2 * static_cast<int>(CountriesToContain.size());
}


void HoI4FocusTree::addAbsolutistEmpireNationalFocuses(shared_ptr<HoI4::Country> Home,
	 const vector<shared_ptr<HoI4::Country>>& targetColonies,
	 const vector<shared_ptr<HoI4::Country>>& annexationTargets,
	 HoI4::Localisation& hoi4Localisations)
{
	auto possibleHomeCountryAdjective = Home->getAdjective();
	string homeCountryAdjective;
	if (possibleHomeCountryAdjective)
	{
		homeCountryAdjective = *possibleHomeCountryAdjective;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine home country adjective for absolutist focuses";
		homeCountryAdjective.clear();
	}

	if (const auto& originalFocus = loadedFocuses.find("EmpireGlory"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->xPos = nextFreeColumn + 5;
		newFocus->yPos = 0;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus EmpireGlory");
	}

	if (const auto& originalFocus = loadedFocuses.find("StrengthenColonies"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "EmpireGlory" + Home->getTag();
		newFocus->xPos = -1;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus StrengthenColonies");
	}

	if (const auto& originalFocus = loadedFocuses.find("StrengthenHome"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "EmpireGlory" + Home->getTag();
		newFocus->xPos = 1;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus StrengthenHome");
	}

	if (const auto& originalFocus = loadedFocuses.find("ColonialInd"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "StrengthenColonies" + Home->getTag();
		newFocus->xPos = -2;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus ColonialInd");
	}

	if (const auto& originalFocus = loadedFocuses.find("ColonialHwy"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "ColonialInd" + Home->getTag();
		newFocus->xPos = -2;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus ColonialHwy");
	}

	if (const auto& originalFocus = loadedFocuses.find("ResourceFac"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "ColonialInd" + Home->getTag();
		newFocus->xPos = 0;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus ResourceFac");
	}

	if (const auto& originalFocus = loadedFocuses.find("ColonialArmy"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "StrengthenColonies" + Home->getTag();
		newFocus->xPos = 0;
		newFocus->yPos = 1;
		newFocus->completionReward = "= {\n";
		newFocus->completionReward += "\t\tadd_ideas = militarism_focus_absolutist\n";
		newFocus->completionReward += "}\n";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus ColonialArmy");
	}

	// establish protectorate
	if (targetColonies.size() >= 1)
	{
		auto target = targetColonies.front();

		auto possibleProtectorateCountryName = target->getName();
		string protectorateCountryName;
		if (possibleProtectorateCountryName)
		{
			protectorateCountryName = *possibleProtectorateCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine protectorate country name for absolutist focuses";
			protectorateCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Protectorate"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag(), hoi4Localisations);
			newFocus->id = "Protectorate" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "\t\t\t" + target->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "\t\t}";
			newFocus->prerequisites.push_back("= { focus = ColonialArmy" + Home->getTag() + " }");
			newFocus->relativePositionId = "ColonialArmy" + Home->getTag();
			newFocus->xPos = 0;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "\t\t\tOR = {\n";
			newFocus->bypass += "\t\t\t\t" + Home->getTag() + " = {\n";
			newFocus->bypass += "\t\t\t\t\tis_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t\thas_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t}\n";
			newFocus->bypass += "\t\t\t\tNOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "\t\t\t}\n";
			newFocus->bypass += "\t\t}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "\t\t\tfactor = 10\n";
			newFocus->aiWillDo += "\t\t\tmodifier = {\n";
			newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
			newFocus->aiWillDo += "\t\t\t\tstrength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "\t\t\t}\n";
			newFocus->aiWillDo += "\t\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\tcreate_wargoal = {\n";
			newFocus->completionReward += "\t\t\t\ttype = annex_everything\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + target->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Protectorate");
		}
	}
	if (targetColonies.size() >= 2)
	{
		auto target = targetColonies.back();

		auto possibleProtectorateCountryName = target->getName();
		string protectorateCountryName;
		if (possibleProtectorateCountryName)
		{
			protectorateCountryName = *possibleProtectorateCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine protectorate country name for absolutist focuses";
			protectorateCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Protectorate"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag(), hoi4Localisations);
			newFocus->id = "Protectorate" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "\t\t\t" + target->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "\t\t}";
			newFocus->prerequisites.push_back(
				 "= { focus = Protectorate" + Home->getTag() + targetColonies.front()->getTag() + " }");
			newFocus->relativePositionId = "Protectorate" + Home->getTag() + targetColonies.front()->getTag();
			newFocus->xPos = 0;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "\t\t\tOR = {\n";
			newFocus->bypass += "\t\t\t\t" + Home->getTag() + " = {\n";
			newFocus->bypass += "\t\t\t\t\tis_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t\thas_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t}\n";
			newFocus->bypass += "\t\t\t\tNOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "\t\t\t}\n";
			newFocus->bypass += "\t\t}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "\t\t\tfactor = 5\n";
			newFocus->aiWillDo += "\t\t\tmodifier = {\n";
			newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
			newFocus->aiWillDo += "\t\t\t\tstrength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "\t\t\t}\n";
			newFocus->aiWillDo += "\t\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\tcreate_wargoal = {\n";
			newFocus->completionReward += "\t\t\t\ttype = annex_everything\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + target->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Protectorate");
		}
	}

	if (const auto& originalFocus = loadedFocuses.find("TradeEmpire"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "ColonialInd" + Home->getTag();
		newFocus->xPos = -1;
		newFocus->yPos = 2;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus TradeEmpire");
	}

	if (const auto& originalFocus = loadedFocuses.find("IndHome"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "StrengthenHome" + Home->getTag();
		newFocus->xPos = 1;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus IndHome");
	}

	if (const auto& originalFocus = loadedFocuses.find("NationalHwy"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "IndHome" + Home->getTag();
		newFocus->xPos = -1;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus NationalHwy");
	}

	if (const auto& originalFocus = loadedFocuses.find("NatCollege"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "IndHome" + Home->getTag();
		newFocus->xPos = 1;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus NatCollege");
	}

	if (const auto& originalFocus = loadedFocuses.find("MilitaryBuildup"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "IndHome" + Home->getTag();
		newFocus->xPos = 2;
		newFocus->yPos = 2;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus MilitaryBuildup");
	}

	if (const auto& originalFocus = loadedFocuses.find("PrepTheBorder"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "StrengthenHome" + Home->getTag();
		newFocus->xPos = 4;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus PrepTheBorder");
	}

	if (const auto& originalFocus = loadedFocuses.find("NatSpirit"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "PrepTheBorder" + Home->getTag();
		newFocus->xPos = 0;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus NatSpirit");
	}

	// ANNEX
	if (annexationTargets.size() >= 1)
	{
		auto target = annexationTargets.front();

		auto possibleTargetCountryName = target->getName();
		string targetCountryName;
		if (possibleTargetCountryName)
		{
			targetCountryName = *possibleTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine target country name for absolutist focuses";
			targetCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Annex"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag(), hoi4Localisations);
			newFocus->id = "Annex" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "\t\t\t" + target->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "\t\t}";
			newFocus->prerequisites.push_back("= { focus = PrepTheBorder" + Home->getTag() + " }");
			newFocus->relativePositionId = "PrepTheBorder" + Home->getTag();
			newFocus->xPos = 2;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "\t\t\tOR = {\n";
			newFocus->bypass += "\t\t\t\t" + Home->getTag() + "= {\n";
			newFocus->bypass += "\t\t\t\t\tis_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t\thas_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t}\n";
			newFocus->bypass += "\t\t\t\tNOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "\t\t\t}\n";
			newFocus->bypass += "\t\t}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "\t\t\tfactor = 5\n";
			newFocus->aiWillDo += "\t\t\tmodifier = {\n";
			newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
			newFocus->aiWillDo += "\t\t\t\tstrength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "\t\t\t}\n";
			newFocus->aiWillDo += "\t\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\tcreate_wargoal = {\n";
			newFocus->completionReward += "\t\t\t\ttype = annex_everything\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + target->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Annex");
		}
	}
	if (annexationTargets.size() >= 2)
	{
		auto target = annexationTargets.back();

		auto possibleTargetCountryName = target->getName();
		string targetCountryName;
		if (possibleTargetCountryName)
		{
			targetCountryName = *possibleTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine target country name for absolutist focuses";
			targetCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Annex"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag(), hoi4Localisations);
			newFocus->id = "Annex" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "\t\t\t\"" + target->getTag() + "\" = { is_in_faction = no }\n";
			newFocus->available += "\t\t}";
			newFocus->prerequisites.push_back("= { focus = NatSpirit" + Home->getTag() + " }");
			newFocus->relativePositionId = "NatSpirit" + Home->getTag();
			newFocus->xPos = 1;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "\t\t\tOR = {\n";
			newFocus->bypass += "\t\t\t\t" + Home->getTag() + " = {\n";
			newFocus->bypass += "\t\t\t\t\tis_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t\thas_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "\t\t\t\t}\n";
			newFocus->bypass += "\t\t\t\tNOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "\t\t\t}\n";
			newFocus->bypass += "\t\t}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "\t\t\tfactor = 5\n";
			newFocus->aiWillDo += "\t\t\tmodifier = {\n";
			newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
			newFocus->aiWillDo += "\t\t\t\tstrength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "\t\t\t}\n";
			newFocus->aiWillDo += "\t\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\tcreate_wargoal = {\n";
			newFocus->completionReward += "\t\t\t\ttype = annex_everything\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + target->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Annex");
		}
	}
	nextFreeColumn += 2;
}

void HoI4FocusTree::addCommunistCoupBranch(shared_ptr<HoI4::Country> Home,
	 const vector<shared_ptr<HoI4::Country>>& coupTargets,
	 const std::set<std::string>& majorIdeologies,
	 HoI4::Localisation& hoi4Localisations)
{
	if (coupTargets.size() > 0)
	{
		if (const auto& originalFocus = loadedFocuses.find("Home_of_Revolution"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			newFocus->xPos = nextFreeColumn + static_cast<int>(coupTargets.size()) - 1;
			newFocus->yPos = 0;
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Home_of_Revolution");
		}

		for (unsigned int i = 0; i < 2; i++)
		{
			if (i < coupTargets.size())
			{
				auto possibleCoupCountryName = coupTargets[i]->getName();
				string coupCountryName;
				if (possibleCoupCountryName)
				{
					coupCountryName = *possibleCoupCountryName;
				}
				else
				{
					Log(LogLevel::Warning) << "Could not determine coup country name for communist coup focuses";
					coupCountryName.clear();
				}

				if (const auto& originalFocus = loadedFocuses.find("Influence_"); originalFocus != loadedFocuses.end())
				{
					auto newFocus =
						 originalFocus->second.makeTargetedCopy(Home->getTag(), coupTargets[i]->getTag(), hoi4Localisations);
					newFocus->id = "Influence_" + coupTargets[i]->getTag() + "_" + Home->getTag();
					newFocus->xPos = nextFreeColumn + i * 2;
					newFocus->yPos = 1;
					newFocus->completionReward += "= {\n";
					newFocus->completionReward += "\t\t\t" + coupTargets[i]->getTag() + " = {\n";
					if (majorIdeologies.contains("fascism"))
					{
						newFocus->completionReward += "\t\t\t\tif = {\n";
						newFocus->completionReward += "\t\t\t\t\tlimit = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t" + Home->getTag() + " = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t\thas_government = fascism\n";
						newFocus->completionReward += "\t\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\tadd_ideas = fascist_influence\n";
						newFocus->completionReward += "\t\t\t\t}\n";
					}
					if (majorIdeologies.contains("communism"))
					{
						newFocus->completionReward += "\t\t\t\tif = {\n";
						newFocus->completionReward += "\t\t\t\t\tlimit = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t" + Home->getTag() + " = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t\thas_government = communism\n";
						newFocus->completionReward += "\t\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\tadd_ideas = communist_influence\n";
						newFocus->completionReward += "\t\t\t\t}\n";
					}
					if (majorIdeologies.contains("democratic"))
					{
						newFocus->completionReward += "\t\t\t\tif = {\n";
						newFocus->completionReward += "\t\t\t\t\tlimit = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t" + Home->getTag() + " = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t\thas_government = democratic\n";
						newFocus->completionReward += "\t\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\tadd_ideas = democratic_influence\n";
						newFocus->completionReward += "\t\t\t\t}\n";
					}
					if (majorIdeologies.contains("absolutist"))
					{
						newFocus->completionReward += "\t\t\t\tif = {\n";
						newFocus->completionReward += "\t\t\t\t\tlimit = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t" + Home->getTag() + " = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t\thas_government = absolutist\n";
						newFocus->completionReward += "\t\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\tadd_ideas = absolutist_influence\n";
						newFocus->completionReward += "\t\t\t\t}\n";
					}
					if (majorIdeologies.contains("radical"))
					{
						newFocus->completionReward += "\t\t\t\tif = {\n";
						newFocus->completionReward += "\t\t\t\t\tlimit = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t" + Home->getTag() + " = {\n";
						newFocus->completionReward += "\t\t\t\t\t\t\thas_government = radical\n";
						newFocus->completionReward += "\t\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\t}\n";
						newFocus->completionReward += "\t\t\t\t\tadd_ideas = radical_influence\n";
						newFocus->completionReward += "\t\t\t\t}\n";
					}
					newFocus->completionReward += "\t\t\t\tcountry_event = { id = generic.1 }\n";
					newFocus->completionReward += "\t\t\t}\n";
					newFocus->completionReward += "\t\t}";
					focuses.push_back(newFocus);
				}
				else
				{
					throw std::runtime_error("Could not load focus Influence_");
				}

				if (const auto& originalFocus = loadedFocuses.find("Coup_"); originalFocus != loadedFocuses.end())
				{
					auto newFocus =
						 originalFocus->second.makeTargetedCopy(Home->getTag(), coupTargets[i]->getTag(), hoi4Localisations);
					newFocus->id = "Coup_" + coupTargets[i]->getTag() + "_" + Home->getTag();
					newFocus->prerequisites.push_back(
						 "= { focus = Influence_" + coupTargets[i]->getTag() + "_" + Home->getTag() + " }");
					newFocus->relativePositionId = "Influence_" + coupTargets[i]->getTag() + "_" + Home->getTag();
					newFocus->xPos = 0;
					newFocus->yPos = 1;
					newFocus->available = "= {\n";
					newFocus->available += "\t\t\t" + coupTargets[i]->getTag() + " = { communism > 0.5 }\n";
					newFocus->available += "\t\t}";
					newFocus->completionReward += "= {\n";
					newFocus->completionReward += "\t\t\t" + coupTargets[i]->getTag() + " = {\n";
					newFocus->completionReward += "\t\t\t\tstart_civil_war = {\n";
					newFocus->completionReward += "\t\t\t\t\tideology = communism\n";
					newFocus->completionReward += "\t\t\t\t\tsize = 0.5\n";
					newFocus->completionReward += "\t\t\t\t}\n";
					newFocus->completionReward += "\t\t\t}\n";
					newFocus->completionReward += "\t\t}";
					focuses.push_back(newFocus);
				}
				else
				{
					throw std::runtime_error("Could not load focus Coup_");
				}
			}
		}
		nextFreeColumn += 2 * static_cast<int>(coupTargets.size());
	}
	return;
}

void HoI4FocusTree::addCommunistWarBranch(shared_ptr<HoI4::Country> Home,
	 const vector<shared_ptr<HoI4::Country>>& warTargets,
	 HoI4::Events& events,
	 HoI4::Localisation& hoi4Localisations)
{
	if (warTargets.size() > 0)
	{

		if (const auto& originalFocus = loadedFocuses.find("StrengthCom"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			newFocus->xPos = nextFreeColumn + static_cast<int>(warTargets.size()) - 1;
			newFocus->yPos = 0;
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus StrengthCom");
		}

		if (const auto& originalFocus = loadedFocuses.find("Inter_Com_Pres"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			newFocus->relativePositionId = "StrengthCom" + Home->getTag();
			newFocus->xPos = 0;
			newFocus->yPos = 1;
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\tadd_named_threat = { threat = 2 name = " + newFocus->text + " }\n";
			newFocus->completionReward += "\t\t\tadd_political_power = 150\n";
			newFocus->completionReward += "\t\t}";
			// FIXME
			// maybe add some claims?
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Inter_Com_Pres");
		}

		for (unsigned int i = 0; i < 3; i++)
		{
			if (i < warTargets.size())
			{
				auto possibleWarTargetCountryName = warTargets[i]->getName();
				string warTargetCountryName;
				if (possibleWarTargetCountryName)
				{
					warTargetCountryName = *possibleWarTargetCountryName;
				}
				else
				{
					Log(LogLevel::Warning) << "Could not determine war target country name for communist war focuses";
					warTargetCountryName.clear();
				}

				int v1 = rand() % 12 + 1;
				int v2 = rand() % 12 + 1;
				if (const auto& originalFocus = loadedFocuses.find("War"); originalFocus != loadedFocuses.end())
				{
					auto newFocus =
						 originalFocus->second.makeTargetedCopy(Home->getTag(), warTargets[i]->getTag(), hoi4Localisations);
					newFocus->id = "War" + warTargets[i]->getTag() + Home->getTag();
					newFocus->available = "= {\n";
					newFocus->available += "\t\t\tdate > 1938." + to_string(v1) + "." + to_string(v2) + "\n";
					newFocus->available += "\t\t}";
					newFocus->xPos = nextFreeColumn + i * 2;
					newFocus->yPos = 2;
					newFocus->bypass = "= {\n";
					newFocus->bypass += "\t\t\t\t\thas_war_with = " + warTargets[i]->getTag() + "\n";
					newFocus->bypass += "\t\t\t\t}";
					newFocus->aiWillDo = "= {\n";
					newFocus->aiWillDo += "\t\t\tfactor = 5\n";
					newFocus->aiWillDo += "\t\t\tmodifier = {\n";
					newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
					newFocus->aiWillDo += "\t\t\t\tstrength_ratio = { tag = " + warTargets[i]->getTag() + " ratio < 1 }\n";
					newFocus->aiWillDo += "\t\t\t}";
					if (warTargets.size() > 1)
					{
						newFocus->aiWillDo += "\n";
						newFocus->aiWillDo += "\t\t\tmodifier = {\n";
						newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
						newFocus->aiWillDo += "\t\t\t\tOR = {\n";
						for (unsigned int i2 = 0; i2 < warTargets.size(); i2++)
						{
							if (i != i2)
								newFocus->aiWillDo += "\t\t\t\t\thas_war_with = " + warTargets[i2]->getTag() + "\n";
						}
						newFocus->aiWillDo += "\t\t\t\t}\n";
						newFocus->aiWillDo += "\t\t\t}";
					}
					newFocus->aiWillDo += "\n";
					newFocus->aiWillDo += "\t\t}";

					newFocus->completionReward += "= {\n";
					newFocus->completionReward +=
						 "\t\t\tadd_named_threat = { threat = 3 name = \"War with " + warTargetCountryName + "\" }\n";
					newFocus->completionReward += "\t\t\tcreate_wargoal = {\n";
					newFocus->completionReward += "\t\t\t\ttype = puppet_wargoal_focus\n";
					newFocus->completionReward += "\t\t\t\ttarget = " + warTargets[i]->getTag() + "\n";
					newFocus->completionReward += "\t\t\t}\n";
					newFocus->completionReward += "\t\t}";
					focuses.push_back(newFocus);
				}
				else
				{
					throw std::runtime_error("Could not load focus War");
				}
			}
		}
		nextFreeColumn += static_cast<int>(warTargets.size()) * 2;
	}
}

void HoI4FocusTree::addFascistAnnexationBranch(shared_ptr<HoI4::Country> Home,
	 const vector<shared_ptr<HoI4::Country>>& annexationTargets,
	 HoI4::Events& events,
	 HoI4::Localisation& hoi4Localisations)
{
	// The Following 'if' statement prevents converter from generating focuses if annexationTargets.size > 1
	// Keep this 'if' statement off until we figure out how to handle Fascist NF's
	// if (annexationTargets.size() >= 1)
	//{
	if (const auto& originalFocus = loadedFocuses.find("The_third_way"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		if (annexationTargets.size() >= 1)
		{
			newFocus->xPos = nextFreeColumn + static_cast<int>(annexationTargets.size()) - 1;
		}

		//'else' statement is there in case annexationTargets.size() is <1.  Need to fix in the future.
		else
		{
			newFocus->xPos = nextFreeColumn;
		}
		newFocus->yPos = 0;
		// FIXME
		// Need to get Drift Defense to work
		// in modified generic focus? (tk)
		// newFocus->completionReward += "\t\t\tdrift_defence_factor = 0.5\n";
		newFocus->completionReward += "= {\n";
		newFocus->completionReward += "\t\t\tadd_named_threat = { threat = 2 name = " + newFocus->text + " }\n";
		newFocus->completionReward += "\t\t\tadd_ideas = fascist_influence\n";
		newFocus->completionReward += "\t\t}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus The_third_way");
	}

	if (const auto& originalFocus = loadedFocuses.find("mil_march"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->relativePositionId = "The_third_way" + Home->getTag();
		newFocus->xPos = 0;
		newFocus->yPos = 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus mil_march");
	}

	for (unsigned int i = 0; i < annexationTargets.size(); i++)
	{
		auto possibleAnnexationTargetCountryName = annexationTargets[i]->getName();
		string annexationTargetCountryName;
		if (possibleAnnexationTargetCountryName)
		{
			annexationTargetCountryName = *possibleAnnexationTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine annexation target country name for fascist annexation focuses";
			annexationTargetCountryName.clear();
		}

		// int x = i * 3;
		// for random date
		int v1 = rand() % 5 + 1;
		int v2 = rand() % 5 + 1;

		if (const auto& originalFocus = loadedFocuses.find("_anschluss_"); originalFocus != loadedFocuses.end())
		{
			auto newFocus =
				 originalFocus->second.makeTargetedCopy(Home->getTag(), annexationTargets[i]->getTag(), hoi4Localisations);
			newFocus->id = Home->getTag() + "_anschluss_" + annexationTargets[i]->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "\t\t\t" + annexationTargets[i]->getTag() + " = {\n";
			newFocus->available += "\t\t\t\tis_in_faction = no\n";
			newFocus->available += "\t\t\t}\n";
			newFocus->available += "\t\t\tis_puppet = no\n";
			newFocus->available += "\t\t\tdate > 1937." + to_string(v1 + 5) + "." + to_string(v2 + 5) + "\n";
			newFocus->available += "\t\t}";
			newFocus->xPos = nextFreeColumn + i * 2;
			newFocus->yPos = 2;
			newFocus->completionReward += "= {\n";
			newFocus->completionReward +=
				 "\t\t\tadd_named_threat = { threat = 2 name = \"Union with " + annexationTargetCountryName + "\" }\n";
			newFocus->completionReward += "\t\t\tarmy_experience = 10\n";
			newFocus->completionReward += "\t\t\tif = {\n";
			newFocus->completionReward += "\t\t\t\tlimit = {\n";
			newFocus->completionReward += "\t\t\t\t\tcountry_exists = " + annexationTargets[i]->getTag() + "\n";
			newFocus->completionReward += "\t\t\t\t}\n";
			newFocus->completionReward += "\t\t\t\t" + annexationTargets[i]->getTag() + " = {\n";
			newFocus->completionReward +=
				 "\t\t\t\t\tcountry_event = NFEvents." + to_string(events.getCurrentNationFocusEventNum()) + "\n";
			newFocus->completionReward += "\t\t\t\t}\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);

			events.createAnnexEvent(*Home, *annexationTargets[i]);
		}
		else
		{
			throw std::runtime_error("Could not load focus _anschluss_");
		}
	}
	if (annexationTargets.size() >= 1)
	{
		nextFreeColumn += static_cast<int>(annexationTargets.size()) * 2;
	}
	else
	{
		nextFreeColumn += 2;
	}
	//}
}

void HoI4FocusTree::addFascistSudetenBranch(shared_ptr<HoI4::Country> Home,
	 const vector<shared_ptr<HoI4::Country>>& sudetenTargets,
	 const vector<vector<int>>& demandedStates,
	 HoI4::World& world,
	 HoI4::Localisation& hoi4Localisations)
{
	auto& events = world.getEvents();

	// if it can easily take these targets as they are not in an alliance, you can get annexation event

	if (const auto& originalFocus = loadedFocuses.find("expand_the_reich"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		if (sudetenTargets.size() == 1 || sudetenTargets.size() >= 2)
		{
			// if there are anschlusses, make this event require at least 1 anschluss, else, its the start of a tree
			for (unsigned int i = 0; i < 2; i++)
			{
				if (i < sudetenTargets.size())
				{
					//					newFocus->prerequisites.push_back("= { focus = " + Home->getTag() + "_anschluss_" +
					// sudetenTargets[i]->getTag() + " }");
				}
			}
			newFocus->xPos = nextFreeColumn + static_cast<int>(sudetenTargets.size()) - 1;
		}

		//'else' statement is there in case sudetenTargets.size() is <1.  Need to fix in the future.
		else
		{
			newFocus->xPos = nextFreeColumn;
		}
		newFocus->yPos = 0;
		newFocus->completionReward += "= {\n";
		newFocus->completionReward +=
			 "\t\t\tadd_named_threat = { threat = 3 name = " + newFocus->text + " }\n"; // give some claims or cores
		newFocus->completionReward += "\t\t\tadd_political_power = 150\n";
		newFocus->completionReward += "\t\t}";
		addFocus(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus expand_the_reich");
	}

	for (unsigned int i = 0; i < sudetenTargets.size(); i++)
	{
		auto possibleSudetenTargetCountryName = sudetenTargets[i]->getName();
		string sudetenTargetCountryName;
		if (possibleSudetenTargetCountryName)
		{
			sudetenTargetCountryName = *possibleSudetenTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine annexation target country name for fascist sudeten focuses";
			sudetenTargetCountryName.clear();
		}

		int v1 = rand() % 8 + 1;
		int v2 = rand() % 8 + 1;

		if (const auto& originalFocus = loadedFocuses.find("_sudeten_"); originalFocus != loadedFocuses.end())
		{
			auto newFocus =
				 originalFocus->second.makeTargetedCopy(Home->getTag(), sudetenTargets[i]->getTag(), hoi4Localisations);
			newFocus->id = Home->getTag() + "_sudeten_" + sudetenTargets[i]->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\tis_puppet = no\n";
			newFocus->available += "\t\t\tdate > 1938." + to_string(v1) + "." + to_string(v2) + "\n";
			newFocus->available += "\t\t}";
			newFocus->xPos = nextFreeColumn + 2 * i;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "  has_war_with = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->bypass += "}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\tadd_named_threat = { threat = 2 name = \"Demand Territory from " +
													sudetenTargetCountryName + "\" }\n";
			newFocus->completionReward += "\t\t\tarmy_experience = 10\n";
			newFocus->completionReward += "\t\t\tif = {\n";
			newFocus->completionReward += "\t\t\t\tlimit = {\n";
			newFocus->completionReward += "\t\t\t\t\tcountry_exists = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->completionReward += "\t\t\t\t}\n";
			newFocus->completionReward += "\t\t\t\t" + sudetenTargets[i]->getTag() + " = {\n";
			newFocus->completionReward +=
				 "\t\t\t\t\tcountry_event = NFEvents." + to_string(events.getCurrentNationFocusEventNum()) + "\n";
			newFocus->completionReward += "\t\t\t\t}\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			addFocus(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus _sudeten_");
		}

		// FINISH HIM
		if (const auto& originalFocus = loadedFocuses.find("_finish_"); originalFocus != loadedFocuses.end())
		{
			auto newFocus =
				 originalFocus->second.makeTargetedCopy(Home->getTag(), sudetenTargets[i]->getTag(), hoi4Localisations);
			newFocus->id = Home->getTag() + "_finish_" + sudetenTargets[i]->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "\t" + sudetenTargets[i]->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "\t\t}";
			newFocus->prerequisites.push_back(
				 "= { focus =  " + Home->getTag() + "_sudeten_" + sudetenTargets[i]->getTag() + " }");
			newFocus->xPos = nextFreeColumn + 2 * i;
			newFocus->yPos = 2;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "\t\thas_war_with = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->bypass += "\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward +=
				 "\t\t\tadd_named_threat = { threat = 3 name = \"Fate of " + sudetenTargetCountryName + "\" }\n";
			newFocus->completionReward += "\t\t\tcreate_wargoal = {\n";
			newFocus->completionReward += "\t\t\t\ttype = annex_everything\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			addFocus(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus _finish_");
		}

		// events
		events.createSudetenEvent(*Home, *sudetenTargets[i], demandedStates[i]);
	}
	nextFreeColumn += 2 * static_cast<int>(sudetenTargets.size());
}


void HoI4FocusTree::addGPWarBranch(shared_ptr<HoI4::Country> Home,
	 const vector<shared_ptr<HoI4::Country>>& newAllies,
	 const vector<shared_ptr<HoI4::Country>>& GCTargets,
	 const string& ideology,
	 HoI4::Events& events,
	 HoI4::Localisation& hoi4Localisations)
{
	int numAllies = static_cast<int>(newAllies.size());
	string ideologyShort = ideology.substr(0, 3);
	if (newAllies.size() > 0)
	{
		if (const auto& originalFocus = loadedFocuses.find("_Summit"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			newFocus->id = ideologyShort + "_Summit" + Home->getTag();
			newFocus->text = ideology + "_Summit";
			if (numAllies == 0)
			{
				newFocus->xPos = nextFreeColumn + static_cast<int>(newAllies.size());
			}
			else
			{
				newFocus->xPos = nextFreeColumn + static_cast<int>(newAllies.size()) - 1;
			}
			newFocus->yPos = 0;
			newFocus->completionReward += "= {\n";
			newFocus->completionReward +=
				 "\t\t\tadd_named_threat = { threat = 3 name = \"Call for the " + ideology + " Summit\" }\n";
			newFocus->completionReward += "\t\t\tadd_political_power = 150\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
			hoi4Localisations.copyFocusLocalisations("_Summit", newFocus->text);
			hoi4Localisations.updateLocalisationText(newFocus->text, "$TARGET", ideology);
			hoi4Localisations.updateLocalisationText(newFocus->text + "_desc", "$TARGET", ideology);
		}
		else
		{
			throw std::runtime_error("Could not load focus _Summit");
		}
	}

	unsigned int i = 0;
	for (auto newAlly: newAllies)
	{
		auto possibleAllyCountryName = newAlly->getName();
		string allyCountryName;
		if (possibleAllyCountryName)
		{
			allyCountryName = *possibleAllyCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine ally country name for GP alliance focuses";
			allyCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Alliance_"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(Home->getTag(), newAlly->getTag(), hoi4Localisations);
			newFocus->id = "Alliance_" + newAlly->getTag() + Home->getTag();
			newFocus->prerequisites.push_back("= { focus = " + ideologyShort + "_Summit" + Home->getTag() + " }");
			newFocus->relativePositionId = ideologyShort + "_Summit" + Home->getTag();
			if (numAllies == 1)
			{
				newFocus->xPos = 0;
			}
			else
			{
				newFocus->xPos = (i * 2) - 1;
			}
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "\t\t\tOR = {\n";
			newFocus->bypass += "\t\t\t\t" + Home->getTag() + " = { is_in_faction_with = " + newAlly->getTag() + "}\n";
			newFocus->bypass += "\t\t\t\thas_war_with = " + newAlly->getTag() + "\n";
			newFocus->bypass += "\t\t\t\tNOT = { country_exists = " + newAlly->getTag() + " }\n";
			newFocus->bypass += "\t\t\t}\n";
			newFocus->bypass += "\t\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "\t\t\t" + newAlly->getTag() + " = {\n";
			newFocus->completionReward += "\t\t\t\tcountry_event = { hours = 6 id = NFEvents." +
													to_string(events.getCurrentNationFocusEventNum()) + " }\n";
			newFocus->completionReward +=
				 "\t\t\t\tadd_opinion_modifier = { target = " + Home->getTag() + " modifier = positive_50 }\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);

			events.createFactionEvents(*Home, *newAlly);
			i++;
		}
		else
		{
			throw std::runtime_error("Could not load focus Alliance_");
		}
	}

	i = 0;
	for (auto GC: GCTargets)
	{
		auto possibleWarTargetCountryName = GC->getName();
		string warTargetCountryName;
		if (possibleWarTargetCountryName)
		{
			warTargetCountryName = *possibleWarTargetCountryName;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not determine war target country name for GP war focuses";
			warTargetCountryName.clear();
		}

		// figuring out location of WG
		if (const auto& originalFocus = loadedFocuses.find("GP_War"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			if (newAllies.size() > 0)
			{
				for (unsigned int i2 = 0; i2 < newAllies.size(); i2++)
				{
					newFocus->prerequisites.push_back(
						 "= { focus = Alliance_" + newAllies[i2]->getTag() + Home->getTag() + " }");
				}
			}
			int v1 = rand() % 12 + 1;
			int v2 = rand() % 12 + 1;
			newFocus->id = "GP_War" + GC->getTag() + Home->getTag();
			newFocus->text += GC->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "\t\t\thas_war = no\n";
			newFocus->available += "\t\t\tdate > 1939." + to_string(v1) + "." + to_string(v2) + "\n";
			newFocus->available += "\t\t}";
			if (newAllies.size() > 0)
			{
				newFocus->relativePositionId = ideologyShort + "_Summit" + Home->getTag();
				newFocus->xPos = 0;
				newFocus->yPos = 2;
			}
			else
			{
				newFocus->xPos = nextFreeColumn;
				newFocus->yPos = 0;
			}
			newFocus->bypass = "= {\n";
			newFocus->bypass += "\t\t   has_war_with = " + GC->getTag() + "\n";
			newFocus->bypass += "\t\t}";
			newFocus->aiWillDo = "= {\n";
			newFocus->aiWillDo += "\t\t\tfactor = " + to_string(10 - GCTargets.size() * 5) + "\n";
			newFocus->aiWillDo += "\t\t\tmodifier = {\n";
			newFocus->aiWillDo += "\t\t\t\t\tfactor = 0\n";
			newFocus->aiWillDo += "\t\t\t\t\tstrength_ratio = { tag = " + GC->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "\t\t\t}";
			if (GCTargets.size() > 1)
			{
				newFocus->aiWillDo = "\n";

				// make ai have this as a 0 modifier if they are at war
				newFocus->aiWillDo += "\t\t\tmodifier = {\n";
				newFocus->aiWillDo += "\t\t\t\tfactor = 0\n";
				newFocus->aiWillDo += "\t\t\t\tOR = {\n";
				for (unsigned int i2 = 0; i2 < GCTargets.size(); i2++)
				{
					if (GC != GCTargets[i2])
					{
						newFocus->aiWillDo += "\t\t\t\t\thas_war_with = " + GCTargets[i2]->getTag() + "\n";
					}
				}
				newFocus->aiWillDo += "\t\t\t\t}\n";
				newFocus->aiWillDo += "\t\t\t}";
			}
			newFocus->aiWillDo += "\n";
			newFocus->aiWillDo += "\t\t}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward +=
				 "\t\t\tadd_named_threat = { threat = 5 name = \"War with " + warTargetCountryName + "\" }\n";
			newFocus->completionReward += "\t\t\tdeclare_war_on = {\n";
			newFocus->completionReward += "\t\t\t\ttype = puppet_wargoal_focus\n";
			newFocus->completionReward += "\t\t\t\ttarget = " + GC->getTag() + "\n";
			newFocus->completionReward += "\t\t\t}\n";
			newFocus->completionReward += "\t\t}";
			focuses.push_back(newFocus);
			hoi4Localisations.copyFocusLocalisations("GPWar", newFocus->text);
			hoi4Localisations.updateLocalisationText(newFocus->text, "$TARGET", GC->getTag());
			hoi4Localisations.updateLocalisationText(newFocus->text + "_desc", "$TARGET", GC->getTag());
			i++;
		}
		else
		{
			throw std::runtime_error("Could not load focus GP_War");
		}
	}
	nextFreeColumn += 2 * static_cast<int>(max(newAllies.size(), GCTargets.size()));
}


std::map<std::string, int> HoI4FocusTree::determineEnemyCoreHolders(std::shared_ptr<HoI4::Country> theCountry,
	 const std::map<int, HoI4::State>& states
){
	std::map<std::string, int> coreHolders;

	for (const auto& stateID: theCountry->getCoreStates())
	{
		const auto& stateItr = states.find(stateID);
		if (stateItr == states.end())
		{
			continue;
		}
		const auto& state = stateItr->second;
		if (const auto& owner = state.getOwner(); owner != theCountry->getTag())
		{
			if (theCountry->isEligibleEnemy(owner))
			{
				int numProvinces = std::min(static_cast<int>(state.getProvinces().size()), 10);
				const auto& [existing, inserted] = coreHolders.insert(make_pair(owner, numProvinces));
				if (!inserted)
				{
				  existing->second += numProvinces;
				}
			}
		}
	}

	return coreHolders;
}

int HoI4FocusTree::calculateNumEnemyOwnedCores(std::shared_ptr<HoI4::Country> theCountry,
	 const std::map<int, HoI4::State>& states
){
	int sumUnownedCores = 0;

	for (const auto& [unused, numCores]: determineEnemyCoreHolders(theCountry, states))
	{
		sumUnownedCores += numCores;
	}

	return sumUnownedCores;
}


std::map<std::string, int> HoI4FocusTree::addReconquestBranch(std::shared_ptr<HoI4::Country> theCountry,
	 int& numWarsWithNeighbors,
	 const std::set<std::string>& majorIdeologies,
	 const std::map<int, HoI4::State>& states,
	 HoI4::Localisation& hoi4Localisations)
{
	const auto& coreHolders = determineEnemyCoreHolders(theCountry, states);
	if (coreHolders.empty())
	{
		return coreHolders;
	}

	int sumUnownedCores = calculateNumEnemyOwnedCores(theCountry, states);

	numWarsWithNeighbors = std::min(static_cast<int>(coreHolders.size()), 4);

	if (const auto& originalFocus = loadedFocuses.find("reclaim_cores"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(theCountry->getTag());
		newFocus->selectEffect = "= {\n";
		for (const auto& [tag, numProvinces]: coreHolders)
		{
			newFocus->selectEffect += "\t\t\tset_variable = { unowned_cores_@" + tag + " = " + std::to_string(numProvinces) + " }\n";
		}
		newFocus->selectEffect += "\t\t\tset_variable = { revanchism = " + std::to_string(0.00001*sumUnownedCores) + " }\n";
		newFocus->selectEffect += "\t\t\tset_variable = { revanchism_stab = " + std::to_string(-0.000001*sumUnownedCores) + " }\n";
		newFocus->selectEffect += "\t\t\tadd_dynamic_modifier = { modifier = revanchism }\n";
		if (majorIdeologies.contains("fascism"))
		{
			newFocus->selectEffect += "\t\t\tadd_dynamic_modifier = { modifier = revanchism_fasc }\n";
		}
		newFocus->selectEffect += "\t\t}\n";
		newFocus->xPos = nextFreeColumn + static_cast<int>(coreHolders.size()) - 1;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus reclaim_cores");
	}

	std::string fascistGovernmentCheck;
	fascistGovernmentCheck = "modifier = {\n";
	fascistGovernmentCheck += "\t\t\t\tfactor = 5\n";
	fascistGovernmentCheck += "\t\t\t\thas_government = fascism\n";
	fascistGovernmentCheck += "\t\t\t}";

	for (const auto& [target, numProvinces]: coreHolders)
	{
		const auto& aiChance = std::to_string(std::max(static_cast<int>(0.1 * numProvinces), 1));

		if (const auto& originalFocus = loadedFocuses.find("raise_matter"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(theCountry->getTag(), target, hoi4Localisations);
			newFocus->xPos = nextFreeColumn;
			if (majorIdeologies.contains("fascism"))
			{
				std::string fascismPopularityCheck;
				fascismPopularityCheck = "modifier = {\n";
				fascismPopularityCheck += "\t\t\t\tfactor = 0\n";
				fascismPopularityCheck += "\t\t\t\tNOT = { has_government = fascism }\n";
				fascismPopularityCheck += "\t\t\t\tNOT = { fascism > 0.35 }\n";
				fascismPopularityCheck += "\t\t\t}";
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCPOP", fascismPopularityCheck);
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCGOV", fascistGovernmentCheck);
			}
			else
			{
				newFocus->completionReward = "= {\n";
				newFocus->completionReward += "\t\t\tadd_stability = 0.0001\n";
				newFocus->completionReward += "\t\t\tadd_political_power = 150\n";
				newFocus->completionReward += "\t\t\tadd_timed_idea = { idea = generic_military_industry days = 180 }\n";
				newFocus->completionReward += "\t\t}";
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCPOP");
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCGOV");
			}
			newFocus->updateFocusElement(newFocus->available, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$POPULARITY", std::to_string(0.000001*numProvinces));
			newFocus->updateFocusElement(newFocus->bypass, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$REVANCHISM", aiChance);
			focuses.push_back(newFocus);
			nextFreeColumn += 2;
		}
		else
		{
			throw std::runtime_error("Could not load focus raise_matter");
		}

		if (const auto& originalFocus = loadedFocuses.find("build_public_support"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(theCountry->getTag(), target, hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = raise_matter" + theCountry->getTag() + target + " }");
			newFocus->relativePositionId += target;
			if (majorIdeologies.contains("fascism"))
			{
				std::string fascismPopularityCheck;
				fascismPopularityCheck = "modifier = {\n";
				fascismPopularityCheck += "\t\t\t\tfactor = 0\n";
				fascismPopularityCheck += "\t\t\t\tNOT = { has_government = fascism }\n";
				fascismPopularityCheck += "\t\t\t\tNOT = { fascism > 0.4 }\n";
				fascismPopularityCheck += "\t\t\t}";
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCPOP", fascismPopularityCheck);
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCGOV", fascistGovernmentCheck);
			}
			else
			{
				newFocus->completionReward = " = {\n";
				newFocus->completionReward += "\t\t\tadd_stability = 0.0001\n";
				newFocus->completionReward += "\t\t\tadd_war_support = $WARSUPPORT\n";
				newFocus->completionReward += "\t\t\tadd_timed_idea = { idea = generic_rapid_mobilization days = 180 }\n";
				newFocus->completionReward += "\t\t}";
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCPOP");
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCGOV");
			}
			newFocus->updateFocusElement(newFocus->available, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$POPULARITY", std::to_string(0.000001*numProvinces));
			newFocus->updateFocusElement(newFocus->completionReward, "$WARSUPPORT", std::to_string(0.00001*numProvinces));
			newFocus->updateFocusElement(newFocus->bypass, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TAG", theCountry->getTag());
			newFocus->updateFocusElement(newFocus->aiWillDo, "$REVANCHISM", aiChance);
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus build_public_support");
		}

		if (const auto& originalFocus = loadedFocuses.find("territory_or_war"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(theCountry->getTag(), target, hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = build_public_support" + theCountry->getTag() + target + " }");
			newFocus->relativePositionId += target;
			if (majorIdeologies.contains("fascism"))
			{
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCGOV", fascistGovernmentCheck);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCGOV");
			}
			newFocus->updateFocusElement(newFocus->available, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->bypass, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TAG", theCountry->getTag());
			newFocus->updateFocusElement(newFocus->aiWillDo, "$REVANCHISM", aiChance);
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus territory_or_war");
		}

		if (const auto& originalFocus = loadedFocuses.find("war_plan"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(theCountry->getTag(), target, hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = territory_or_war" + theCountry->getTag() + target + " }");
			newFocus->relativePositionId += target;
			if (majorIdeologies.contains("fascism"))
			{
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCGOV", fascistGovernmentCheck);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCGOV");
			}
			newFocus->updateFocusElement(newFocus->available, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->bypass, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TAG", theCountry->getTag());
			newFocus->updateFocusElement(newFocus->aiWillDo, "$REVANCHISM", aiChance);
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus war_plan");
		}

		if (const auto& originalFocus = loadedFocuses.find("declare_war"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(theCountry->getTag(), target, hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = war_plan" + theCountry->getTag() + target + " }");
			newFocus->relativePositionId += target;
			if (majorIdeologies.contains("fascism"))
			{
				newFocus->updateFocusElement(newFocus->aiWillDo, "#FASCGOV", fascistGovernmentCheck);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->aiWillDo, "#FASCGOV");
			}
			newFocus->updateFocusElement(newFocus->available, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->bypass, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TAG", theCountry->getTag());
			newFocus->updateFocusElement(newFocus->aiWillDo, "$REVANCHISM", std::to_string(std::max(static_cast<int>(numProvinces), 1)));
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus declare_war");
		}

		if (const auto& originalFocus = loadedFocuses.find("cleanup_revanchism"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(theCountry->getTag(), target, hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = declare_war" + theCountry->getTag() + target + " }");
			newFocus->relativePositionId += target;
			newFocus->updateFocusElement(newFocus->available, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$TARGET", target);
			newFocus->updateFocusElement(newFocus->completionReward, "$REVANCHISM", std::to_string(0.000005*numProvinces));
			newFocus->updateFocusElement(newFocus->completionReward, "$STABILITY", std::to_string(0.0000005*numProvinces));
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus cleanup_revanchism");
		}
	}

	return coreHolders;
}

int HoI4FocusTree::getMaxConquerValue(const std::vector<HoI4::AIStrategy>& conquerStrategies)
{
	const auto& maxConquerValueItr = std::max_element(conquerStrategies.begin(), conquerStrategies.end(), [](const HoI4::AIStrategy& a, const HoI4::AIStrategy& b) {
		return a.getValue() < b.getValue();
	});
	return maxConquerValueItr->getValue();
}

std::set<std::string> HoI4FocusTree::addConquerBranch(
	 std::shared_ptr<HoI4::Country> theCountry,
	 int& numWarsWithNeighbors,
	 const std::set<std::string>& majorIdeologies,
	 const std::map<std::string, int>& coreHolders,
	 HoI4::Localisation& hoi4Localisations)
{
	std::string tag = theCountry->getTag();
	std::set<std::string> conquerTags;

	const auto& conquerStrategies = theCountry->getConquerStrategies();
	if (conquerStrategies.empty())
	{
		return conquerTags;
	}

	const auto& maxConquerValue = getMaxConquerValue(conquerStrategies);
	for (const auto& strategy: conquerStrategies)
	{
		if (strategy.getID() == tag)
		{
			continue;
		}

		int aiChance = 10 * strategy.getValue() / maxConquerValue;
		if (hasMaxNeighborWars(numWarsWithNeighbors) || aiChance < 1)
		{
			break;
		}
		if (!theCountry->isEligibleEnemy(strategy.getID()))
		{
			continue;
		}
		if (coreHolders.contains(strategy.getID()))
		{
			continue;
		}

		conquerTags.insert(strategy.getID());
		numWarsWithNeighbors++;
		auto relations = theCountry->getRelations(strategy.getID());
		date startDate = date("1936.01.01");
		startDate.increaseByMonths((200 + relations->getRelations()) / 8);

		if (const auto& originalFocus = loadedFocuses.find("border_disputes_conquer"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
			newFocus->relativePositionId.clear();
			if (majorIdeologies.contains("communism"))
			{
				std::string comm;
				comm = "if = {\n";
				comm += "\t\t\t\t\t\tlimit = { ROOT = { has_government = communism } }\n";
				comm += "\t\t\t\t\t\tpotential_communist_puppet_target = yes\n";
				comm += "\t\t\t\t\t}";
				newFocus->updateFocusElement(newFocus->available, "#COMMUNISM", comm);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->available, "#COMMUNISM");
			}
			if (majorIdeologies.contains("fascism"))
			{
				std::string fasc;
				if (!majorIdeologies.contains("communism"))
				{
					fasc = "if = {\n";
				}
				else
				{
					fasc = "else_if = {\n";
				}
				fasc += "\t\t\t\t\t\tlimit = { ROOT = { has_government = fascism } }\n";
				fasc += "\t\t\t\t\t\tpotential_fascist_annex_target = yes\n";
				fasc += "\t\t\t\t\t}";
				newFocus->updateFocusElement(newFocus->available, "#FASCISM", fasc);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->available, "#FASCISM");
			}
			if (majorIdeologies.contains("radical"))
			{
				std::string rad;
				if (!majorIdeologies.contains("communism") && !majorIdeologies.contains("fascism"))
				{
					rad = "if = {\n";
				}
				else
				{
					rad = "else_if = {\n";
				}
				rad += "\t\t\t\t\t\tlimit = { ROOT = { has_government = radical } }\n";
				rad += "\t\t\t\t\t\tpotential_radical_annex_target = yes\n";
				rad += "\t\t\t\t\t}";
				newFocus->updateFocusElement(newFocus->available, "#RADICAL", rad);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->available, "#RADICAL");
			}
			if (majorIdeologies.contains("communism") || majorIdeologies.contains("fascism") || majorIdeologies.contains("radical"))
			{
				std::string els;
				els = "else = {\n";
				els += "\t\t\t\t\t\thidden_trigger = { always = no }\n";
				els += "\t\t\t\t\t}";
				newFocus->updateFocusElement(newFocus->available, "#ELSE", els);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->available, "#ELSE");
			}
			newFocus->updateFocusElement(newFocus->available, "$TARGET", strategy.getID());
			newFocus->xPos = nextFreeColumn;
			newFocus->yPos = 0;
			newFocus->updateFocusElement(newFocus->aiWillDo, "$AICHANCE", to_string(aiChance));
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", strategy.getID());
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus border_disputes");
		}

		if (const auto& originalFocus = loadedFocuses.find("prepare_for_war_conquer"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = border_disputes_conquer" + tag + strategy.getID() + " }");
			newFocus->relativePositionId += strategy.getID();
			newFocus->updateFocusElement(newFocus->available, "$STARTDATE", startDate.toString());
			newFocus->updateFocusElement(newFocus->available, "$TARGET", strategy.getID());
			newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", strategy.getID());
			newFocus->updateFocusElement(newFocus->selectEffect, "var:ROOT.neighbor_war_defender", strategy.getID());
			newFocus->updateFocusElement(newFocus->completionReward, "var:neighbor_war_defender", strategy.getID());
			newFocus->updateFocusElement(newFocus->bypass, "var:neighbor_war_defender", strategy.getID());
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus prepare_for_war");
		}

		if (const auto& originalFocus = loadedFocuses.find("neighbor_war_conquer"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(tag, strategy.getID(), hoi4Localisations);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = prepare_for_war_conquer" + tag + strategy.getID() + " }");
			newFocus->relativePositionId += strategy.getID();
			newFocus->updateFocusElement(newFocus->available, "var:neighbor_war_defender", strategy.getID());
			newFocus->updateFocusElement(newFocus->available, "var:ROOT.neighbor_war_defender", strategy.getID());
			if (majorIdeologies.contains("communism"))
			{
				std::string comm;
				comm = "else_if = {\n";
				comm += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_communist_puppet_target = yes } }\n";
				comm += "\t\t\t\tdeclare_war_on = {\n";
				comm += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
				comm += "\t\t\t\t\ttype = puppet_wargoal_focus\n";
				comm += "\t\t\t\t}\n";
				comm += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
				comm += "\t\t\t}";
				newFocus->updateFocusElement(newFocus->completionReward, "#COMMUNISM", comm);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->completionReward, "#COMMUNISM");
			}
			if (majorIdeologies.contains("fascism"))
			{
				std::string fasc;
				fasc = "else_if = {\n";
				fasc += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_fascist_annex_target = yes } }\n";
				fasc += "\t\t\t\tdeclare_war_on = {\n";
				fasc += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
				fasc += "\t\t\t\t\ttype = annex_everything\n";
				fasc += "\t\t\t\t}\n";
				fasc += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
				fasc += "\t\t\t}";
				newFocus->updateFocusElement(newFocus->completionReward, "#FASCISM", fasc);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->completionReward, "#FASCISM");
			}
			if (majorIdeologies.contains("radical"))
			{
				std::string rad;
				rad = "else_if = {\n";
				rad += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_radical_annex_target = yes } }\n";
				rad += "\t\t\t\tdeclare_war_on = {\n";
				rad += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
				rad += "\t\t\t\t\ttype = annex_everything\n";
				rad += "\t\t\t\t}\n";
				rad += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
				rad += "\t\t\t}";
				newFocus->updateFocusElement(newFocus->completionReward, "#RADICAL", rad);
			}
			else
			{
				newFocus->removePlaceholder(newFocus->completionReward, "#RADICAL");
			}
			newFocus->updateFocusElement(newFocus->completionReward, "var:neighbor_war_defender", strategy.getID());
			newFocus->updateFocusElement(newFocus->completionReward, "var:ROOT.neighbor_war_defender", strategy.getID());
			newFocus->updateFocusElement(newFocus->bypass, "var:neighbor_war_defender", strategy.getID());
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus neighbor_war");
		}

		nextFreeColumn += 2;
	}

	return conquerTags;
}

void HoI4FocusTree::addNeighborWarBranch(const string& tag,
	 const shared_ptr<HoI4::Country>& targetNeighbors,
	 const string& targetName,
	 const date& startDate,
	 const std::set<std::string>& majorIdeologies,
	 HoI4::Localisation& hoi4Localisations)
{
	if (const auto& originalFocus = loadedFocuses.find("border_disputes_nw"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus =
			 originalFocus->second.makeTargetedCopy(tag, targetNeighbors->getTag(), hoi4Localisations);
		newFocus->relativePositionId.clear();
		if (majorIdeologies.contains("communism"))
		{
			std::string comm;
			comm = "if = {\n";
			comm += "\t\t\t\t\t\tlimit = { ROOT = { has_government = communism } }\n";
			comm += "\t\t\t\t\t\tpotential_communist_puppet_target = yes\n";
			comm += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#COMMUNISM", comm);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#COMMUNISM");
		}
		if (majorIdeologies.contains("fascism"))
		{
			std::string fasc;
			if (!majorIdeologies.contains("communism"))
			{
				fasc = "if = {\n";
			}
			else
			{
				fasc = "else_if = {\n";
			}
			fasc += "\t\t\t\t\t\tlimit = { ROOT = { has_government = fascism } }\n";
			fasc += "\t\t\t\t\t\tpotential_fascist_annex_target = yes\n";
			fasc += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#FASCISM", fasc);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#FASCISM");
		}
		if (majorIdeologies.contains("radical"))
		{
			std::string rad;
			if (!majorIdeologies.contains("communism") && !majorIdeologies.contains("fascism"))
			{
				rad = "if = {\n";
			}
			else
			{
				rad = "else_if = {\n";
			}
			rad += "\t\t\t\t\t\tlimit = { ROOT = { has_government = radical } }\n";
			rad += "\t\t\t\t\t\tpotential_radical_annex_target = yes\n";
			rad += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#RADICAL", rad);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#RADICAL");
		}
		if (majorIdeologies.contains("communism") || majorIdeologies.contains("fascism") || majorIdeologies.contains("radical"))
		{
			std::string els;
			els = "else = {\n";
			els += "\t\t\t\t\t\thidden_trigger = { always = no }\n";
			els += "\t\t\t\t\t}";
			newFocus->updateFocusElement(newFocus->available, "#ELSE", els);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->available, "#ELSE");
		}
		newFocus->updateFocusElement(newFocus->available, "$TARGET", targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->aiWillDo, "$TARGET", targetNeighbors->getTag());
		newFocus->selectEffect.clear();
		newFocus->xPos = nextFreeColumn;
		newFocus->yPos = 0;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus border_disputes");
	}

	if (const auto& originalFocus = loadedFocuses.find("prepare_for_war_nw"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus =
			 originalFocus->second.makeTargetedCopy(tag, targetNeighbors->getTag(), hoi4Localisations);
		newFocus->prerequisites.clear();
		newFocus->prerequisites.push_back("= { focus = border_disputes_nw" + tag + targetNeighbors->getTag() + " }");
		newFocus->relativePositionId += targetNeighbors->getTag();
		newFocus->updateFocusElement(newFocus->available, "$TARGET", targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->selectEffect, "var:ROOT.neighbor_war_defender", targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->completionReward, "var:neighbor_war_defender", targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->bypass, "var:neighbor_war_defender", targetNeighbors->getTag());
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus prepare_for_war");
	}

	if (const auto& originalFocus = loadedFocuses.find("neighbor_war_nw"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus =
			 originalFocus->second.makeTargetedCopy(tag, targetNeighbors->getTag(), hoi4Localisations);
		newFocus->prerequisites.clear();
		newFocus->prerequisites.push_back("= { focus = prepare_for_war_nw" + tag + targetNeighbors->getTag() + " }");
		newFocus->relativePositionId += targetNeighbors->getTag();
		newFocus->updateFocusElement(newFocus->available, "var:neighbor_war_defender", targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->available, "var:ROOT.neighbor_war_defender", targetNeighbors->getTag());
		if (majorIdeologies.contains("communism"))
		{
			std::string comm;
			comm = "else_if = {\n";
			comm += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_communist_puppet_target = yes } }\n";
			comm += "\t\t\t\tdeclare_war_on = {\n";
			comm += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
			comm += "\t\t\t\t\ttype = puppet_wargoal_focus\n";
			comm += "\t\t\t\t}\n";
			comm += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
			comm += "\t\t\t}";
			newFocus->updateFocusElement(newFocus->completionReward, "#COMMUNISM", comm);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->completionReward, "#COMMUNISM");
		}
		if (majorIdeologies.contains("fascism"))
		{
			std::string fasc;
			fasc += "else_if = {\n";
			fasc += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_fascist_annex_target = yes } }\n";
			fasc += "\t\t\t\tdeclare_war_on = {\n";
			fasc += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
			fasc += "\t\t\t\t\ttype = annex_everything\n";
			fasc += "\t\t\t\t}\n";
			fasc += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
			fasc += "\t\t\t}";
			newFocus->updateFocusElement(newFocus->completionReward, "#FASCISM", fasc);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->completionReward, "#FASCISM");
		}
		if (majorIdeologies.contains("radical"))
		{
			std::string rad;
			rad += "else_if = {\n";
			rad += "\t\t\t\tlimit = { var:neighbor_war_defender = { potential_radical_annex_target = yes } }\n";
			rad += "\t\t\t\tdeclare_war_on = {\n";
			rad += "\t\t\t\t\ttarget = var:neighbor_war_defender\n";
			rad += "\t\t\t\t\ttype = annex_everything\n";
			rad += "\t\t\t\t}\n";
			rad += "\t\t\t\tadd_named_threat = { threat = 3 name = neighbor_war_NF_threat }\n";
			rad += "\t\t\t}";
			newFocus->updateFocusElement(newFocus->completionReward, "#RADICAL", rad);
		}
		else
		{
			newFocus->removePlaceholder(newFocus->completionReward, "#RADICAL");
		}
		newFocus->updateFocusElement(newFocus->completionReward, "var:neighbor_war_defender", targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->completionReward,
			 "var:ROOT.neighbor_war_defender",
			 targetNeighbors->getTag());
		newFocus->updateFocusElement(newFocus->bypass, "var:neighbor_war_defender", targetNeighbors->getTag());
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus neighbor_war");
	}

	nextFreeColumn += 2;
}

void HoI4FocusTree::addIntegratePuppetsBranch(const std::string& tag,
	 const std::set<std::string>& puppetTags,
	 HoI4::Localisation& hoi4Localisations)
{
	if (const auto& originalFocus = loadedFocuses.find("integrate_satellite"); originalFocus != loadedFocuses.end())
	{
		int yPos = 0;

		for (const auto& puppet: puppetTags)
		{
			shared_ptr<HoI4Focus> newFocus =
				 originalFocus->second.makeTargetedCopy(tag, puppet, hoi4Localisations);
			newFocus->xPos = nextFreeColumn;
			newFocus->yPos = yPos;
			newFocus->updateFocusElement(newFocus->selectEffect, "#TARGET", puppet);
			newFocus->updateFocusElement(newFocus->bypass, "#TARGET", puppet);
			newFocus->updateFocusElement(newFocus->completionReward, "#TARGET", puppet);
			focuses.push_back(newFocus);

			yPos++;
		}
	}
	else
	{
		throw std::runtime_error("Could not load focus integrate_satellite");
	}

	nextFreeColumn += 2;
}

void HoI4FocusTree::removeFocus(const string& id)
{
	focuses.erase(std::remove_if(focuses.begin(),
							focuses.end(),
							[id](std::shared_ptr<HoI4Focus> focus) {
								return focus->id == id;
							}),
		 focuses.end());
}