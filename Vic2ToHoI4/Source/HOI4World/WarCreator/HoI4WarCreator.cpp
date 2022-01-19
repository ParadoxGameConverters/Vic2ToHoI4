#include "HoI4WarCreator.h"
#include "HOI4World/Diplomacy/Faction.h"
#include "HOI4World/Events/Events.h"
#include "HOI4World/HoI4Focus.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/HoI4World.h"
#include "HOI4World/WarCreator/MapUtils.h"
#include "Log.h"
#include "Maps/MapData.h"
#include "Maps/ProvinceDefinitions.h"
#include "V2World/Countries/Country.h"
#include "V2World/Politics/Party.h"
#include "V2World/World/World.h"



HoI4WarCreator::HoI4WarCreator(HoI4::World* world,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration):
	 genericFocusTree(new HoI4FocusTree),
	 theWorld(world), mapUtils(theWorld->getStates(), theWorld->getCountries()), AggressorFactions(), WorldTargetMap()
{
	Log(LogLevel::Info) << "\tCreating wars";

	std::ofstream AILog;
	if (theConfiguration.getDebug())
	{
		AILog.open("AI-log.txt");
	}

	genericFocusTree->addGenericFocusTree(world->getMajorIdeologies());

	addAllTargetsToWorldTargetMap();
	double worldStrength = calculateWorldStrength(AILog, theConfiguration);

	std::set<std::shared_ptr<HoI4::Faction>> factionsAtWar;
	Log(LogLevel::Info) << "\t\tGenerating major wars";
	generateMajorWars(AILog,
		 factionsAtWar,
		 world->getMajorIdeologies(),
		 world,
		 theMapData,
		 provinceDefinitions,
		 hoi4Localisations,
		 theConfiguration);
	Log(LogLevel::Info) << "\t\tGenerating reconquest wars";
	generateReconquestWars(AILog, theMapData, provinceDefinitions, hoi4Localisations, theConfiguration);

	if (theConfiguration.getDebug())
	{
		AILog.close();
	}
}


void HoI4WarCreator::addAllTargetsToWorldTargetMap()
{
	for (auto greatPower: theWorld->getGreatPowers())
	{
		addTargetsToWorldTargetMap(greatPower);
	}
}


void HoI4WarCreator::addTargetsToWorldTargetMap(std::shared_ptr<HoI4::Country> country)
{
	if (country->getGovernmentIdeology() != "democratic")
	{
		int maxGCWars = 0;
		for (const auto& greatPowerTag: mapUtils.getGPsByDistance(*country, theWorld->getGreatPowers()))
		{
			auto greatPower = theWorld->findCountry(greatPowerTag);
			if (greatPower == nullptr)
			{
				continue;
			}

			if (maxGCWars > 1)
			{
				continue;
			}

			std::string HowToTakeGC = HowToTakeLand(greatPower, country, 3);
			if (HowToTakeGC == "noactionneeded" || HowToTakeGC == "factionneeded" || HowToTakeGC == "morealliesneeded")
			{
				if (greatPower != country)
				{
					auto relations = country->getRelations(greatPower->getTag());
					if ((relations) && (relations->getRelations() < 0))
					{
						std::vector<std::shared_ptr<HoI4::Country>> tempvector;
						if (WorldTargetMap.find(greatPower) == WorldTargetMap.end())
						{
							tempvector.push_back(country);
							WorldTargetMap.insert(std::make_pair(greatPower, tempvector));
						}
						if (WorldTargetMap.find(greatPower) != WorldTargetMap.end())
						{
							tempvector = WorldTargetMap.find(greatPower)->second;
							if (find(tempvector.begin(), tempvector.end(), country) == tempvector.end())
								tempvector.push_back(country);

							WorldTargetMap[greatPower] = tempvector;
						}
						++maxGCWars;
					}
				}
			}
		}
	}
}


double HoI4WarCreator::calculateWorldStrength(std::ofstream& AILog, const Configuration& theConfiguration) const
{
	double worldStrength = 0.0;
	for (auto Faction: theWorld->getFactions())
	{
		worldStrength += GetFactionStrength(Faction, 3);
	}

	if (theConfiguration.getDebug())
	{
		AILog << "Total world strength: " << worldStrength << "\n\n";
	}
	return worldStrength;
}


void HoI4WarCreator::generateMajorWars(std::ofstream& AILog,
	 std::set<std::shared_ptr<HoI4::Faction>>& factionsAtWar,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::World* world,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	if (theConfiguration.getDebug())
	{
		AILog << "Creating major wars\n";
	}

	for (auto country: theWorld->getCountries())
	{
		if (isImportantCountry(country.second))
		{
			std::vector<std::shared_ptr<HoI4::Faction>> newFactionsAtWar;

			if (country.second->getGovernmentIdeology() == "fascism")
			{
				newFactionsAtWar = fascistWarMaker(country.second,
					 AILog,
					 world,
					 theMapData,
					 provinceDefinitions,
					 hoi4Localisations,
					 theConfiguration);
			}
			else if (country.second->getGovernmentIdeology() == "communism")
			{
				newFactionsAtWar = communistWarCreator(country.second,
					 majorIdeologies,
					 AILog,
					 theMapData,
					 provinceDefinitions,
					 hoi4Localisations);
			}
			else if (country.second->getGovernmentIdeology() == "absolutist")
			{
				newFactionsAtWar = absolutistWarCreator(country.second, theMapData, provinceDefinitions, hoi4Localisations);
			}
			else if (country.second->getGovernmentIdeology() == "radical")
			{
				newFactionsAtWar = radicalWarCreator(country.second, theMapData, provinceDefinitions, hoi4Localisations);
			}
			else if (country.second->getGovernmentIdeology() == "democratic")
			{
				newFactionsAtWar = democracyWarCreator(country.second, hoi4Localisations);
			}


			factionsAtWar.insert(newFactionsAtWar.begin(), newFactionsAtWar.end());
		}
	}
}


double HoI4WarCreator::calculatePercentOfWorldAtWar(std::ofstream& AILog,
	 const std::set<std::shared_ptr<HoI4::Faction>>& factionsAtWar,
	 double worldStrength,
	 const Configuration& theConfiguration) const
{
	double countriesAtWarStrength = 0.0;
	for (auto faction: factionsAtWar)
	{
		countriesAtWarStrength += GetFactionStrength(faction, 3);
	}

	double percentOfWorldAtWar = countriesAtWarStrength / worldStrength;
	if (theConfiguration.getDebug())
	{
		AILog << "Fraction of world at war " << percentOfWorldAtWar << "\n";
	}

	return percentOfWorldAtWar;
}


bool HoI4WarCreator::isImportantCountry(std::shared_ptr<HoI4::Country> country)
{
	if (country->isGreatPower() || country->isHuman())
	{
		return true;
	}
	return false;
}


std::string HoI4WarCreator::HowToTakeLand(std::shared_ptr<HoI4::Country> TargetCountry,
	 std::shared_ptr<HoI4::Country> AttackingCountry,
	 double time)
{
	std::string type;
	if (TargetCountry != AttackingCountry)
	{
		auto targetFaction = findFaction(TargetCountry);
		auto myFaction = findFaction(AttackingCountry);
		// right now assumes you are stronger then them

		double myFactionDisStrength = GetFactionStrengthWithDistance(AttackingCountry, myFaction->getMembers(), time);
		double enemyFactionDisStrength = GetFactionStrengthWithDistance(TargetCountry, targetFaction->getMembers(), time);
		// lets check if I am stronger then their faction
		if (AttackingCountry->getStrengthOverTime(time) >= GetFactionStrength(targetFaction, static_cast<int>(time)))
		{
			// we are stronger, and dont even need ally help
			// ADD CONQUEST GOAL
			type = "noactionneeded";
		}
		else
		{
			// lets check if my faction is stronger

			if (myFactionDisStrength >= enemyFactionDisStrength)
			{
				// ADD CONQUEST GOAL
				type = "factionneeded";
			}
			else
			{
				// FIXME
				// hmm I am still weaker, maybe need to look for allies?
				type = "morealliesneeded";
				if (GetFactionStrengthWithDistance(AttackingCountry, myFaction->getMembers(), time) >=
					 GetFactionStrengthWithDistance(TargetCountry, targetFaction->getMembers(), time))
				{
					// ADD CONQUEST GOAL
				}
				else
				{
					// Time to Try Coup
					type = "coup";
				}
			}
		}
	}
	return type;
}
std::vector<std::shared_ptr<HoI4::Country>> HoI4WarCreator::GetMorePossibleAllies(
	 const std::shared_ptr<HoI4::Country>& CountryThatWantsAllies)
{
	int maxcountries = 0;
	std::vector<std::shared_ptr<HoI4::Country>> newPossibleAllies;
	std::set<std::string> currentAllies = CountryThatWantsAllies->getAllies();
	std::vector<std::shared_ptr<HoI4::Country>> CountriesWithin1000Miles; // Rename to actual distance
	for (auto country: theWorld->getCountries())
	{
		if (country.second->hasProvinces())
		{
			auto country2 = country.second;
			auto distance = mapUtils.getDistanceBetweenCapitals(*CountryThatWantsAllies, *country2);
			if (distance && (*distance <= 1000) && (country2 != CountryThatWantsAllies))
			{
				if (!currentAllies.contains(country2->getTag()))
				{
					CountriesWithin1000Miles.push_back(country2);
				}
			}
		}
	}
	std::string yourIdeology = CountryThatWantsAllies->getGovernmentIdeology();
	// look for all capitals within a distance of Berlin to Tehran
	for (unsigned int i = 0; i < CountriesWithin1000Miles.size(); i++)
	{
		std::string allyIdeology = CountriesWithin1000Miles[i]->getGovernmentIdeology();
		// possible government matches
		if ((allyIdeology == yourIdeology) /* ||
			 // add other possible combinations here, but maybe coordinate with HoI4World::governmentsAllowFaction()
			 */
		)
		{

			if (maxcountries < 2)
			{
				// FIXME
				// check if we are friendly at all?
				auto relationsWithPossibleAlly =
					 CountryThatWantsAllies->getRelations(CountriesWithin1000Miles[i]->getTag());
				// for now can only ally with people not in a faction, and must be worth adding
				if (relationsWithPossibleAlly)
				{
					int relationsValue = relationsWithPossibleAlly->getRelations();
					if ((relationsValue >= -50) && (findFaction(CountriesWithin1000Miles[i])->getMembers().size() <= 1))
					{
						// ok we dont hate each other, lets check how badly we need each other, well I do, the only reason I
						// am here is im trying to conquer a neighbor and am not strong enough! if
						// (GetFactionStrength(findFaction(country)) < 20000) //maybe also check if he has any fascist/comm
						// neighbors he doesnt like later?

						// well that ally is weak, he probably wants some friends
						if (relationsValue < 0)
						{
							// will take some NF to ally
							newPossibleAllies.push_back(CountriesWithin1000Miles[i]);
							maxcountries++;
						}
						if (relationsValue >= 0)
						{
							// well we are positive, 1 NF to add to ally should be fine
							newPossibleAllies.push_back(CountriesWithin1000Miles[i]);
							maxcountries++;
						}

						/*else if (relationsValue > 0)
						{
							//we are friendly, add 2 NF for ally? Good way to decide how many alliances there will be
							newPossibleAllies.push_back(country);
							i++;
						}*/
					}
				}
			}
		}
	}
	return newPossibleAllies;
}


double HoI4WarCreator::GetFactionStrengthWithDistance(std::shared_ptr<HoI4::Country> HomeCountry,
	 const std::vector<std::shared_ptr<HoI4::Country>>& Faction,
	 double time)
{
	double strength = 0.0;
	for (auto country: Faction)
	{
		double distanceMulti = 1;
		if (country != HomeCountry)
		{
			auto distance = mapUtils.getDistanceBetweenCapitals(*HomeCountry, *country);
			if (distance)
			{
				if (*distance < 300)
					distanceMulti = 1;
				else if (*distance < 500)
					distanceMulti = 0.9;
				else if (*distance < 750)
					distanceMulti = 0.8;
				else if (*distance < 1000)
					distanceMulti = 0.7;
				else if (*distance < 1500)
					distanceMulti = 0.5;
				else if (*distance < 2000)
					distanceMulti = 0.3;
				else
					distanceMulti = 0.2;
			}
		}

		strength += country->getStrengthOverTime(time) * distanceMulti;
	}
	return strength;
}


std::shared_ptr<HoI4::Faction> HoI4WarCreator::findFaction(std::shared_ptr<HoI4::Country> CheckingCountry)
{
	for (auto faction: theWorld->getFactions())
	{
		auto FactionMembers = faction->getMembers();
		if (std::find(FactionMembers.begin(), FactionMembers.end(), CheckingCountry) != FactionMembers.end())
		{
			// if country is in faction list, it is part of that faction
			return faction;
		}
	}

	std::vector<std::shared_ptr<HoI4::Country>> myself;
	myself.push_back(CheckingCountry);
	return std::make_shared<HoI4::Faction>(CheckingCountry, myself);
}


double HoI4WarCreator::GetFactionStrength(const std::shared_ptr<HoI4::Faction>& Faction, int years) const
{
	double strength = 0;
	for (auto country: Faction->getMembers())
	{
		strength += country->getStrengthOverTime(years);
	}
	return strength;
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::fascistWarMaker(std::shared_ptr<HoI4::Country> Leader,
	 std::ofstream& AILog,
	 const HoI4::World* world,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	std::vector<std::shared_ptr<HoI4::Faction>> CountriesAtWar;
	Log(LogLevel::Info) << "\t\tPicking targets for " + Leader->getTag();
	// too many lists, need to clean up
	std::vector<std::shared_ptr<HoI4::Country>> Anschluss;
	std::vector<std::shared_ptr<HoI4::Country>> Sudeten;
	std::vector<std::shared_ptr<HoI4::Country>> EqualTargets;
	std::vector<std::shared_ptr<HoI4::Country>> DifficultTargets;
	// getting country provinces and its neighbors
	std::set<std::string> neighbors;
	const auto& nearbyCountries = mapUtils.getNearbyCountries(Leader->getTag(), 500.0F);
	const auto& targets = Leader->getConquerStrategies();
	for (const auto& target: targets)
	{
		if (nearbyCountries.contains(target.getID()))
		{
			neighbors.insert(target.getID());
		}
	}

	std::set<std::string> Allies = Leader->getAllies();
	// should add method to look for cores you dont own
	// should add method to look for more allies

	// lets look for weak neighbors
	Log(LogLevel::Info) << "\t\t\tDoing Neighbor calcs for " + Leader->getTag();
	for (const auto& neighborTag: neighbors)
	{
		const auto neighbor = world->findCountry(neighborTag);
		if (neighbor == nullptr)
		{
			continue;
		}

		// lets check to see if they are not our ally and not a great country
		if (!Allies.contains(neighbor->getTag()) && !neighbor->isGreatPower())
		{
			volatile double enemystrength = neighbor->getStrengthOverTime(1.5);
			volatile double mystrength = Leader->getStrengthOverTime(1.5);
			// lets see their strength is at least < 20%
			if (neighbor->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5) * 0.2 &&
				 findFaction(neighbor)->getMembers().size() == 1)
			{
				// they are very weak
				Anschluss.push_back(neighbor);
			}
			// if not, lets see their strength is at least < 60%
			else if (neighbor->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5) * 0.6 &&
						neighbor->getStrengthOverTime(1.5) > Leader->getStrengthOverTime(1.5) * 0.2 &&
						findFaction(neighbor)->getMembers().size() == 1)
			{
				// they are weak and we can get 1 of these countries in sudeten deal
				Sudeten.push_back(neighbor);
			}
			// if not, lets see their strength is at least = to ours%
			else if (neighbor->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5))
			{
				// EqualTargets.push_back(neigh);
				EqualTargets.push_back(neighbor);
			}
			// if not, lets see their strength is at least < 120%
			else if (neighbor->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5) * 1.2)
			{
				// StrongerTargets.push_back(neigh);
				DifficultTargets.push_back(neighbor);
			}
		}
	}
	// std::string that contains all events
	std::vector<std::shared_ptr<HoI4::Country>> anschlussTargets;

	// look through every anchluss and see its difficulty
	for (auto target: Anschluss)
	{
		std::string type;
		// outputs are for HowToTakeLand()
		// noactionneeded -  Can take target without any help
		// factionneeded - can take target and faction with attackers faction helping
		// morealliesneeded - can take target with more allies, comes with "newallies" in map
		// coup - cant take over, need to coup
		type = HowToTakeLand(target, Leader, 1.5);
		if (type == "noactionneeded")
		{
			// too many std::vectors, need to clean up
			anschlussTargets.push_back(target);
		}
	}
	// gives us generic focus tree start
	auto FocusTree = genericFocusTree->makeCustomizedCopy(*Leader);

	std::vector<std::shared_ptr<HoI4::Country>> sudetenTargets;
	for (auto target: Sudeten)
	{
		std::string type;
		// outputs are
		// noactionneeded -  Can take target without any help
		// factionneeded - can take target and faction with attackers faction helping
		// morealliesneeded - can take target with more allies, comes with "newallies" in map
		// coup - cant take over, need to coup
		type = HowToTakeLand(target, Leader, 2.5);

		if (type == "noactionneeded")
		{
			sudetenTargets.push_back(target);
		}
	}
	// find neighboring states to take in sudeten deal
	std::map<std::string, std::vector<int>> demandedStates;

	const auto leaderCapitalPosition = mapUtils.getCapitalPosition(*Leader);
	if (leaderCapitalPosition)
	{
		for (const auto& target: sudetenTargets)
		{
			std::set<int> borderStates = mapUtils.findBorderStates(*Leader,
				 *target,
				 world->getProvinceToStateIDMap(),
				 theMapData,
				 provinceDefinitions);
			demandedStates[target->getTag()] =
				 mapUtils.sortStatesByDistance(borderStates, *leaderCapitalPosition, world->getStates());
		}
	}

	// events for allies
	auto newAllies = GetMorePossibleAllies(Leader);
	if (theConfiguration.getCreateFactions())
	{
		if (newAllies.size() > 0 && Leader->isInFaction())
		{
			std::vector<std::shared_ptr<HoI4::Country>> self;
			self.push_back(Leader);
			auto newFaction = std::make_shared<HoI4::Faction>(Leader, self);
			Leader->setFaction(newFaction);
		}
	}

	std::vector<std::shared_ptr<HoI4::Faction>> FactionsAttackingMe;
	if (WorldTargetMap.contains(Leader))
	{
		for (auto country: WorldTargetMap.find(Leader)->second)
		{
			auto attackingFaction = findFaction(country);
			if (find(FactionsAttackingMe.begin(), FactionsAttackingMe.end(), attackingFaction) ==
				 FactionsAttackingMe.end())
			{
				FactionsAttackingMe.push_back(attackingFaction);
			}
		}
		double FactionsAttackingMeStrength = 0;
		for (auto attackingFaction: FactionsAttackingMe)
		{
			FactionsAttackingMeStrength += GetFactionStrengthWithDistance(Leader, attackingFaction->getMembers(), 3);
		}
		if (theConfiguration.getDebug())
		{
			AILog << "\t" << Leader->getTag() << " is under threat, there are " << FactionsAttackingMe.size()
					<< " faction(s) attacking them, I have a strength of " << GetFactionStrength(findFaction(Leader), 3)
					<< " and they have a strength of " << FactionsAttackingMeStrength << "\n";
		}
		if (FactionsAttackingMeStrength > GetFactionStrength(findFaction(Leader), 3))
		{
			int numAlliances = 0;
			for (auto& greatPower: theWorld->getGreatPowers())
			{
				if (const auto relations = Leader->getRelations(greatPower->getTag());
					 (relations) && (relations->getRelations() > 0) && (numAlliances < 1))
				{
					if (theConfiguration.getDebug())
					{
						AILog << "\t" << Leader->getTag() << " can attempt to ally " << greatPower->getTag() << "\n";
					}
					if (theConfiguration.getCreateFactions())
					{
						if (greatPower->isInFaction())
						{
							std::vector<std::shared_ptr<HoI4::Country>> self;
							self.push_back(greatPower);
							auto newFaction = std::make_shared<HoI4::Faction>(greatPower, self);
							greatPower->setFaction(newFaction);
						}
					}
					newAllies.push_back(greatPower);
					++numAlliances;
				}
			}
		}
	}

	// Declaring war with Great Country
	std::vector<std::shared_ptr<HoI4::Country>> GCTargets;
	for (const auto& greatPowerTag: mapUtils.getGPsByDistance(*Leader, theWorld->getGreatPowers()))
	{
		auto greatPower = theWorld->findCountry(greatPowerTag);
		if (greatPower == nullptr)
		{
			continue;
		}

		std::string HowToTakeGC = HowToTakeLand(greatPower, Leader, 3);
		if (HowToTakeGC == "noactionneeded" || HowToTakeGC == "factionneeded" || HowToTakeGC == "morealliesneeded")
		{
			auto relations = Leader->getRelations(greatPowerTag);
			if ((greatPower != Leader) && (relations) && (relations->getRelations() < 0))
			{
				if (GCTargets.size() < maxGCWars)
				{
					GCTargets.push_back(greatPower);
				}
			}
		}
	}

	if (!anschlussTargets.empty())
	{
		FocusTree->addFascistAnnexationBranch(Leader,
			 anschlussTargets,
			 sudetenTargets.size(),
			 theWorld->getEvents(),
			 hoi4Localisations);
	}

	if (!sudetenTargets.empty() && !demandedStates.empty())
	{
		FocusTree->addFascistSudetenBranch(Leader,
			 anschlussTargets,
			 sudetenTargets,
			 demandedStates,
			 theWorld->getEvents(),
			 hoi4Localisations);
	}

	if (!GCTargets.empty())
	{
		FocusTree->addGPWarBranch(Leader,
			 newAllies,
			 GCTargets,
			 "Fascist",
			 theWorld->getEvents(),
			 theWorld->getFactionNameMapper(),
			 hoi4Localisations);
	}

	if (FocusTree)
	{
		Leader->giveNationalFocus(FocusTree);
	}
	return CountriesAtWar;
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::communistWarCreator(std::shared_ptr<HoI4::Country> Leader,
	 const std::set<std::string>& majorIdeologies,
	 std::ofstream& AILog,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations)
{
	std::vector<std::shared_ptr<HoI4::Faction>> CountriesAtWar;
	// communism still needs great country war events
	Log(LogLevel::Info) << "\t\tPicking targets for " + Leader->getTag();
	std::set<std::string> neighbors;
	const auto& nearbyCountries = mapUtils.getNearbyCountries(Leader->getTag(), 400);
	const auto& targets = Leader->getConquerStrategies();
	for (const auto& target: targets)
	{
		if (nearbyCountries.contains(target.getID()))
		{
			neighbors.insert(target.getID());
		}
	}

	std::set<std::string> Allies = Leader->getAllies();
	std::vector<std::shared_ptr<HoI4::Country>> coups;
	std::vector<std::shared_ptr<HoI4::Country>> forcedtakeover;

	// if (Permanant Revolution)
	// Decide between Anti - Democratic Focus, Anti - Monarch Focus, or Anti - Fascist Focus(Look at all great powers and
	// get average relation between each ideology, the one with the lowest average relation leads to that focus). Attempt
	// to ally with other Communist Countries(with Permanant Revolution)
	Log(LogLevel::Info) << "\t\t\tDoing Neighbor calcs for " + Leader->getTag();
	for (const auto& neighborTag: neighbors)
	{
		const auto neighbor = theWorld->findCountry(neighborTag);
		if (neighbor == nullptr)
		{
			continue;
		}
		// lets check to see if they are our ally and not a great country
		if (!Allies.contains(neighbor->getTag()) && !neighbor->isGreatPower())
		{
			double com = 0;
			auto neighFaction = findFaction(neighbor);
			for (auto party: neighbor->getIdeologySupport())
			{
				if ((party.first == "socialist") || (party.first == "communist") || (party.first == "anarcho_liberal"))
					com += party.second;
			}
			if (const auto& rulingParty = neighbor->getRulingParty();
				 com > 25 && rulingParty->getIdeology() != "communist" && HowToTakeLand(neighbor, Leader, 2.5) == "coup")
			{
				// look for neighboring countries to spread communism too(Need 25 % or more Communism support), Prioritizing
				// those with "Communism Allowed" Flags, prioritizing those who are weakest 	Method() Influence Ideology
				// and
				// Attempt Coup
				coups.push_back(neighbor);
			}
			else if (neighFaction->getMembers().size() == 1 && rulingParty->getIdeology() != "communist")
			{
				//	Then look for neighboring countries to spread communism by force, prioritizing weakest first
				forcedtakeover.push_back(neighbor);
				//	Depending on Anti - Ideology Focus, look for allies in alternate ideologies to get to ally with to
				// declare war against Anti - Ideology Country.
			}
		}
	}
	// if (Socialism in One State)
	//	Events / Focuses to increase Industrialization and defense of the country, becomes Isolationist
	//	Eventually gets events to drop Socialism in One state and switch to permanant revolution(Maybe ? )

	std::map<std::string, std::vector<std::shared_ptr<HoI4::Country>>> TargetMap;
	std::vector<std::shared_ptr<HoI4::Country>> nan;
	std::vector<std::shared_ptr<HoI4::Country>> fn;
	std::vector<std::shared_ptr<HoI4::Country>> man;
	std::vector<std::shared_ptr<HoI4::Country>> coup;
	for (auto target: forcedtakeover)
	{
		std::string type;
		// outputs are
		// noactionneeded -  Can take target without any help
		// factionneeded - can take target and faction with attackers faction helping
		// morealliesneeded - can take target with more allies, comes with "newallies" in map
		// coup - cant take over, need to coup
		type = HowToTakeLand(target, Leader, 2.5);
		if (type == "noactionneeded")
			nan.push_back(target);
		else if (type == "factionneeded")
			fn.push_back(target);
		else if (type == "morealliesneeded")
			man.push_back(target);
		else if (type == "coup")
			coup.push_back(target);
	}
	// insert these values in targetmap for use later possibly?
	TargetMap.emplace("noactionneeded", nan);
	TargetMap.emplace("factionneeded", fn);
	TargetMap.emplace("morealliesneeded", man);
	TargetMap.emplace("coup", coup);

	std::vector<std::shared_ptr<HoI4::Country>> TargetsByTech;
	bool first = true;
	// FIXME
	// Right now just uses everyone in forcedtakover, doesnt use nan, fn, ect...
	for (auto country: forcedtakeover)
	{
		if (first)
		{
			TargetsByTech.push_back(country);
			first = false;
		}
		else
		{
			// makes sure not a coup target
			if (find(coups.begin(), coups.end(), country) == coups.end())
			{
				if (TargetsByTech.front()->getTechnologyCount() < country->getTechnologyCount())
				{
					TargetsByTech.insert(TargetsByTech.begin(), country);
				}
				else
					TargetsByTech.push_back(country);
			}
		}
	}

	// Candidates for Get Allies foci
	auto newAllies = GetMorePossibleAllies(Leader);

	// Declaring war with Great Country
	std::vector<std::shared_ptr<HoI4::Country>> GCTargets;
	for (const auto& greatPowerTag: mapUtils.getGPsByDistance(*Leader, theWorld->getGreatPowers()))
	{
		auto greatPower = theWorld->findCountry(greatPowerTag);
		if (greatPower == nullptr)
		{
			continue;
		}

		std::string HowToTakeGC = HowToTakeLand(greatPower, Leader, 3);
		if (HowToTakeGC == "noactionneeded" || HowToTakeGC == "factionneeded")
		{
			if (greatPower != Leader)
				GCTargets.push_back(greatPower);
		}
		if (HowToTakeGC == "morealliesneeded")
		{
			// TODO
		}
	}
	std::vector<std::shared_ptr<HoI4::Country>> finalTargets;
	for (auto GC: GCTargets)
	{
		auto relations = Leader->getRelations(GC->getTag());
		if ((relations) && (relations->getRelations() < 0))
		{
			finalTargets.push_back(GC);
		}
		if (finalTargets.size() >= maxGCWars)
			break;
	}

	auto FocusTree = genericFocusTree->makeCustomizedCopy(*Leader);
	if (!forcedtakeover.empty())
	{
		FocusTree->addCommunistCoupBranch(Leader, forcedtakeover, majorIdeologies, hoi4Localisations);
	}
	if (!TargetsByTech.empty())
	{
		FocusTree->addCommunistWarBranch(Leader, TargetsByTech, theWorld->getEvents(), hoi4Localisations);
	}
	if (!newAllies.empty() && !finalTargets.empty())
	{
		FocusTree->addGPWarBranch(Leader,
			 newAllies,
			 finalTargets,
			 "Communist",
			 theWorld->getEvents(),
			 theWorld->getFactionNameMapper(),
			 hoi4Localisations);
	}

	if (FocusTree)
	{
		Leader->giveNationalFocus(FocusTree);
	}

	return CountriesAtWar;
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::democracyWarCreator(std::shared_ptr<HoI4::Country> Leader,
	 HoI4::Localisation& hoi4Localisations)
{
	std::vector<std::shared_ptr<HoI4::Faction>> CountriesAtWar;
	std::map<int, std::shared_ptr<HoI4::Country>> CountriesToContain;
	std::vector<std::shared_ptr<HoI4::Country>> vCountriesToContain;
	std::set<std::string> Allies = Leader->getAllies();
	auto FocusTree = genericFocusTree->makeCustomizedCopy(*Leader);
	for (auto GC: theWorld->getGreatPowers())
	{
		auto relations = Leader->getRelations(GC->getTag());
		if (relations)
		{
			double relationVal = relations->getRelations();
			if (relationVal < 100 && GC->getGovernmentIdeology() != "democratic" && !Allies.contains(GC->getTag()))
			{
				CountriesToContain.insert(std::make_pair(static_cast<int>(relationVal), GC));
			}
		}
	}
	for (auto country: CountriesToContain)
	{
		vCountriesToContain.push_back(country.second);
	}
	if (vCountriesToContain.empty())
	{
		return CountriesAtWar;
	}

	CountriesAtWar.push_back(findFaction(Leader));

	FocusTree->addDemocracyNationalFocuses(Leader, vCountriesToContain, hoi4Localisations);
	Leader->giveNationalFocus(FocusTree);

	return CountriesAtWar;
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::absolutistWarCreator(std::shared_ptr<HoI4::Country> country,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations)
{
	std::vector<std::shared_ptr<HoI4::Faction>> CountriesAtWar;
	auto focusTree = genericFocusTree->makeCustomizedCopy(*country);

	Log(LogLevel::Info) << "\t\tPicking targets for " + country->getTag();

	auto weakNeighbors = findWeakNeighbors(country, theMapData, provinceDefinitions);
	auto weakColonies = findWeakColonies(country, theMapData, provinceDefinitions);
	focusTree->addAbsolutistEmpireNationalFocuses(country, weakColonies, weakNeighbors, hoi4Localisations);


	if (auto greatPowerTargets = getGreatPowerTargets(country); !greatPowerTargets.empty())
	{
		CountriesAtWar = addGreatPowerWars(country, *focusTree, greatPowerTargets, hoi4Localisations);
		addTradeEvents(country, greatPowerTargets);
	}

	if (focusTree)
	{
		country->giveNationalFocus(focusTree);
	}

	return CountriesAtWar;
}


void HoI4WarCreator::generateReconquestWars(std::ofstream& AILog,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	if (theConfiguration.getDebug())
	{
		AILog << "Creating Reconquest wars\n";
	}

	for (const auto& [tag, country]: theWorld->getCountries())
	{
		if (tag == "UCV" || country->isUnrecognizedNation())
		{
			continue;
		}
		if (country->getNationalFocus())
		{
			continue;
		}
		int numWarsWithNeighbors = 0;
		auto focusTree = genericFocusTree->makeCustomizedCopy(*country);
		const auto& coreHolders = focusTree->addReconquestBranch(country,
			 numWarsWithNeighbors,
			 theWorld->getMajorIdeologies(),
			 theWorld->getStates(),
			 hoi4Localisations);

		const auto& conquerTags = focusTree->addConquerBranch(country,
			 numWarsWithNeighbors,
			 theWorld->getMajorIdeologies(),
			 coreHolders,
			 theWorld->getStates(),
			 hoi4Localisations);

		if (numWarsWithNeighbors > 0)
		{
			country->giveNationalFocus(focusTree);
		}
	}
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::radicalWarCreator(std::shared_ptr<HoI4::Country> country,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations)
{
	return absolutistWarCreator(country, theMapData, provinceDefinitions, hoi4Localisations);
}


std::vector<std::shared_ptr<HoI4::Country>> HoI4WarCreator::findWeakNeighbors(std::shared_ptr<HoI4::Country> country,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions)
{
	std::vector<std::shared_ptr<HoI4::Country>> weakNeighbors;

	auto allies = country->getAllies();
	const auto& nearbyCountries = mapUtils.getNearbyCountries(country->getTag(), 500);
	const auto& targets = country->getConquerStrategies();
	for (const auto& target: targets)
	{
		const auto& neighborTag = target.getID();
		if (!nearbyCountries.contains(neighborTag))
		{
			continue;
		}
		if (allies.contains(neighborTag))
		{
			continue;
		}

		auto neighbor = theWorld->findCountry(neighborTag);
		if (neighbor == nullptr)
		{
			continue;
		}
		if (neighbor->isUnrecognizedNation() || neighbor->isGeneratedDominion())
		{
			continue;
		}

		if (neighbor->isGreatPower())
		{
			continue;
		}

		double enemystrength = neighbor->getStrengthOverTime(1.5);
		double mystrength = country->getStrengthOverTime(1.5);
		if ((enemystrength < (mystrength * 0.5)) && (findFaction(neighbor)->getMembers().size() == 1))
		{
			weakNeighbors.push_back(neighbor);
		}
	}

	return weakNeighbors;
}


std::vector<std::shared_ptr<HoI4::Country>> HoI4WarCreator::findWeakColonies(std::shared_ptr<HoI4::Country> country,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions)
{
	std::vector<std::pair<std::shared_ptr<HoI4::Country>, float>> weakColonies;

	auto allies = country->getAllies();
	for (auto neighborTag: mapUtils.getFarCountries(country->getTag(), 400))
	{
		if (allies.contains(neighborTag))
		{
			continue;
		}

		auto neighbor = theWorld->findCountry(neighborTag);
		if (neighbor == nullptr)
		{
			continue;
		}
		if (neighbor->isUnrecognizedNation() || neighbor->isGeneratedDominion())
		{
			continue;
		}
		if (neighbor->isGreatPower())
		{
			continue;
		}
		if (!neighbor->hasProvinces())
		{
			continue;
		}
		if (neighbor->isCivilized())
		{
			continue;
		}
		const auto& distanceBetweenCapitals = mapUtils.getDistanceBetweenCapitals(*country, *neighbor);
		if (!distanceBetweenCapitals || *distanceBetweenCapitals > 1500)
		{
			continue;
		}

		double enemystrength = neighbor->getStrengthOverTime(1.5);
		double mystrength = country->getStrengthOverTime(1.5);
		if ((enemystrength < mystrength * 0.5) && (findFaction(neighbor)->getMembers().size() == 1))
		{
			weakColonies.push_back(std::make_pair(neighbor, *distanceBetweenCapitals));
		}
	}
	std::sort(weakColonies.begin(),
		 weakColonies.end(),
		 [](const std::pair<std::shared_ptr<HoI4::Country>, float>& a,
			  const std::pair<std::shared_ptr<HoI4::Country>, float>& b) {
			 return a.second < b.second;
		 });
	std::vector<std::shared_ptr<HoI4::Country>> sortedWeakColonies;
	for (const auto& [colony, unused]: weakColonies)
	{
		sortedWeakColonies.push_back(colony);
	}
	return sortedWeakColonies;
}


std::vector<std::shared_ptr<HoI4::Country>> HoI4WarCreator::getGreatPowerTargets(std::shared_ptr<HoI4::Country> country)
{
	std::vector<std::shared_ptr<HoI4::Country>> greatPowerTargets;

	for (auto greatPowerTag: mapUtils.getGPsByDistance(*country, theWorld->getGreatPowers()))
	{
		auto greatPower = theWorld->findCountry(greatPowerTag);
		if (greatPower == nullptr)
		{
			continue;
		}

		std::string prereqsNeeded = HowToTakeLand(greatPower, country, 3);
		if (prereqsNeeded == "noactionneeded" || prereqsNeeded == "factionneeded")
		{
			if (greatPower != country)
			{
				greatPowerTargets.push_back(greatPower);
			}
		}
		if (prereqsNeeded == "morealliesneeded")
		{
		}
	}

	return greatPowerTargets;
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::addGreatPowerWars(std::shared_ptr<HoI4::Country> country,
	 HoI4FocusTree& FocusTree,
	 std::vector<std::shared_ptr<HoI4::Country>>& greatPowerTargets,
	 HoI4::Localisation& hoi4Localisations)
{
	std::vector<std::shared_ptr<HoI4::Faction>> countriesAtWar;

	int numWarsWithGreatPowers = 0;
	for (auto target: greatPowerTargets)
	{
		if (numWarsWithGreatPowers >= 2)
		{
			break;
		}

		auto relations = country->getRelations(target->getTag());
		if ((!relations) || (relations->getRelations() >= 0))
		{
			continue;
		}

		std::set<std::string> Allies = country->getAllies();
		if (!Allies.contains(target->getTag()))
		{
			auto possibleTargetName = target->getName();
			std::string targetName;
			if (possibleTargetName)
			{
				targetName = *possibleTargetName;
			}
			else
			{
				Log(LogLevel::Warning) << "Could not set target name in great power war creator";
				targetName.clear();
			}

			countriesAtWar.push_back(findFaction(country));

			std::shared_ptr<HoI4Focus> newFocus = std::make_shared<HoI4Focus>();
			newFocus->id = "War_with" + target->getTag() + country->getTag();
			newFocus->icon = "GFX_goal_generic_major_war";
			newFocus->text = "War_with" + target->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "			has_war = no\n";
			const auto& truceUntil = country->getTruceUntil(target->getTag());
			if (truceUntil && *truceUntil > date("1939.1.1"))
			{
				newFocus->available += "\t\t\tdate > " + truceUntil->toString() + "\n";
			}
			else
			{
				newFocus->available += "			date > 1939.1.1\n";
			}
			newFocus->available += "		}";
			newFocus->xPos = 31 + numWarsWithGreatPowers * 2;
			newFocus->yPos = 5;
			newFocus->cost = 10;
			newFocus->aiWillDo = "= {\n";
			newFocus->aiWillDo += "			factor = " + std::to_string(10 - numWarsWithGreatPowers * 5) + "\n";
			newFocus->aiWillDo += "			modifier = {\n";
			newFocus->aiWillDo += "				factor = 0\n";
			newFocus->aiWillDo += "				strength_ratio = { tag = " + target->getTag() + " ratio < 0.8 }\n";
			newFocus->aiWillDo += "			}";
			if (greatPowerTargets.size() > 2) // make ai have this as a 0 modifier if they are at war
			{
				newFocus->aiWillDo += "\n";
				newFocus->aiWillDo += "			modifier = {\n";
				newFocus->aiWillDo += "				factor = 0\n";
				newFocus->aiWillDo += "				OR = {\n";
				for (auto target2: greatPowerTargets)
				{
					if (target != target2)
					{
						newFocus->aiWillDo += "					has_war_with = " + target2->getTag() + "\n";
					}
				}
				newFocus->aiWillDo += "				}\n";
				newFocus->aiWillDo += "			}";
			}
			newFocus->aiWillDo += "\n";
			newFocus->aiWillDo += "		}";
			newFocus->bypass += "= {\n";
			newFocus->bypass += " 		has_war_with = " + target->getTag() + "\n";
			newFocus->bypass += " 	}";
			newFocus->completionReward += "= {\n";
			newFocus->completionReward +=
				 "			add_named_threat = { threat = 5 name = \"War with " + targetName + "\" }\n";
			newFocus->completionReward += "			declare_war_on = {\n";
			newFocus->completionReward += "				type = annex_everything\n";
			newFocus->completionReward += "				target = " + target->getTag() + "\n";
			newFocus->completionReward += "			}\n";
			newFocus->completionReward += "		}";
			FocusTree.addFocus(newFocus);
			hoi4Localisations.copyFocusLocalisations("War_with", newFocus->text);
			hoi4Localisations.updateLocalisationText(newFocus->text, "$TARGET", target->getTag());
			hoi4Localisations.updateLocalisationText(newFocus->text + "_desc", "$TARGET", target->getTag());

			numWarsWithGreatPowers++;
		}
	}

	return countriesAtWar;
}


void HoI4WarCreator::addTradeEvents(std::shared_ptr<HoI4::Country> country,
	 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowerTargets)
{
	for (auto greatPowerTarget: greatPowerTargets)
	{
		auto relations = country->getRelations(greatPowerTarget->getTag());
		if ((!relations) || (relations->getRelations() >= 0))
		{
			continue;
		}

		theWorld->getEvents().createTradeEvent(*country, greatPowerTarget->getTag());
	}
}