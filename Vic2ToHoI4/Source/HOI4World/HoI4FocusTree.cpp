/*Copyright (c) 2018 The Paradox Game Converters Project
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



#include "HoI4FocusTree.h"
#include "HoI4Country.h"
#include "HoI4Focus.h"
#include "HoI4Localisation.h"
#include "HoI4World.h"
#include "../Configuration.h"
#include "../V2World/Party.h"
#include "../V2World/Country.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include <fstream>
using namespace std;



//this is used to cache focuses that can be just loaded from a file
static std::map<std::string, HoI4Focus> loadedFocuses;



HoI4FocusTree::HoI4FocusTree(const HoI4::Country& country):
	srcCountryTag(country.getSourceCountry().getTag()),
	dstCountryTag(country.getTag())
{
}


void HoI4FocusTree::addGenericFocusTree(const set<string>& majorIdeologies)
{
	confirmLoadedFocuses();

	if (const auto& originalFocus = loadedFocuses.find("army_effort"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus army_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("equipment_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus equipment_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("motorization_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus motorization_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("doctrine_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus doctrine_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("equipment_effort_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus equipment_effort_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("mechanization_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus mechanization_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("doctrine_effort_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus doctrine_effort_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("equipment_effort_3"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus equipment_effort_3");
	}

	if (const auto& originalFocus = loadedFocuses.find("armor_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus armor_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("special_forces"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus special_forces");
	}

	if (const auto& originalFocus = loadedFocuses.find("aviation_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus aviation_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("fighter_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus fighter_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("bomber_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus bomber_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("aviation_effort_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus aviation_effort_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("CAS_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus CAS_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("rocket_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus rocket_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("NAV_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus NAV_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("naval_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus naval_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("flexible_navy"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus flexible_navy");
	}

	if (const auto& originalFocus = loadedFocuses.find("large_navy"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus large_navy");
	}

	if (const auto& originalFocus = loadedFocuses.find("submarine_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus submarine_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("cruiser_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus cruiser_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("destroyer_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus destroyer_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("capital_ships_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus capital_ships_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("industrial_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->aiWillDo = "= {\n";
		newFocus->aiWillDo += "			factor = 3\n";
		newFocus->aiWillDo += "			modifier = {\n";
		newFocus->aiWillDo += "				factor = 0\n";
		newFocus->aiWillDo += "				date < 1939.1.1\n";
		newFocus->aiWillDo += "				OR = {\n";
		newFocus->aiWillDo += "					# we also dont want tiny nations to go crazy with slots right away\n";
		newFocus->aiWillDo += "					num_of_controlled_states < 2\n";
		newFocus->aiWillDo += "				}\n";
		newFocus->aiWillDo += "			}\n";
		newFocus->aiWillDo += "		}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus industrial_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("construction_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus construction_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("production_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus production_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("construction_effort_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus construction_effort_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("production_effort_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus production_effort_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("infrastructure_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus infrastructure_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("production_effort_3"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus production_effort_3");
	}

	if (const auto& originalFocus = loadedFocuses.find("infrastructure_effort_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus infrastructure_effort_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("construction_effort_3"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus construction_effort_3");
	}

	if (const auto& originalFocus = loadedFocuses.find("nuclear_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus nuclear_effort");
	}

	if (const auto& originalFocus = loadedFocuses.find("extra_tech_slot"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus extra_tech_slot");
	}

	if (const auto& originalFocus = loadedFocuses.find("extra_tech_slot_2"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus extra_tech_slot_2");
	}

	if (const auto& originalFocus = loadedFocuses.find("secret_weapons"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus secret_weapons");
	}

	int numCollectovistIdeologies = calculateNumCollectovistIdeologies(majorIdeologies);

	if (const auto& originalFocus = loadedFocuses.find("political_effort"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->xPos = static_cast<int>((numCollectovistIdeologies * 1.5) + 16);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus political_effort");
	}

	if (numCollectovistIdeologies > 0)
	{
		if (const auto& originalFocus = loadedFocuses.find("collectivist_ethos"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
			newFocus->available = "= {\n";
			newFocus->available += "			OR = {\n";
			for (auto majorIdeology : majorIdeologies)
			{
				if (majorIdeology == "democratic")
				{
					continue;
				}
				newFocus->available += "				has_government = " + majorIdeology + "\n";
			}
			newFocus->available += "			}\n";
			newFocus->available += "		}";
			newFocus->xPos = -(numCollectovistIdeologies / 2) - 1;
			newFocus->completionReward = "= {\n";
			if (majorIdeologies.count("democratic") > 0)
			{
				newFocus->completionReward += "			add_ideas = collectivist_ethos_focus_democratic\n";
			}
			else
			{
				newFocus->completionReward += "			add_ideas = collectivist_ethos_focus_neutral\n";
			}
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus collectivist_ethos");
		}

		determineMutualExclusions(majorIdeologies);

		string ideolgicalFanaticsmPrereqs;
		int relativePosition = 1 - numCollectovistIdeologies;
		if (majorIdeologies.count("fascism") > 0)
		{
			addFascistGenericFocuses(relativePosition, majorIdeologies);
			ideolgicalFanaticsmPrereqs += " ";
			ideolgicalFanaticsmPrereqs += "focus = paramilitarism";
			relativePosition += 2;
		}
		if (majorIdeologies.count("communism") > 0)
		{
			addCommunistGenericFocuses(relativePosition);
			if (ideolgicalFanaticsmPrereqs.size() > 0)
			{
				ideolgicalFanaticsmPrereqs += " ";
			}
			ideolgicalFanaticsmPrereqs += "focus = political_commissars";
			relativePosition += 2;
		}
		if (majorIdeologies.count("absolutist") > 0)
		{
			addAbsolutistGenericFocuses(relativePosition);
			if (ideolgicalFanaticsmPrereqs.size() > 0)
			{
				ideolgicalFanaticsmPrereqs += " ";
			}
			ideolgicalFanaticsmPrereqs += "focus = historical_claims_focus";
			relativePosition += 2;
		}
		if (majorIdeologies.count("radical") > 0)
		{
			addRadicalGenericFocuses(relativePosition);
			if (ideolgicalFanaticsmPrereqs.size() > 0)
			{
				ideolgicalFanaticsmPrereqs += " ";
			}
			ideolgicalFanaticsmPrereqs += "focus = army_provides_focus";
		}

		if (const auto& originalFocus = loadedFocuses.find("ideological_fanaticism"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { " + ideolgicalFanaticsmPrereqs + " }");
			newFocus->xPos = 0;
			newFocus->yPos = 5;
			newFocus->relativePositionId = "collectivist_ethos";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus ideological_fanaticism");
		}
	}

	if (const auto& originalFocus = loadedFocuses.find("liberty_ethos"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		if (numCollectovistIdeologies == 0)
		{
			newFocus->mutuallyExclusive.clear();
		}
		if (majorIdeologies.count("democratic") == 0)
		{
			newFocus->available = "= {\n";
			newFocus->available += "			has_government = neutrality\n";
			newFocus->available += "		}";

			newFocus->completionReward = "= {\n";
			newFocus->completionReward += "	add_ideas = liberty_ethos_focus_neutral\n";
			newFocus->completionReward += "}";
		}
		newFocus->xPos = (numCollectovistIdeologies + 1) / 2;
		newFocus->aiWillDo = "= {\n";
		newFocus->aiWillDo += "			factor = 95\n";
		newFocus->aiWillDo += "			modifier = {\n";
		newFocus->aiWillDo += "				factor = 0.1\n";
		newFocus->aiWillDo += "				any_neighbor_country = {\n";
		newFocus->aiWillDo += "					is_major = yes\n";
		newFocus->aiWillDo += "					OR = {\n";
		for (auto majorIdeology : majorIdeologies)
		{
			newFocus->aiWillDo += "						has_government = " + majorIdeology + "\n";
		}
		newFocus->aiWillDo += "					}\n";
		newFocus->aiWillDo += "				}\n";
		if (majorIdeologies.count("democratic") > 0)
		{
			newFocus->aiWillDo += "				NOT = {\n";
			newFocus->aiWillDo += "					any_neighbor_country = {\n";
			newFocus->aiWillDo += "						is_major = yes\n";
			newFocus->aiWillDo += "						has_government = democratic\n";
			newFocus->aiWillDo += "					}\n";
			newFocus->aiWillDo += "				}\n";
		}
		newFocus->aiWillDo += "			}\n";
		newFocus->aiWillDo += "		}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus liberty_ethos");
	}

	if (const auto& originalFocus = loadedFocuses.find("neutrality_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		if (majorIdeologies.count("democratic") == 0)
		{
			newFocus->mutuallyExclusive.clear();
		}
		newFocus->aiWillDo = "= {\n";
		newFocus->aiWillDo += "			factor = 1\n";
		newFocus->aiWillDo += "		}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus neutrality_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("deterrence"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus deterrence");
	}

	if (majorIdeologies.count("democratic") != 0)
	{
		if (const auto& originalFocus = loadedFocuses.find("interventionism_focus"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus interventionism_focus");
		}

		if (const auto& originalFocus = loadedFocuses.find("volunteer_corps"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus volunteer_corps");
		}

		if (const auto& originalFocus = loadedFocuses.find("foreign_expeditions"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus foreign_expeditions");
		}
	}

	if (const auto& originalFocus = loadedFocuses.find("why_we_fight"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		if (majorIdeologies.count("democratic") == 0)
		{
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = deterrence }");
		}
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus why_we_fight");
	}

	if (const auto& originalFocus = loadedFocuses.find("technology_sharing"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		if (numCollectovistIdeologies == 0)
		{
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus = why_we_fight }");
		}
		newFocus->xPos = numCollectovistIdeologies;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus technology_sharing");
	}

	nextFreeColumn = static_cast<int>(numCollectovistIdeologies * 1.5) + ((numCollectovistIdeologies + 1) / 2) + 20;
}


void HoI4FocusTree::confirmLoadedFocuses()
{
	if (loadedFocuses.size() == 0)
	{
		registerKeyword(std::regex("focus_tree"), [this](const std::string& unused, std::istream& theStream) {});
		registerKeyword(std::regex("id"), commonItems::ignoreString);
		registerKeyword(std::regex("country"), commonItems::ignoreObject);
		registerKeyword(std::regex("default"), commonItems::ignoreString);
		registerKeyword(std::regex("reset_on_civilwar"), commonItems::ignoreString);
		registerKeyword(std::regex("focus"), [this](const std::string& unused, std::istream& theStream)
		{
			HoI4Focus newFocus(theStream);
			loadedFocuses.insert(make_pair(newFocus.id, newFocus));
		}
		);

		parseFile(theConfiguration.getHoI4Path() + "/common/national_focus/generic.txt");
		parseFile("converterFocuses.txt");
	}
}


int HoI4FocusTree::calculateNumCollectovistIdeologies(const set<string>& majorIdeologies)
{
	int numCollectovistIdeologies = 0;
	numCollectovistIdeologies += majorIdeologies.count("radical");
	numCollectovistIdeologies += majorIdeologies.count("absolutist");
	numCollectovistIdeologies += majorIdeologies.count("communism");
	numCollectovistIdeologies += majorIdeologies.count("fascism");
	return numCollectovistIdeologies;
}


void HoI4FocusTree::determineMutualExclusions(const set<string>& majorIdeologies)
{
	if (majorIdeologies.count("fascism") > 0)
	{
		communistMutualExclusions += "focus = nationalism_focus";
		absolutistMutualExlusions += "focus = nationalism_focus";
		radicalMutualExclusions += "focus = nationalism_focus";
	}
	if (majorIdeologies.count("communism") > 0)
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
	if (majorIdeologies.count("absolutist") > 0)
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
	if (majorIdeologies.count("radical") > 0)
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
		shared_ptr<HoI4Focus> newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + fascistMutualExlusions + " }";
		newFocus->xPos = relativePosition;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus nationalism_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("militarism"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus militarism");
	}

	if (const auto& originalFocus = loadedFocuses.find("military_youth"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->completionReward = "= {\n";
		newFocus->completionReward += "			add_ideas = military_youth_focus\n";
		for (auto ideology : majorIdeologies)
		{
			newFocus->completionReward += "			if = {\n";
			newFocus->completionReward += "				limit = { has_government = " + ideology + " }\n";
			newFocus->completionReward += "				add_popularity = {\n";
			newFocus->completionReward += "					ideology = " + ideology + "\n";
			newFocus->completionReward += "					popularity = 0.2\n";
			newFocus->completionReward += "				}\n";
			newFocus->completionReward += "			}\n";
		}
		newFocus->completionReward += "		}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus military_youth");
	}

	if (const auto& originalFocus = loadedFocuses.find("paramilitarism"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
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
		shared_ptr<HoI4Focus> newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + communistMutualExclusions + " }";
		newFocus->available = "= {\n";
		newFocus->available += "			OR = {\n";
		newFocus->available += "				has_government = communism\n";
		newFocus->available += "				has_government = neutrality\n";
		newFocus->available += "			}\n";
		newFocus->available += "		}";
		newFocus->xPos = relativePosition;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus internationalism_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("political_correctness"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus political_correctness");
	}

	if (const auto& originalFocus = loadedFocuses.find("indoctrination_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus indoctrination_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("political_commissars"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->completionReward = "= {\n";
		newFocus->completionReward += "			add_ideas = political_commissars_focus\n";
		newFocus->completionReward += "			if = {\n";
		newFocus->completionReward += "				limit = { has_government = communism }\n";
		newFocus->completionReward += "				add_popularity = {\n";
		newFocus->completionReward += "					ideology = communism\n";
		newFocus->completionReward += "					popularity = 0.2\n";
		newFocus->completionReward += "				}\n";
		newFocus->completionReward += "			}\n";
		newFocus->completionReward += "			add_political_power = 200\n";
		newFocus->completionReward += "		}";
		focuses.push_back(newFocus);
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
		shared_ptr<HoI4Focus> newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + absolutistMutualExlusions + " }";
		newFocus->xPos = relativePosition;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus absolutism_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("royal_dictatorship_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus royal_dictatorship_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("royal_army_tradition_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus royal_army_tradition_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("historical_claims_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
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
		shared_ptr<HoI4Focus> newFocus = make_shared<HoI4Focus>(originalFocus->second);
		newFocus->mutuallyExclusive = "= { " + radicalMutualExclusions + " }";
		newFocus->xPos = relativePosition;
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus radical_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("private_channels_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus private_channels_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("hardfought_market_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus hardfought_market_focus");
	}

	if (const auto& originalFocus = loadedFocuses.find("army_provides_focus"); originalFocus != loadedFocuses.end())
	{
		auto newFocus = make_shared<HoI4Focus>(originalFocus->second);
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus army_provides_focus");
	}
}


std::unique_ptr<HoI4FocusTree> HoI4FocusTree::makeCustomizedCopy(const HoI4::Country& country) const
{
	HoI4FocusTree newFocusTree(country);

	for (auto focus : focuses)
	{
		auto newFocus = focus->makeCustomizedCopy(newFocusTree.dstCountryTag);
		newFocusTree.addFocus(newFocus);
	}
	newFocusTree.setNextFreeColumn(nextFreeColumn);

	return std::make_unique<HoI4FocusTree>(std::move(newFocusTree));
}


void HoI4FocusTree::addDemocracyNationalFocuses(shared_ptr<HoI4::Country> Home, vector<shared_ptr<HoI4::Country>>& CountriesToContain)
{
	double WTModifier = 1;
	if (Home->getGovernmentIdeology() == "democratic")
	{
		string warPol = Home->getRulingParty().getWarPolicy();
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

	if (const auto& originalFocus = loadedFocuses.find("WarProp"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		newFocus->available = "= {\n";
		newFocus->available += "			threat > " + to_string(0.20 * WTModifier / 1000) + "\n";
		newFocus->available += "		}";
		newFocus->xPos = nextFreeColumn + (CountriesToContain.size() * 2) - 1;
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
		newFocus->available += "			threat > " + to_string(0.30 * WTModifier / 1000) + "\n";
		newFocus->available += "		}";
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
		newFocus->available += "			threat > " + to_string(0.50 * WTModifier / 1000) + "\n";
		newFocus->available += "		}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus Lim");
	}

	int relavtivePos = 1 - (CountriesToContain.size() * 2);
	for (auto country : CountriesToContain)
	{
		auto possibleContainedCountryName = country->getSourceCountry().getName("english");
		string containedCountryName;
		if (possibleContainedCountryName)
		{
			containedCountryName = *possibleContainedCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine contained country name for democratic focuses";
			containedCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("WarPlan"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), country->getTag());
			newFocus->bypass = "= {\n";
			newFocus->bypass += "			has_war_with = " + country->getTag() + "\n";
			newFocus->bypass += "		}";
			newFocus->xPos = relavtivePos;
			newFocus->available = "= {\n";
			newFocus->available += "			any_other_country = {\n";
			newFocus->available += "				original_tag = " + country->getTag() + "\n";
			newFocus->available += "				exists = yes\n";
			newFocus->available += "				NOT = { has_government = democratic } \n";
			newFocus->available += "				NOT = { is_in_faction_with = " + Home->getTag() + " }\n";
			newFocus->available += "				OR = {\n";
			newFocus->available += "					has_offensive_war = yes\n";
			newFocus->available += "					has_added_tension_amount > 30\n";
			newFocus->available += "				}\n";
			newFocus->available += "			}\n";
			newFocus->available += "		}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus WarPlan");
		}

		if (const auto& originalFocus = loadedFocuses.find("Embargo"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), country->getTag());
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus =  WarPlan" + Home->getTag() + country->getTag() + " }");
			newFocus->bypass = "= {\n";
			newFocus->bypass += "			has_war_with = " + country->getTag() + "\n";
			newFocus->bypass += "		}";
			newFocus->relativePositionId += country->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "			any_other_country = {\n";
			newFocus->available += "				original_tag = " + country->getTag() + "\n";
			newFocus->available += "				exists = yes\n";
			newFocus->available += "				NOT = { has_government = democratic } \n";
			newFocus->available += "				NOT = { is_in_faction_with = " + Home->getTag() + " }\n";
			newFocus->available += "				OR = {\n";
			newFocus->available += "					has_offensive_war = yes\n";
			newFocus->available += "					has_added_tension_amount > 30\n";
			newFocus->available += "					threat > 0.6\n";
			newFocus->available += "				}\n";
			newFocus->available += "			}\n";
			newFocus->available += "		}";
			newFocus->completionReward = "= {\n";
			newFocus->completionReward += "			" + country->getTag() + " = {\n";
			newFocus->completionReward += "				add_opinion_modifier = { target = " + Home->getTag() + " modifier = embargo }\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Embargo");
		}

		if (const auto& originalFocus = loadedFocuses.find("WAR"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), country->getTag());
			newFocus->prerequisites.clear();
			newFocus->prerequisites.push_back("= { focus =  Embargo" + Home->getTag() + country->getTag() + " }");
			newFocus->prerequisites.push_back("= { focus =  Lim" + Home->getTag() + " }");
			newFocus->bypass = "= {\n";
			newFocus->bypass += "			has_war_with = " + country->getTag() + "\n";
			newFocus->bypass += "		}";
			newFocus->relativePositionId += country->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "			has_war = no\n";
			newFocus->available += "			any_other_country = {\n";
			newFocus->available += "				original_tag = " + country->getTag() + "\n";
			newFocus->available += "				exists = yes\n";
			newFocus->available += "				NOT = { has_government = democratic } \n";
			newFocus->available += "				NOT = { is_in_faction_with = " + Home->getTag() + " }\n";
			newFocus->available += "				OR = {\n";
			newFocus->available += "					has_offensive_war = yes\n";
			newFocus->available += "					has_added_tension_amount > 30\n";
			newFocus->available += "					threat > 0.6\n";
			newFocus->available += "				}\n";
			newFocus->available += "			}\n";
			newFocus->available += "		}";
			newFocus->aiWillDo = "= {\n";
			newFocus->aiWillDo += "			factor = 10\n";
			newFocus->aiWillDo += "		}";
			newFocus->completionReward = "= {\n";
			newFocus->completionReward += "			declare_war_on = {\n";
			newFocus->completionReward += "				type = puppet_wargoal_focus\n";
			newFocus->completionReward += "				target = " + country->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);

			relavtivePos += 4;
		}
		else
		{
			throw std::runtime_error("Could not load focus WAR");
		}
	}
}


void HoI4FocusTree::addAbsolutistEmpireNationalFocuses(shared_ptr<HoI4::Country> Home, const vector<shared_ptr<HoI4::Country>>& targetColonies, const vector<shared_ptr<HoI4::Country>>& annexationTargets)
{
	auto possibleHomeCountryAdjective = Home->getSourceCountry().getAdjective("english");
	string homeCountryAdjective;
	if (possibleHomeCountryAdjective)
	{
		homeCountryAdjective = *possibleHomeCountryAdjective;
	}
	else
	{
		LOG(LogLevel::Warning) << "Could not determine home country adjective for absolutist focuses";
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
		newFocus->completionReward = "{\n";
		newFocus->completionReward += "		add_ideas = militarism_focus_absolutist\n";
		newFocus->completionReward += "}\n";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus ColonialArmy");
	}

	//establish protectorate
	if (targetColonies.size() >= 1)
	{
		auto target = targetColonies.front();

		auto possibleProtectorateCountryName = target->getSourceCountry().getName("english");
		string protectorateCountryName;
		if (possibleProtectorateCountryName)
		{
			protectorateCountryName = *possibleProtectorateCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine protectorate country name for absolutist focuses";
			protectorateCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Protectorate"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag());
			newFocus->id = "Protectorate" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "			" + target->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "		}";
			newFocus->prerequisites.push_back("= { focus = ColonialArmy" + Home->getTag() + " }");
			newFocus->relativePositionId = "ColonialArmy" + Home->getTag();
			newFocus->xPos = 0;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "			OR = {\n";
			newFocus->bypass += "				" + Home->getTag() + " = {\n";
			newFocus->bypass += "					is_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "					has_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "				}\n";
			newFocus->bypass += "				NOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "			}\n";
			newFocus->bypass += "		}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "			factor = 10\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "				factor = 0\n";
			newFocus->aiWillDo += "				strength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "			}\n";
			newFocus->aiWillDo += "		}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			create_wargoal = {\n";
			newFocus->completionReward += "				type = annex_everything\n";
			newFocus->completionReward += "				target = " + target->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
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

		auto possibleProtectorateCountryName = target->getSourceCountry().getName("english");
		string protectorateCountryName;
		if (possibleProtectorateCountryName)
		{
			protectorateCountryName = *possibleProtectorateCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine protectorate country name for absolutist focuses";
			protectorateCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Protectorate"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag());
			newFocus->id = "Protectorate" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "			" + target->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "		}";
			newFocus->prerequisites.push_back("= { focus = Protectorate" + Home->getTag() + targetColonies.front()->getTag() + " }");
			newFocus->relativePositionId = "Protectorate" + Home->getTag() + targetColonies.front()->getTag();
			newFocus->xPos = 0;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "			OR = {\n";
			newFocus->bypass += "				" + Home->getTag() + " = {\n";
			newFocus->bypass += "					is_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "					has_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "				}\n";
			newFocus->bypass += "				NOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "			}\n";
			newFocus->bypass += "		}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "			factor = 5\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "				factor = 0\n";
			newFocus->aiWillDo += "				strength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "			}\n";
			newFocus->aiWillDo += "		}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			create_wargoal = {\n";
			newFocus->completionReward += "				type = annex_everything\n";
			newFocus->completionReward += "				target = " + target->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
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

	//ANNEX
	if (annexationTargets.size() >= 1)
	{
		auto target = annexationTargets.front();

		auto possibleTargetCountryName = target->getSourceCountry().getName("english");
		string targetCountryName;
		if (possibleTargetCountryName)
		{
			targetCountryName = *possibleTargetCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine target country name for absolutist focuses";
			targetCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Annex"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag());
			newFocus->id = "Annex" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "			" + target->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "		}";
			newFocus->prerequisites.push_back("= { focus = PrepTheBorder" + Home->getTag() + " }");
			newFocus->relativePositionId = "PrepTheBorder" + Home->getTag();
			newFocus->xPos = 2;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "			OR = {\n";
			newFocus->bypass += "				" + Home->getTag() + "= {\n";
			newFocus->bypass += "					is_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "					has_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "				}\n";
			newFocus->bypass += "				NOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "			}\n";
			newFocus->bypass += "		}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "			factor = 5\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "				factor = 0\n";
			newFocus->aiWillDo += "				strength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "			}\n";
			newFocus->aiWillDo += "		}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			create_wargoal = {\n";
			newFocus->completionReward += "				type = annex_everything\n";
			newFocus->completionReward += "				target = " + target->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
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

		auto possibleTargetCountryName = target->getSourceCountry().getName("english");
		string targetCountryName;
		if (possibleTargetCountryName)
		{
			targetCountryName = *possibleTargetCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine target country name for absolutist focuses";
			targetCountryName.clear();
		}

		if (const auto& originalFocus = loadedFocuses.find("Annex"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), target->getTag());
			newFocus->id = "Annex" + Home->getTag() + target->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "			\"" + target->getTag() + "\" = { is_in_faction = no }\n";
			newFocus->available += "		}";
			newFocus->prerequisites.push_back("= { focus = NatSpirit" + Home->getTag() + " }");
			newFocus->relativePositionId = "NatSpirit" + Home->getTag();
			newFocus->xPos = 1;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "			OR = {\n";
			newFocus->bypass += "				" + Home->getTag() + " = {\n";
			newFocus->bypass += "					is_in_faction_with = " + target->getTag() + "\n";
			newFocus->bypass += "					has_war_with = " + target->getTag() + "\n";
			newFocus->bypass += "				}\n";
			newFocus->bypass += "				NOT = { country_exists = " + target->getTag() + " }\n";
			newFocus->bypass += "			}\n";
			newFocus->bypass += "		}";
			newFocus->aiWillDo += "= {\n";
			newFocus->aiWillDo += "			factor = 5\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "				factor = 0\n";
			newFocus->aiWillDo += "				strength_ratio = { tag = " + target->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "			}\n";
			newFocus->aiWillDo += "		}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			create_wargoal = {\n";
			newFocus->completionReward += "				type = annex_everything\n";
			newFocus->completionReward += "				target = " + target->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus Annex");
		}
	}
}

void HoI4FocusTree::addCommunistCoupBranch(shared_ptr<HoI4::Country> Home, const vector<shared_ptr<HoI4::Country>>& coupTargets, const std::set<std::string>& majorIdeologies)
{
	if (coupTargets.size() > 0)
	{
		if (const auto& originalFocus = loadedFocuses.find("Home_of_Revolution"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			newFocus->xPos = nextFreeColumn + coupTargets.size() - 1;
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
				auto possibleCoupCountryName = coupTargets[i]->getSourceCountry().getName("english");
				string coupCountryName;
				if (possibleCoupCountryName)
				{
					coupCountryName = *possibleCoupCountryName;
				}
				else
				{
					LOG(LogLevel::Warning) << "Could not determine coup country name for communist coup focuses";
					coupCountryName.clear();
				}

				if (const auto& originalFocus = loadedFocuses.find("Influence_"); originalFocus != loadedFocuses.end())
				{
					auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), coupTargets[i]->getTag());
					newFocus->id = "Influence_" + coupTargets[i]->getTag() + "_" + Home->getTag();
					newFocus->xPos = nextFreeColumn + i * 2;
					newFocus->yPos = 1;
					newFocus->completionReward += "= {\n";
					newFocus->completionReward += "			" + coupTargets[i]->getTag() + " = {\n";
					if (majorIdeologies.count("fascism") > 0)
					{
						newFocus->completionReward += "				if = {\n";
						newFocus->completionReward += "					limit = {\n";
						newFocus->completionReward += "						" + Home->getTag() + " = {\n";
						newFocus->completionReward += "							has_government = fascism\n";
						newFocus->completionReward += "						}\n";
						newFocus->completionReward += "					}\n";
						newFocus->completionReward += "					add_ideas = fascist_influence\n";
						newFocus->completionReward += "				}\n";
					}
					if (majorIdeologies.count("communism") > 0)
					{
						newFocus->completionReward += "				if = {\n";
						newFocus->completionReward += "					limit = {\n";
						newFocus->completionReward += "						" + Home->getTag() + " = {\n";
						newFocus->completionReward += "							has_government = communism\n";
						newFocus->completionReward += "						}\n";
						newFocus->completionReward += "					}\n";
						newFocus->completionReward += "					add_ideas = communist_influence\n";
						newFocus->completionReward += "				}\n";
					}
					if (majorIdeologies.count("democratic") > 0)
					{
						newFocus->completionReward += "				if = {\n";
						newFocus->completionReward += "					limit = {\n";
						newFocus->completionReward += "						" + Home->getTag() + " = {\n";
						newFocus->completionReward += "							has_government = democratic\n";
						newFocus->completionReward += "						}\n";
						newFocus->completionReward += "					}\n";
						newFocus->completionReward += "					add_ideas = democratic_influence\n";
						newFocus->completionReward += "				}\n";
					}
					if (majorIdeologies.count("absolutist") > 0)
					{
						newFocus->completionReward += "				if = {\n";
						newFocus->completionReward += "					limit = {\n";
						newFocus->completionReward += "						" + Home->getTag() + " = {\n";
						newFocus->completionReward += "							has_government = absolutist\n";
						newFocus->completionReward += "						}\n";
						newFocus->completionReward += "					}\n";
						newFocus->completionReward += "					add_ideas = absolutist_influence\n";
						newFocus->completionReward += "				}\n";
					}
					if (majorIdeologies.count("radical") > 0)
					{
						newFocus->completionReward += "				if = {\n";
						newFocus->completionReward += "					limit = {\n";
						newFocus->completionReward += "						" + Home->getTag() + " = {\n";
						newFocus->completionReward += "							has_government = radical\n";
						newFocus->completionReward += "						}\n";
						newFocus->completionReward += "					}\n";
						newFocus->completionReward += "					add_ideas = radical_influence\n";
						newFocus->completionReward += "				}\n";
					}
					newFocus->completionReward += "				country_event = { id = generic.1 }\n";
					newFocus->completionReward += "			}\n";
					newFocus->completionReward += "		}";
					focuses.push_back(newFocus);
				}
				else
				{
					throw std::runtime_error("Could not load focus Influence_");
				}

				if (const auto& originalFocus = loadedFocuses.find("Coup_"); originalFocus != loadedFocuses.end())
				{
					auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), coupTargets[i]->getTag());
					newFocus->id = "Coup_" + coupTargets[i]->getTag() + "_" + Home->getTag();
					newFocus->prerequisites.push_back("= { focus = Influence_" + coupTargets[i]->getTag() + "_" + Home->getTag() + " }");
					newFocus->relativePositionId = "Influence_" + coupTargets[i]->getTag() + "_" + Home->getTag();
					newFocus->xPos = 0;
					newFocus->yPos = 1;
					newFocus->available = "= {\n";
					newFocus->available += "			" + coupTargets[i]->getTag() + " = { communism > 0.5 }\n";
					newFocus->available += "		}";
					newFocus->completionReward += "= {\n";
					newFocus->completionReward += "			" + coupTargets[i]->getTag() + " = {\n";
					newFocus->completionReward += "				start_civil_war = {\n";
					newFocus->completionReward += "					ideology = communism\n";
					newFocus->completionReward += "					size = 0.5\n";
					newFocus->completionReward += "				}\n";
					newFocus->completionReward += "			}\n";
					newFocus->completionReward += "		}";
					focuses.push_back(newFocus);
				}
				else
				{
					throw std::runtime_error("Could not load focus Coup_");
				}
			}
		}
		nextFreeColumn += 2 * coupTargets.size();
	}
	return;
}

void HoI4FocusTree::addCommunistWarBranch(shared_ptr<HoI4::Country> Home, const vector<shared_ptr<HoI4::Country>>& warTargets, HoI4::Events* events)
{
	if (warTargets.size() > 0)
	{

		if (const auto& originalFocus = loadedFocuses.find("StrengthCom"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			newFocus->xPos = nextFreeColumn + warTargets.size() - 1;
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
			newFocus->completionReward += "			add_named_threat = { threat = 2 name = " + newFocus->id + " }\n";
			newFocus->completionReward += "			add_political_power = 150\n";
			newFocus->completionReward += "		}";
			//FIXME
			//maybe add some claims?
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
				auto possibleWarTargetCountryName = warTargets[i]->getSourceCountry().getName("english");
				string warTargetCountryName;
				if (possibleWarTargetCountryName)
				{
					warTargetCountryName = *possibleWarTargetCountryName;
				}
				else
				{
					LOG(LogLevel::Warning) << "Could not determine war target country name for communist war focuses";
					warTargetCountryName.clear();
				}

				int v1 = rand() % 12 + 1;
				int v2 = rand() % 12 + 1;
				if (const auto& originalFocus = loadedFocuses.find("War"); originalFocus != loadedFocuses.end())
				{
					auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), warTargets[i]->getTag());
					newFocus->id = "War" + warTargets[i]->getTag() + Home->getTag();
					newFocus->available = "= {\n";
					newFocus->available += "			date > 1938." + to_string(v1) + "." + to_string(v2) + "\n";
					newFocus->available += "		}";
					newFocus->xPos = nextFreeColumn + i * 2;
					newFocus->yPos = 2;
					newFocus->bypass = "= {\n";
					newFocus->bypass += "					has_war_with = " + warTargets[i]->getTag() + "\n";
					newFocus->bypass += "				}";
					newFocus->aiWillDo = "= {\n";
					newFocus->aiWillDo += "			factor = 5\n";
					newFocus->aiWillDo += "			modifier = {\n";
					newFocus->aiWillDo += "				factor = 0\n";
					newFocus->aiWillDo += "				strength_ratio = { tag = " + warTargets[i]->getTag() + " ratio < 1 }\n";
					newFocus->aiWillDo += "			}";
					if (warTargets.size() > 1)
					{
						newFocus->aiWillDo += "\n";
						newFocus->aiWillDo += "			modifier = {\n";
						newFocus->aiWillDo += "				factor = 0\n";
						newFocus->aiWillDo += "				OR = {\n";
						for (unsigned int i2 = 0; i2 < warTargets.size(); i2++)
						{
							if (i != i2)
								newFocus->aiWillDo += "					has_war_with = " + warTargets[i]->getTag() + "\n";
						}
						newFocus->aiWillDo += "				}\n";
						newFocus->aiWillDo += "			}";
					}
					newFocus->aiWillDo += "\n";
					newFocus->aiWillDo += "		}";

					newFocus->completionReward += "= {\n";
					newFocus->completionReward += "			add_named_threat = { threat = 3 name = " + newFocus->id + " }\n";
					newFocus->completionReward += "			create_wargoal = {\n";
					newFocus->completionReward += "				type = puppet_wargoal_focus\n";
					newFocus->completionReward += "				target = " + warTargets[i]->getTag() + "\n";
					newFocus->completionReward += "			}\n";
					newFocus->completionReward += "		}";
					focuses.push_back(newFocus);
				}
				else
				{
					throw std::runtime_error("Could not load focus War");
				}
			}
		}
		nextFreeColumn += warTargets.size() * 2;
	}
}

void HoI4FocusTree::addFascistAnnexationBranch(shared_ptr<HoI4::Country> Home, const vector<shared_ptr<HoI4::Country>>& annexationTargets, HoI4::Events* events)
{
	//The Following 'if' statement prevents converter from generating focuses if annexationTargets.size > 1
	//Keep this 'if' statement off until we figure out how to handle Fascist NF's
	//if (annexationTargets.size() >= 1)
	//{
	if (const auto& originalFocus = loadedFocuses.find("The_third_way"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		if (annexationTargets.size() >= 1)
		{
			newFocus->xPos = nextFreeColumn + annexationTargets.size() - 1;
		}

		//'else' statement is there in case annexationTargets.size() is <1.  Need to fix in the future.
		else
		{
			newFocus->xPos = nextFreeColumn;
		}
		newFocus->yPos = 0;
		//FIXME
		//Need to get Drift Defense to work
		//in modified generic focus? (tk)
		//newFocus->completionReward += "			drift_defence_factor = 0.5\n";
		newFocus->completionReward += "= {\n";
		newFocus->completionReward += "			add_named_threat = { threat = 2 name = " + newFocus->id + " }\n";
		newFocus->completionReward += "			add_ideas = fascist_influence\n";
		newFocus->completionReward += "		}";
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
		auto possibleAnnexationTargetCountryName = annexationTargets[i]->getSourceCountry().getName("english");
		string annexationTargetCountryName;
		if (possibleAnnexationTargetCountryName)
		{
			annexationTargetCountryName = *possibleAnnexationTargetCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine annexation target country name for fascist annexation focuses";
			annexationTargetCountryName.clear();
		}

		//int x = i * 3;
		//for random date
		int v1 = rand() % 5 + 1;
		int v2 = rand() % 5 + 1;

		if (const auto& originalFocus = loadedFocuses.find("_anschluss_"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), annexationTargets[i]->getTag());
			newFocus->id = Home->getTag() + "_anschluss_" + annexationTargets[i]->getTag();
			newFocus->available += "= {\n";
			newFocus->available += "			" + annexationTargets[i]->getTag() + " = {\n";
			newFocus->available += "				is_in_faction = no\n";
			newFocus->available += "			}\n";
			newFocus->available += "			is_puppet = no\n";
			newFocus->available += "			date > 1937." + to_string(v1 + 5) + "." + to_string(v2 + 5) + "\n";
			newFocus->available += "		}";
			newFocus->xPos = nextFreeColumn + i * 2;
			newFocus->yPos = 2;
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			add_named_threat = { threat = 2 name = " + newFocus->id + " }\n";
			newFocus->completionReward += "			army_experience = 10\n";
			newFocus->completionReward += "			if = {\n";
			newFocus->completionReward += "				limit = {\n";
			newFocus->completionReward += "					country_exists = " + annexationTargets[i]->getTag() + "\n";
			newFocus->completionReward += "				}\n";
			newFocus->completionReward += "				" + annexationTargets[i]->getTag() + " = {\n";
			newFocus->completionReward += "					country_event = NFEvents." + to_string(events->getCurrentNationFocusEventNum()) + "\n";
			newFocus->completionReward += "				}\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);

			events->createAnnexEvent(Home, annexationTargets[i]);
		}
		else
		{
			throw std::runtime_error("Could not load focus _anschluss_");
		}
	}
	if (annexationTargets.size() >= 1)
	{
		nextFreeColumn += annexationTargets.size() * 2;
	}
	else
	{
		nextFreeColumn += 2;
	}
	//}
}

void HoI4FocusTree::addFascistSudetenBranch(shared_ptr<HoI4::Country> Home, const vector<shared_ptr<HoI4::Country>>& sudetenTargets, const vector<vector<int>>& demandedStates, const HoI4::World* world)
{
	HoI4::Events* events = world->getEvents();

	//if it can easily take these targets as they are not in an alliance, you can get annexation event

	if (const auto& originalFocus = loadedFocuses.find("expand_the_reich"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
		if (sudetenTargets.size() == 1 || sudetenTargets.size() >= 2)
		{
			//if there are anschlusses, make this event require at least 1 anschluss, else, its the start of a tree
			for (unsigned int i = 0; i < 2; i++)
			{
				if (i < sudetenTargets.size())
				{
					//					newFocus->prerequisites.push_back("= { focus = " + Home->getTag() + "_anschluss_" + sudetenTargets[i]->getTag() + " }");
				}
			}
			newFocus->xPos = nextFreeColumn + sudetenTargets.size() - 1;
		}

		//'else' statement is there in case sudetenTargets.size() is <1.  Need to fix in the future.
		else
		{
			newFocus->xPos = nextFreeColumn;
		}
		newFocus->yPos = 0;
		newFocus->completionReward += "= {\n";
		newFocus->completionReward += "			add_named_threat = { threat = 3 name = " + newFocus->id + " }\n";//give some claims or cores
		newFocus->completionReward += "			add_political_power = 150\n";
		newFocus->completionReward += "		}";
		addFocus(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus expand_the_reich");
	}

	for (unsigned int i = 0; i < sudetenTargets.size(); i++)
	{
		auto possibleSudetenTargetCountryName = sudetenTargets[i]->getSourceCountry().getName("english");
		string sudetenTargetCountryName;
		if (possibleSudetenTargetCountryName)
		{
			sudetenTargetCountryName = *possibleSudetenTargetCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine annexation target country name for fascist sudeten focuses";
			sudetenTargetCountryName.clear();
		}

		int v1 = rand() % 8 + 1;
		int v2 = rand() % 8 + 1;

		if (const auto& originalFocus = loadedFocuses.find("_sudeten_"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), sudetenTargets[i]->getTag());
			newFocus->id = Home->getTag() + "_sudeten_" + sudetenTargets[i]->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "			is_puppet = no\n";
			newFocus->available += "			date > 1938." + to_string(v1) + "." + to_string(v2) + "\n";
			newFocus->available += "		}";
			newFocus->xPos = nextFreeColumn + 2 * i;
			newFocus->yPos = 1;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "  has_war_with = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->bypass += "}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			add_named_threat = { threat = 2 name = " + newFocus->id + " }\n";
			newFocus->completionReward += "			army_experience = 10\n";
			newFocus->completionReward += "			if = {\n";
			newFocus->completionReward += "				limit = {\n";
			newFocus->completionReward += "					country_exists = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->completionReward += "				}\n";
			newFocus->completionReward += "				" + sudetenTargets[i]->getTag() + " = {\n";
			newFocus->completionReward += "					country_event = NFEvents." + to_string(events->getCurrentNationFocusEventNum()) + "\n";
			newFocus->completionReward += "				}\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			addFocus(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus _sudeten_");
		}

		//FINISH HIM
		if (const auto& originalFocus = loadedFocuses.find("_finish_"); originalFocus != loadedFocuses.end())
		{
			auto newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), sudetenTargets[i]->getTag());
			newFocus->id = Home->getTag() + "_finish_" + sudetenTargets[i]->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "	" + sudetenTargets[i]->getTag() + " = { is_in_faction = no }\n";
			newFocus->available += "		}";
			newFocus->prerequisites.push_back("= { focus =  " + Home->getTag() + "_sudeten_" + sudetenTargets[i]->getTag() + " }");
			newFocus->xPos = nextFreeColumn + 2 * i;
			newFocus->yPos = 2;
			newFocus->bypass += "= {\n";
			newFocus->bypass += "		has_war_with = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->bypass += "	}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			add_named_threat = { threat = 3 name = " + newFocus->id + " }\n";
			newFocus->completionReward += "			create_wargoal = {\n";
			newFocus->completionReward += "				type = annex_everything\n";
			newFocus->completionReward += "				target = " + sudetenTargets[i]->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			addFocus(newFocus);
		}
		else
		{
			throw std::runtime_error("Could not load focus _finish_");
		}

		//events
		events->createSudetenEvent(Home, sudetenTargets[i], demandedStates[i]);
	}
	nextFreeColumn += 2 * sudetenTargets.size();
}


void HoI4FocusTree::addGPWarBranch(shared_ptr<HoI4::Country> Home, const vector<shared_ptr<HoI4::Country>>& newAllies, const vector<shared_ptr<HoI4::Country>>& GCTargets, const string& ideology, HoI4::Events* events)
{
	int numAllies = newAllies.size();
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
				newFocus->xPos = nextFreeColumn + newAllies.size();
			}
			else
			{
				newFocus->xPos = nextFreeColumn + newAllies.size() + 1;
			}
			newFocus->yPos = 0;
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			add_named_threat = { threat = 3 name = " + newFocus->id + " }\n";
			newFocus->completionReward += "			add_political_power = 150\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);
			HoI4Localisation::copyFocusLocalisations("_Summit", newFocus->text);
			HoI4Localisation::updateLocalisationText(newFocus->text, "$TARGET", ideology);
			HoI4Localisation::updateLocalisationText(newFocus->text + "_desc", "$TARGET", ideology);
		}
		else
		{
			throw std::runtime_error("Could not load focus _Summit");
		}
	}

	unsigned int i = 0;
	for (auto newAlly : newAllies)
	{
		auto possibleAllyCountryName = newAlly->getSourceCountry().getName("english");
		string allyCountryName;
		if (possibleAllyCountryName)
		{
			allyCountryName = *possibleAllyCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine ally country name for GP alliance focuses";
			allyCountryName.clear();
		}
		
		if (const auto& originalFocus = loadedFocuses.find("Alliance_"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeTargetedCopy(Home->getTag(), newAlly->getTag());
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
			newFocus->bypass += "			OR = {\n";
			newFocus->bypass += "				" + Home->getTag() + " = { is_in_faction_with = " + newAlly->getTag() + "}\n";
			newFocus->bypass += "				has_war_with = " + newAlly->getTag() + "\n";
			newFocus->bypass += "				NOT = { country_exists = " + newAlly->getTag() + " }\n";
			newFocus->bypass += "			}\n";
			newFocus->bypass += "		}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			" + newAlly->getTag() + " = {\n";
			newFocus->completionReward += "				country_event = { hours = 6 id = NFEvents." + to_string(events->getCurrentNationFocusEventNum()) + " }\n";
			newFocus->completionReward += "				add_opinion_modifier = { target = " + Home->getTag() + " modifier = positive_50 }\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);

			events->createFactionEvents(Home, newAlly);
			i++;
		}
		else
		{
			throw std::runtime_error("Could not load focus Alliance_");
		}
	}

	i = 0;
	for (auto GC : GCTargets)
	{
		auto possibleWarTargetCountryName = GC->getSourceCountry().getName("english");
		string warTargetCountryName;
		if (possibleWarTargetCountryName)
		{
			warTargetCountryName = *possibleWarTargetCountryName;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not determine war target country name for GP war focuses";
			warTargetCountryName.clear();
		}

		//figuring out location of WG
		if (const auto& originalFocus = loadedFocuses.find("GP_War"); originalFocus != loadedFocuses.end())
		{
			shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeCustomizedCopy(Home->getTag());
			if (newAllies.size() > 0)
			{
				for (unsigned int i2 = 0; i2 < newAllies.size(); i2++)
				{
					newFocus->prerequisites.push_back("= { focus = Alliance_" + newAllies[i2]->getTag() + Home->getTag() + " }");
				}
			}
			int v1 = rand() % 12 + 1;
			int v2 = rand() % 12 + 1;
			newFocus->id = "GP_War" + GC->getTag() + Home->getTag();
			newFocus->text += GC->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "			has_war = no\n";
			newFocus->available += "			date > 1939." + to_string(v1) + "." + to_string(v2) + "\n";
			newFocus->available += "		}";
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
			newFocus->bypass += "		   has_war_with = " + GC->getTag() + "\n";
			newFocus->bypass += "		}";
			newFocus->aiWillDo = "= {\n";
			newFocus->aiWillDo += "			factor = " + to_string(10 - GCTargets.size() * 5) + "\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "					factor = 0\n";
			newFocus->aiWillDo += "					strength_ratio = { tag = " + GC->getTag() + " ratio < 1 }\n";
			newFocus->aiWillDo += "			}";
			if (GCTargets.size() > 1)
			{
				newFocus->aiWillDo = "\n";

				//make ai have this as a 0 modifier if they are at war
				newFocus->aiWillDo += "			modifier = {\n";
				newFocus->aiWillDo += "				factor = 0\n";
				newFocus->aiWillDo += "				OR = {\n";
				for (unsigned int i2 = 0; i2 < GCTargets.size(); i2++)
				{
					if (GC != GCTargets[i2])
					{
						newFocus->aiWillDo += "					has_war_with = " + GCTargets[i2]->getTag() + "\n";
					}
				}
				newFocus->aiWillDo += "				}\n";
				newFocus->aiWillDo += "			}";
			}
			newFocus->aiWillDo += "\n";
			newFocus->aiWillDo += "		}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward += "			add_named_threat = { threat = 5 name = " + newFocus->id + " }\n";
			newFocus->completionReward += "			declare_war_on = {\n";
			newFocus->completionReward += "				type = puppet_wargoal_focus\n";
			newFocus->completionReward += "				target = " + GC->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			focuses.push_back(newFocus);
			HoI4Localisation::copyFocusLocalisations("GPWar", newFocus->text);
			HoI4Localisation::updateLocalisationText(newFocus->text, "$TARGET", GC->getTag());
			HoI4Localisation::updateLocalisationText(newFocus->text + "_desc", "$TARGET", GC->getTag());
			i++;
		}
		else
		{
			throw std::runtime_error("Could not load focus GP_War");
		}
	}
	nextFreeColumn += 2 * max(newAllies.size(), GCTargets.size());
}


void HoI4FocusTree::addNeighborWarBranch(
	const string& tag,
	const vector<shared_ptr<HoI4::Country>>& weakNeighbors,
	const shared_ptr<HoI4::Country>& targetNeighbors,
	const string& targetName,
	const date& startDate,
	int numWarsWithNeighbors
)
{
	if (const auto& originalFocus = loadedFocuses.find("NeighborWar"); originalFocus != loadedFocuses.end())
	{
		shared_ptr<HoI4Focus> newFocus = originalFocus->second.makeTargetedCopy(tag, targetNeighbors->getTag());
		newFocus->id = "NeighborWar" + targetNeighbors->getTag() + tag;
		newFocus->available = "= {\n";
		newFocus->available += "			has_war = no\n";
		newFocus->available += "			date > " + startDate.toString() + "\n";
		newFocus->available += "		}";
		newFocus->xPos = nextFreeColumn;
		newFocus->yPos = 0;
		newFocus->bypass = "= {\n";
		newFocus->bypass += "			has_war_with = " + targetNeighbors->getTag() + "\n";
		newFocus->bypass += "		}";
		newFocus->aiWillDo = "= {\n";
		newFocus->aiWillDo += "			factor = " + to_string(10 - numWarsWithNeighbors * 5) + "\n";
		newFocus->aiWillDo += "			modifier = {\n";
		newFocus->aiWillDo += "				factor = 0\n";
		newFocus->aiWillDo += "				strength_ratio = { tag = " + targetNeighbors->getTag() + " ratio < 0.8 }\n";
		newFocus->aiWillDo += "			}";
		if (weakNeighbors.size() > 2) //make ai have this as a 0 modifier if they are at war
		{
			newFocus->aiWillDo += "\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "				factor = 0\n";
			newFocus->aiWillDo += "				OR = {\n";
			for (auto target2 : weakNeighbors)
			{
				if (targetNeighbors != target2)
				{
					newFocus->aiWillDo += "					has_war_with = " + target2->getTag() + "\n";
				}
			}
			newFocus->aiWillDo += "				}\n";
			newFocus->aiWillDo += "			}";
		}
		newFocus->aiWillDo += "\n";
		newFocus->aiWillDo += "		}";
		newFocus->completionReward += "= {\n";
		newFocus->completionReward += "			add_named_threat = { threat = 3 name = " + newFocus->id + " }\n";
		newFocus->completionReward += "			create_wargoal = {\n";
		newFocus->completionReward += "				type = annex_everything\n";
		newFocus->completionReward += "				target = " + targetNeighbors->getTag() + "\n";
		newFocus->completionReward += "			}\n";
		newFocus->completionReward += "		}";
		focuses.push_back(newFocus);
	}
	else
	{
		throw std::runtime_error("Could not load focus NeighborWar");
	}
}

void HoI4FocusTree::removeFocus(const string& id)
{
	focuses.erase(
		std::remove_if(
			focuses.begin(),
			focuses.end(),
			[id](std::shared_ptr<HoI4Focus> focus) {return focus->id == id; }
		),
		focuses.end()
	);
}


void HoI4FocusTree::output(const string& filename) const
{
	ofstream out(filename);
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not create " << filename;
		exit(-1);
	}

	out << "focus_tree = {\n";
	if (!dstCountryTag.empty())
	{
		out << "	id = " << dstCountryTag + "_focus\n";
		out << "	\n";
		out << "	country = {\n";
		out << "		factor = 0\n";
		out << "		\n";
		out << "		modifier = {\n";
		out << "			add = 10\n";
		out << "			tag = " << dstCountryTag << "\n";
		out << "		}\n";
		out << "	}\n";
		out << "	\n";
		out << "	default = no\n";
		out << "\n";
	}
	else
	{
		out << "	id = generic_focus\n";
		out << "	\n";
		out << "	country = {\n";
		out << "		factor = 1\n";
		out << "	}\n";
		out << "	\n";
		out << "	default = yes\n";
		out << "	reset_on_civilwar = no\n";
		out << "\n";
	}

	for (auto focus : focuses)
	{
		out << *focus;
		out << "\n";
	}

	out << "}";

	out.close();
}
