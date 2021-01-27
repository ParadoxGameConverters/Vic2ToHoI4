#include "HoI4WarCreator.h"
#include "HOI4World/Diplomacy/Faction.h"
#include "HOI4World/Events/Events.h"
#include "HOI4World/HoI4Focus.h"
#include "HOI4World/HoI4Localisation.h"
#include "HOI4World/HoI4World.h"
#include "HOI4World/Map/MapData.h"
#include "HOI4World/ProvinceDefinitions.h"
#include "Log.h"
#include "V2World/Countries/Country.h"
#include "V2World/Politics/Party.h"
#include "V2World/World/World.h"



HoI4WarCreator::HoI4WarCreator(HoI4::World* world,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration):
	 genericFocusTree(new HoI4FocusTree),
	 theWorld(world), AggressorFactions(), WorldTargetMap(), provincePositions(), provinceToOwnerMap()
{
	Log(LogLevel::Info) << "\tCreating wars";

	ofstream AILog;
	if (theConfiguration.getDebug())
	{
		AILog.open("AI-log.txt");
	}

	genericFocusTree->addGenericFocusTree(world->getMajorIdeologies());

	determineProvinceOwners();
	addAllTargetsToWorldTargetMap();
	double worldStrength = calculateWorldStrength(AILog, theConfiguration);

	set<shared_ptr<HoI4::Faction>> factionsAtWar;
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
	generateReconquestWars(AILog, hoi4Localisations, theConfiguration);
	Log(LogLevel::Info) << "\t\tGenerating additional wars";
	generateAdditionalWars(AILog,
		 factionsAtWar,
		 worldStrength,
		 theMapData,
		 provinceDefinitions,
		 hoi4Localisations,
		 theConfiguration);

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


void HoI4WarCreator::addTargetsToWorldTargetMap(shared_ptr<HoI4::Country> country)
{
	if (country->getGovernmentIdeology() != "democratic")
	{
		int maxGCWars = 0;
		for (auto GC: getDistancesToGreatPowers(country))
		{
			if (maxGCWars < 2)
			{
				string HowToTakeGC = HowToTakeLand(GC.second, country, 3);
				if (HowToTakeGC == "noactionneeded" || HowToTakeGC == "factionneeded" || HowToTakeGC == "morealliesneeded")
				{
					if (GC.second != country)
					{
						auto relations = country->getRelations(GC.second->getTag());
						if ((relations) && (relations->getRelations() < 0))
						{
							vector<shared_ptr<HoI4::Country>> tempvector;
							if (WorldTargetMap.find(GC.second) == WorldTargetMap.end())
							{
								tempvector.push_back(country);
								WorldTargetMap.insert(make_pair(GC.second, tempvector));
							}
							if (WorldTargetMap.find(GC.second) != WorldTargetMap.end())
							{
								tempvector = WorldTargetMap.find(GC.second)->second;
								if (find(tempvector.begin(), tempvector.end(), country) == tempvector.end())
									tempvector.push_back(country);

								WorldTargetMap[GC.second] = tempvector;
							}
							maxGCWars++;
						}
					}
				}
			}
		}
	}
}


map<double, shared_ptr<HoI4::Country>> HoI4WarCreator::getDistancesToGreatPowers(shared_ptr<HoI4::Country> country)
{
	map<double, shared_ptr<HoI4::Country>> GCDistance;
	for (auto GC: theWorld->getGreatPowers())
	{
		set<string> Allies = country->getAllies();
		if (!Allies.contains(GC->getTag()))
		{
			auto distance = getDistanceBetweenCapitals(country, GC);
			if (distance && (*distance < 2200))
			{
				GCDistance.insert(make_pair(*distance, GC));
			}
		}
	}

	return GCDistance;
}


double HoI4WarCreator::calculateWorldStrength(ofstream& AILog, const Configuration& theConfiguration) const
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


void HoI4WarCreator::generateMajorWars(ofstream& AILog,
	 set<shared_ptr<HoI4::Faction>>& factionsAtWar,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::World* world,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
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
			vector<shared_ptr<HoI4::Faction>> newFactionsAtWar;

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


double HoI4WarCreator::calculatePercentOfWorldAtWar(ofstream& AILog,
	 const set<shared_ptr<HoI4::Faction>>& factionsAtWar,
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


void HoI4WarCreator::generateAdditionalWars(ofstream& AILog,
	 set<shared_ptr<HoI4::Faction>>& factionsAtWar,
	 double worldStrength,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	auto countriesEvilnessSorted = findEvilCountries();

	for (auto country = countriesEvilnessSorted.rbegin(); country != countriesEvilnessSorted.rend(); country++)
	{
		if (!isImportantCountry(*country))
		{
			if (theConfiguration.getDebug())
			{
				auto name = (*country)->getName();
				if (name)
				{
					AILog << "Checking for war in " + *name << "\n";
				}
			}
			vector<shared_ptr<HoI4::Faction>> newCountriesatWar;
			newCountriesatWar =
				 neighborWarCreator(*country, AILog, theMapData, provinceDefinitions, hoi4Localisations, theConfiguration);

			for (auto addedFactions: newCountriesatWar)
			{
				if (!factionsAtWar.contains(addedFactions))
				{
					factionsAtWar.insert(addedFactions);
				}
			}
		}
	}
}


bool HoI4WarCreator::isImportantCountry(shared_ptr<HoI4::Country> country)
{
	if (country->isGreatPower() || country->isHuman())
	{
		return true;
	}
	return false;
}


std::vector<std::shared_ptr<HoI4::Country>> HoI4WarCreator::findEvilCountries() const
{
	std::multimap<double, std::shared_ptr<HoI4::Country>> countryEvilness;
	std::vector<std::shared_ptr<HoI4::Country>> countriesEvilnessSorted;

	for (auto country: theWorld->getCountries())
	{
		double evilness = 0.5;
		auto ideology = country.second->getGovernmentIdeology();
		if (ideology == "fascism")
		{
			evilness += 5;
		}
		else if (ideology == "absolutist")
		{
			evilness += 3;
		}
		else if (ideology == "communism")
		{
			evilness += 3;
		}
		else if (ideology == "radical")
		{
			evilness += 3;
		}
		else if (ideology == "neutrality")
		{
			auto leaderIdeology = country.second->getLeaderIdeology();
			if (leaderIdeology == "fascism_ideology_neutral")
			{
				evilness += 5;
			}
			else if ((leaderIdeology == "prussian_const_neutral") || (leaderIdeology == "absolute_monarchy_neutral") ||
						(leaderIdeology == "dictatorship_neutral") || (leaderIdeology == "theocracy_neutral") ||
						(leaderIdeology == "despotism"))
			{
				evilness += 3;
			}
			else if (leaderIdeology == "leninism_neutral")
			{
				evilness += 5;
			}
			else if ((leaderIdeology == "minarchism_neutral") || (leaderIdeology == "oligarchism"))
			{
				evilness += 5;
			}
		}

		if (const auto& rulingParty = country.second->getRulingParty(); rulingParty != std::nullopt)
		{
			auto warPolicy = rulingParty->getWarPolicy();
			if (warPolicy == "jingoism")
			{
				evilness += 3;
			}
			else if (warPolicy == "pro_military")
			{
				evilness += 2;
			}
			else if (warPolicy == "anti_military")
			{
				evilness -= 1;
			}
			else if (warPolicy == "pacifism")
			{
				evilness -= 3;
			}
		}

		if (evilness > 2)
		{
			countryEvilness.insert(make_pair(evilness, country.second));
		}
	}

	// put them into a vector so we know their order
	for (auto iterator = countryEvilness.begin(); iterator != countryEvilness.end(); ++iterator)
	{
		countriesEvilnessSorted.push_back(iterator->second);
	}

	return countriesEvilnessSorted;
}


void HoI4WarCreator::setSphereLeaders(const Vic2::World* sourceWorld)
{
	for (auto greatPower: theWorld->getGreatPowers())
	{
		auto relations = greatPower->getRelations();
		for (auto relation: relations)
		{
			if (relation.second.getSphereLeader())
			{
				auto spheredcountry = theWorld->getCountries().find(relation.second.getTag());
				if (spheredcountry != theWorld->getCountries().end())
				{
					spheredcountry->second->setSphereLeader(greatPower->getTag());
				}
			}
		}
	}
}


string HoI4WarCreator::HowToTakeLand(shared_ptr<HoI4::Country> TargetCountry,
	 shared_ptr<HoI4::Country> AttackingCountry,
	 double time)
{
	string type;
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
vector<shared_ptr<HoI4::Country>> HoI4WarCreator::GetMorePossibleAllies(
	 const shared_ptr<HoI4::Country>& CountryThatWantsAllies)
{
	int maxcountries = 0;
	vector<shared_ptr<HoI4::Country>> newPossibleAllies;
	set<string> currentAllies = CountryThatWantsAllies->getAllies();
	vector<shared_ptr<HoI4::Country>> CountriesWithin1000Miles; // Rename to actual distance
	for (auto country: theWorld->getCountries())
	{
		if (country.second->hasProvinces())
		{
			auto country2 = country.second;
			auto distance = getDistanceBetweenCapitals(CountryThatWantsAllies, country2);
			if (distance && (*distance <= 1000) && (country2 != CountryThatWantsAllies))
			{
				if (!currentAllies.contains(country2->getTag()))
				{
					CountriesWithin1000Miles.push_back(country2);
				}
			}
		}
	}
	string yourIdeology = CountryThatWantsAllies->getGovernmentIdeology();
	// look for all capitals within a distance of Berlin to Tehran
	for (unsigned int i = 0; i < CountriesWithin1000Miles.size(); i++)
	{
		string allyIdeology = CountriesWithin1000Miles[i]->getGovernmentIdeology();
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


optional<double> HoI4WarCreator::getDistanceBetweenCountries(shared_ptr<HoI4::Country> country1,
	 shared_ptr<HoI4::Country> country2)
{
	auto distanceBetweenCountries = getDistanceBetweenCapitals(country1, country2);
	std::pair<int, int> capital2Position = getCapitalPosition(country2);

	for (auto province1: country1->getProvinces())
	{
		auto province1Position = getProvincePosition(province1);
		if (auto newDistance = getDistanceBetweenPoints(province1Position, capital2Position); newDistance < distanceBetweenCountries)
		{
			distanceBetweenCountries = newDistance;
			for (auto province2: country2->getProvinces())
			{
				auto province2Position = getProvincePosition(province2);
				if (auto newestDistance = getDistanceBetweenPoints(province1Position, province2Position); newestDistance < distanceBetweenCountries)
				{
					distanceBetweenCountries = newestDistance;
				}
			}		
		}
	}

	return distanceBetweenCountries;
}


optional<double> HoI4WarCreator::getDistanceBetweenCapitals(shared_ptr<HoI4::Country> country1, shared_ptr<HoI4::Country> country2)
{
	if (!bothCountriesHaveCapitals(country1, country2))
	{
		return {};
	}

	pair<int, int> country1Position = getCapitalPosition(country1);
	pair<int, int> country2Position = getCapitalPosition(country2);

	return getDistanceBetweenPoints(country1Position, country2Position);
}


bool HoI4WarCreator::bothCountriesHaveCapitals(shared_ptr<HoI4::Country> Country1,
	 shared_ptr<HoI4::Country> Country2) const
{
	return (Country1->getCapitalState()) && (Country2->getCapitalState());
}


std::pair<int, int> HoI4WarCreator::getCapitalPosition(std::shared_ptr<HoI4::Country> country)
{
	auto capitalProvince = country->getCapitalProvince();
	if (capitalProvince)
	{
		return getProvincePosition(*capitalProvince);
	}
	else
	{
		return make_pair(65536, 65536);
	}
}


pair<int, int> HoI4WarCreator::getProvincePosition(int provinceNum)
{
	if (provincePositions.size() == 0)
	{
		establishProvincePositions();
	}

	auto itr = provincePositions.find(provinceNum);
	return itr->second;
}


void HoI4WarCreator::establishProvincePositions()
{
	ifstream positionsFile("Configurables/positions.txt");
	if (!positionsFile.is_open())
	{
		throw std::runtime_error("Could not open positions.txt");
	}

	string line;
	while (getline(positionsFile, line))
	{
		processPositionLine(line);
	}

	positionsFile.close();
}


void HoI4WarCreator::processPositionLine(const string& line)
{
	vector<string> tokenizedLine = tokenizeLine(line);
	addProvincePosition(tokenizedLine);
}


void HoI4WarCreator::addProvincePosition(const vector<string>& tokenizedLine)
{
	int province = stoi(tokenizedLine[0]);
	int x = stoi(tokenizedLine[2]);
	int y = stoi(tokenizedLine[4]);

	provincePositions.insert(make_pair(province, make_pair(x, y)));
}


vector<string> HoI4WarCreator::tokenizeLine(const string& line)
{
	vector<string> parts;
	stringstream ss(line);
	string tok;
	while (getline(ss, tok, ';'))
	{
		parts.push_back(tok);
	}

	return parts;
}


double HoI4WarCreator::getDistanceBetweenPoints(pair<int, int> point1, pair<int, int> point2) const
{
	int xDistance = abs(point2.first - point1.first);
	if (xDistance > 2625)
	{
		xDistance = 5250 - xDistance;
	}

	int yDistance = point2.second - point1.second;

	return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
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
			auto distance = getDistanceBetweenCapitals(HomeCountry, country);
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


shared_ptr<HoI4::Faction> HoI4WarCreator::findFaction(shared_ptr<HoI4::Country> CheckingCountry)
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

	vector<shared_ptr<HoI4::Country>> myself;
	myself.push_back(CheckingCountry);
	return make_shared<HoI4::Faction>(CheckingCountry, myself);
}


map<string, shared_ptr<HoI4::Country>> HoI4WarCreator::getNeighbors(shared_ptr<HoI4::Country> checkingCountry,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	map<string, shared_ptr<HoI4::Country>> neighbors =
		 getImmediateNeighbors(checkingCountry, theMapData, provinceDefinitions);
	if (neighbors.size() == 0)
	{
		neighbors = getNearbyCountries(checkingCountry);
	}

	return neighbors;
}


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4WarCreator::getImmediateNeighbors(
	 std::shared_ptr<HoI4::Country> checkingCountry,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> neighbors;

	for (auto province: checkingCountry->getProvinces())
	{
		for (int provinceNumber: theMapData.getNeighbors(province))
		{
			if (!provinceDefinitions.isLandProvince(province))
			{
				continue;
			}

			auto provinceToOwnerItr = provinceToOwnerMap.find(provinceNumber);
			if (provinceToOwnerItr == provinceToOwnerMap.end())
			{
				continue;
			}

			auto ownerTag = provinceToOwnerItr->second;
			if (ownerTag == checkingCountry->getTag())
			{
				continue;
			}

			auto countries = theWorld->getCountries();
			if (auto ownerCountry = countries.find(ownerTag); ownerCountry != countries.end())
			{
				neighbors.insert(make_pair(ownerTag, ownerCountry->second));
			}
		}
	}

	return neighbors;
}


map<string, shared_ptr<HoI4::Country>> HoI4WarCreator::getNearbyCountries(shared_ptr<HoI4::Country> checkingCountry)
{
	map<string, shared_ptr<HoI4::Country>> neighbors;

	for (auto countryItr: theWorld->getCountries())
	{
		auto country = countryItr.second;
		if (country->getCapitalState())
		{
			// IMPROVE
			// need to get further neighbors, as well as countries without capital in an area
			auto distance = getDistanceBetweenCapitals(checkingCountry, country);
			if (distance && (*distance <= 500) && (country->hasProvinces()))
			{
				neighbors.insert(countryItr);
			}
		}
	}

	return neighbors;
}


void HoI4WarCreator::determineProvinceOwners()
{
	for (auto state: theWorld->getStates())
	{
		for (auto province: state.second.getProvinces())
		{
			string owner = state.second.getOwner();
			provinceToOwnerMap.insert(make_pair(province, owner));
		}
	}
}


double HoI4WarCreator::GetFactionStrength(const shared_ptr<HoI4::Faction>& Faction, int years) const
{
	double strength = 0;
	for (auto country: Faction->getMembers())
	{
		strength += country->getStrengthOverTime(years);
	}
	return strength;
}


vector<shared_ptr<HoI4::Faction>> HoI4WarCreator::fascistWarMaker(shared_ptr<HoI4::Country> Leader,
	 ofstream& AILog,
	 const HoI4::World* world,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	vector<shared_ptr<HoI4::Faction>> CountriesAtWar;
	auto name = Leader->getName();
	if (name)
	{
		Log(LogLevel::Info) << "\t\t\tCalculating AI for " + *name;
	}
	else
	{
		Log(LogLevel::Info) << "\t\t\tCalculating AI";
	}
	// too many lists, need to clean up
	vector<shared_ptr<HoI4::Country>> Anschluss;
	vector<shared_ptr<HoI4::Country>> Sudeten;
	vector<shared_ptr<HoI4::Country>> EqualTargets;
	vector<shared_ptr<HoI4::Country>> DifficultTargets;
	// getting country provinces and its neighbors
	auto AllNeighbors = getNeighbors(Leader, theMapData, provinceDefinitions);
	map<string, shared_ptr<HoI4::Country>> CloseNeighbors;
	// gets neighbors that are actually close to you
	for (auto neigh: AllNeighbors)
	{
		if (neigh.second->getCapitalState())
		{
			// IMPROVE
			// need to get further neighbors, as well as countries without capital in an area
			auto distance = getDistanceBetweenCapitals(Leader, neigh.second);
			if (distance && (distance <= 500))
			{
				CloseNeighbors.insert(neigh);
			}
		}
	}

	set<string> Allies = Leader->getAllies();
	// should add method to look for cores you dont own
	// should add method to look for more allies

	// lets look for weak neighbors
	if (name)
	{
		Log(LogLevel::Info) << "\t\t\tDoing Neighbor calcs for " + *name;
	}
	else
	{
		Log(LogLevel::Info) << "\t\t\tDoing Neighbor calcs";
	}
	for (auto neigh: CloseNeighbors)
	{
		// lets check to see if they are not our ally and not a great country
		if (!Allies.contains(neigh.second->getTag()) && !neigh.second->isGreatPower())
		{
			volatile double enemystrength = neigh.second->getStrengthOverTime(1.5);
			volatile double mystrength = Leader->getStrengthOverTime(1.5);
			// lets see their strength is at least < 20%
			if (neigh.second->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5) * 0.2 &&
				 findFaction(neigh.second)->getMembers().size() == 1)
			{
				// they are very weak
				Anschluss.push_back(neigh.second);
			}
			// if not, lets see their strength is at least < 60%
			else if (neigh.second->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5) * 0.6 &&
						neigh.second->getStrengthOverTime(1.5) > Leader->getStrengthOverTime(1.5) * 0.2 &&
						findFaction(neigh.second)->getMembers().size() == 1)
			{
				// they are weak and we can get 1 of these countries in sudeten deal
				Sudeten.push_back(neigh.second);
			}
			// if not, lets see their strength is at least = to ours%
			else if (neigh.second->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5))
			{
				// EqualTargets.push_back(neigh);
				EqualTargets.push_back(neigh.second);
			}
			// if not, lets see their strength is at least < 120%
			else if (neigh.second->getStrengthOverTime(1.5) < Leader->getStrengthOverTime(1.5) * 1.2)
			{
				// StrongerTargets.push_back(neigh);
				DifficultTargets.push_back(neigh.second);
			}
		}
	}
	// string that contains all events
	vector<shared_ptr<HoI4::Country>> nan;

	// look through every anchluss and see its difficulty
	for (auto target: Anschluss)
	{
		string type;
		// outputs are for HowToTakeLand()
		// noactionneeded -  Can take target without any help
		// factionneeded - can take target and faction with attackers faction helping
		// morealliesneeded - can take target with more allies, comes with "newallies" in map
		// coup - cant take over, need to coup
		type = HowToTakeLand(target, Leader, 1.5);
		if (type == "noactionneeded")
		{
			// too many vectors, need to clean up
			nan.push_back(target);
		}
	}
	// gives us generic focus tree start
	auto FocusTree = genericFocusTree->makeCustomizedCopy(*Leader);

	FocusTree->addFascistAnnexationBranch(Leader, nan, theWorld->getEvents(), hoi4Localisations);
	nan.clear();

	for (auto target: Sudeten)
	{
		string type;
		// outputs are
		// noactionneeded -  Can take target without any help
		// factionneeded - can take target and faction with attackers faction helping
		// morealliesneeded - can take target with more allies, comes with "newallies" in map
		// coup - cant take over, need to coup
		type = HowToTakeLand(target, Leader, 2.5);

		if (type == "noactionneeded")
		{
			nan.push_back(target);
		}
	}
	// find neighboring states to take in sudeten deal
	vector<vector<int>> demandedStates;
	for (unsigned int i = 0; i < nan.size(); i++)
	{
		set<int> borderStates = findBorderState(Leader, nan[i], world, theMapData, provinceDefinitions);
		demandedStates.push_back(sortStatesByCapitalDistance(borderStates, Leader, world));
	}
	FocusTree->addFascistSudetenBranch(Leader, nan, demandedStates, *theWorld, hoi4Localisations);
	nan.clear();

	// events for allies
	auto newAllies = GetMorePossibleAllies(Leader);
	if (theConfiguration.getCreateFactions())
	{
		if (newAllies.size() > 0 && Leader->isInFaction())
		{
			vector<shared_ptr<HoI4::Country>> self;
			self.push_back(Leader);
			auto newFaction = make_shared<HoI4::Faction>(Leader, self);
			Leader->setFaction(newFaction);
		}
	}

	vector<shared_ptr<HoI4::Faction>> FactionsAttackingMe;
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
			if (name)
			{
				AILog << "\t" << *name << " is under threat, there are " << FactionsAttackingMe.size()
						<< " faction(s) attacking them, I have a strength of " << GetFactionStrength(findFaction(Leader), 3)
						<< " and they have a strength of " << FactionsAttackingMeStrength << "\n";
			}
			else
			{
				AILog << "\t"
						<< "A country is under threat, there are " << FactionsAttackingMe.size()
						<< " faction(s) attacking them, I have a strength of " << GetFactionStrength(findFaction(Leader), 3)
						<< " and they have a strength of " << FactionsAttackingMeStrength << "\n";
			}
		}
		if (FactionsAttackingMeStrength > GetFactionStrength(findFaction(Leader), 3))
		{
			int maxGCAlliance = 0;

			for (auto GC: theWorld->getGreatPowers())
			{
				auto allyName = GC->getName();

				auto relations = Leader->getRelations(GC->getTag());
				if ((relations) && (relations->getRelations() > 0) && (maxGCAlliance < 1))
				{
					if (theConfiguration.getDebug())
					{
						if (name)
						{
							if (allyName)
							{
								AILog << "\t" << *name << " can attempt to ally " << *allyName << "\n";
							}
							else
							{
								AILog << "\t" << *name << " can attempt to ally a country\n";
							}
						}
						else
						{
							if (allyName)
							{
								AILog << "\t"
										<< "A country can attempt to ally " << *allyName << "\n";
							}
							else
							{
								AILog << "\t"
										<< "A country can attempt to ally a country\n";
							}
						}
					}
					if (theConfiguration.getCreateFactions())
					{
						if (GC->isInFaction())
						{
							vector<shared_ptr<HoI4::Country>> self;
							self.push_back(GC);
							auto newFaction = make_shared<HoI4::Faction>(GC, self);
							GC->setFaction(newFaction);
						}
						theWorld->getEvents().createFactionEvents(*Leader, *GC);
					}
					newAllies.push_back(GC);
					maxGCAlliance++;
				}
			}
		}
	}

	// Declaring war with Great Country
	map<double, shared_ptr<HoI4::Country>> GCDistance;
	vector<shared_ptr<HoI4::Country>> GCDistanceSorted;
	// get great countries with a distance
	for (auto GC: theWorld->getGreatPowers())
	{
		auto distance = getDistanceBetweenCapitals(Leader, GC);
		if (distance)
		{
			GCDistance.insert(make_pair(*distance, GC));
		}
	}
	// put them into a vector so we know their order
	for (auto iterator = GCDistance.begin(); iterator != GCDistance.end(); ++iterator)
	{
		GCDistanceSorted.push_back(iterator->second);
	}

	vector<shared_ptr<HoI4::Country>> GCTargets;
	for (auto GC: GCDistanceSorted)
	{
		string HowToTakeGC = HowToTakeLand(GC, Leader, 3);
		if (HowToTakeGC == "noactionneeded" || HowToTakeGC == "factionneeded" || HowToTakeGC == "morealliesneeded")
		{
			auto relations = Leader->getRelations(GC->getTag());
			if ((GC != Leader) && (relations) && (relations->getRelations() < 0))
			{
				if (GCTargets.size() < maxGCWars)
				{
					GCTargets.push_back(GC);
				}
			}
		}
	}

	FocusTree->addGPWarBranch(Leader, newAllies, GCTargets, "Fascist", theWorld->getEvents(), hoi4Localisations);

	Leader->giveNationalFocus(FocusTree);
	return CountriesAtWar;
}


vector<shared_ptr<HoI4::Faction>> HoI4WarCreator::communistWarCreator(shared_ptr<HoI4::Country> Leader,
	 const std::set<std::string>& majorIdeologies,
	 ofstream& AILog,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations)
{
	vector<shared_ptr<HoI4::Faction>> CountriesAtWar;
	// communism still needs great country war events
	auto name = Leader->getName();
	if (name)
	{
		Log(LogLevel::Info) << "\t\t\tCalculating AI for " + *name;
		Log(LogLevel::Info) << "\t\t\tCalculating Neighbors for " + *name;
	}
	else
	{
		Log(LogLevel::Info) << "\t\t\tCalculating AI for a country";
		Log(LogLevel::Info) << "\t\t\tCalculating Neighbors for a country";
	}
	auto AllNeighbors = getNeighbors(Leader, theMapData, provinceDefinitions);
	map<string, shared_ptr<HoI4::Country>> Neighbors;
	for (auto neigh: AllNeighbors)
	{
		if (neigh.second->getCapitalState())
		{
			// IMPROVE
			// need to get further neighbors, as well as countries without capital in an area
			auto distance = getDistanceBetweenCapitals(Leader, neigh.second);
			if (distance && (distance <= 400))
			{
				Neighbors.insert(neigh);
			}
		}
	}
	set<string> Allies = Leader->getAllies();
	vector<shared_ptr<HoI4::Country>> coups;
	vector<shared_ptr<HoI4::Country>> forcedtakeover;

	// if (Permanant Revolution)
	// Decide between Anti - Democratic Focus, Anti - Monarch Focus, or Anti - Fascist Focus(Look at all great powers and
	// get average relation between each ideology, the one with the lowest average relation leads to that focus). Attempt
	// to ally with other Communist Countries(with Permanant Revolution)
	if (name)
	{
		Log(LogLevel::Info) << "\t\t\tDoing Neighbor calcs for " + *name;
	}
	else
	{
		Log(LogLevel::Info) << "\t\t\tDoing Neighbor calcs for a country";
	}
	for (auto neigh: Neighbors)
	{
		// lets check to see if they are our ally and not a great country
		if (!Allies.contains(neigh.second->getTag()) && !neigh.second->isGreatPower())
		{
			double com = 0;
			auto neighFaction = findFaction(neigh.second);
			for (auto party: neigh.second->getIdeologySupport())
			{
				if ((party.first == "socialist") || (party.first == "communist") || (party.first == "anarcho_liberal"))
					com += party.second;
			}
			if (const auto& rulingParty = neigh.second->getRulingParty();
				 com > 25 && rulingParty->getIdeology() != "communist" &&
				 HowToTakeLand(neigh.second, Leader, 2.5) == "coup")
			{
				// look for neighboring countries to spread communism too(Need 25 % or more Communism support), Prioritizing
				// those with "Communism Allowed" Flags, prioritizing those who are weakest 	Method() Influence Ideology
				// and
				// Attempt Coup
				coups.push_back(neigh.second);
			}
			else if (neighFaction->getMembers().size() == 1 && rulingParty->getIdeology() != "communist")
			{
				//	Then look for neighboring countries to spread communism by force, prioritizing weakest first
				forcedtakeover.push_back(neigh.second);
				//	Depending on Anti - Ideology Focus, look for allies in alternate ideologies to get to ally with to
				// declare war against Anti - Ideology Country.
			}
		}
	}
	// if (Socialism in One State)
	//	Events / Focuses to increase Industrialization and defense of the country, becomes Isolationist
	//	Eventually gets events to drop Socialism in One state and switch to permanant revolution(Maybe ? )

	map<string, vector<shared_ptr<HoI4::Country>>> TargetMap;
	vector<shared_ptr<HoI4::Country>> nan;
	vector<shared_ptr<HoI4::Country>> fn;
	vector<shared_ptr<HoI4::Country>> man;
	vector<shared_ptr<HoI4::Country>> coup;
	for (auto target: forcedtakeover)
	{
		string type;
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
	TargetMap.insert(make_pair("noactionneeded", nan));
	TargetMap.insert(make_pair("factionneeded", fn));
	TargetMap.insert(make_pair("morealliesneeded", man));
	TargetMap.insert(make_pair("coup", coup));

	vector<shared_ptr<HoI4::Country>> TargetsByTech;
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
	map<double, shared_ptr<HoI4::Country>> GCDistance;
	vector<shared_ptr<HoI4::Country>> GCDistanceSorted;
	for (auto GC: theWorld->getGreatPowers())
	{
		auto distance = getDistanceBetweenCapitals(Leader, GC);
		if (distance && (distance < 1200))
		{
			GCDistance.insert(make_pair(*distance, GC));
		}
	}
	// put them into a vector so we know their order
	for (auto iterator = GCDistance.begin(); iterator != GCDistance.end(); ++iterator)
	{
		GCDistanceSorted.push_back(iterator->second);
	}
	sort(GCDistanceSorted.begin(), GCDistanceSorted.end());
	vector<shared_ptr<HoI4::Country>> GCTargets;
	for (auto GC: GCDistanceSorted)
	{
		string HowToTakeGC = HowToTakeLand(GC, Leader, 3);
		if (HowToTakeGC == "noactionneeded" || HowToTakeGC == "factionneeded")
		{
			if (GC != Leader)
				GCTargets.push_back(GC);
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
	FocusTree->addCommunistCoupBranch(Leader, forcedtakeover, majorIdeologies, hoi4Localisations);
	FocusTree->addCommunistWarBranch(Leader, TargetsByTech, theWorld->getEvents(), hoi4Localisations);
	FocusTree->addGPWarBranch(Leader, newAllies, finalTargets, "Communist", theWorld->getEvents(), hoi4Localisations);
	Leader->giveNationalFocus(FocusTree);

	return CountriesAtWar;
}


vector<shared_ptr<HoI4::Faction>> HoI4WarCreator::democracyWarCreator(shared_ptr<HoI4::Country> Leader,
	 HoI4::Localisation& hoi4Localisations)
{
	vector<shared_ptr<HoI4::Faction>> CountriesAtWar;
	map<int, shared_ptr<HoI4::Country>> CountriesToContain;
	vector<shared_ptr<HoI4::Country>> vCountriesToContain;
	set<string> Allies = Leader->getAllies();
	auto FocusTree = genericFocusTree->makeCustomizedCopy(*Leader);
	for (auto GC: theWorld->getGreatPowers())
	{
		auto relations = Leader->getRelations(GC->getTag());
		if (relations)
		{
			double relationVal = relations->getRelations();
			if (relationVal < 100 && GC->getGovernmentIdeology() != "democratic" && !Allies.contains(GC->getTag()))
			{
				CountriesAtWar.push_back(findFaction(Leader));
				CountriesToContain.insert(make_pair(static_cast<int>(relationVal), GC));
			}
		}
	}
	for (auto country: CountriesToContain)
	{
		vCountriesToContain.push_back(country.second);
	}
	if (vCountriesToContain.size() > 0)
	{
		FocusTree->addDemocracyNationalFocuses(Leader, vCountriesToContain, hoi4Localisations);
	}

	Leader->giveNationalFocus(FocusTree);

	return CountriesAtWar;
}


vector<shared_ptr<HoI4::Faction>> HoI4WarCreator::absolutistWarCreator(shared_ptr<HoI4::Country> country,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations)
{
	auto focusTree = genericFocusTree->makeCustomizedCopy(*country);

	auto name = country->getName();
	if (name)
	{
		Log(LogLevel::Info) << "\t\t\tDoing neighbor calcs for " + *name;
	}
	else
	{
		Log(LogLevel::Info) << "\t\t\tDoing neighbor calcs for a country";
	}

	auto weakNeighbors = findWeakNeighbors(country, theMapData, provinceDefinitions);
	auto weakColonies = findWeakColonies(country, theMapData, provinceDefinitions);
	focusTree->addAbsolutistEmpireNationalFocuses(country, weakColonies, weakNeighbors, hoi4Localisations);

	auto greatPowerTargets = getGreatPowerTargets(country);
	auto CountriesAtWar = addGreatPowerWars(country, *focusTree, greatPowerTargets, hoi4Localisations);
	addTradeEvents(country, greatPowerTargets);

	country->giveNationalFocus(focusTree);

	return CountriesAtWar;
}


void HoI4WarCreator::generateReconquestWars(std::ofstream& AILog,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	if (theConfiguration.getDebug())
	{
		AILog << "Creating Reconquest wars\n";
	}

	for (const auto& [unused, country]: theWorld->getCountries())
	{
		if (country->getNationalFocus())
		{
			continue;
		}
		int numWarsWithNeighbors = 0;
		auto focusTree = genericFocusTree->makeCustomizedCopy(*country);
		const auto& coreHolders = focusTree->addReconquestBranch(country, numWarsWithNeighbors, theWorld->getMajorIdeologies(), theWorld->getStates(), hoi4Localisations);
		if (!coreHolders.empty())
		{
			country->giveNationalFocus(focusTree);
		}
	}
}


std::vector<std::shared_ptr<HoI4::Faction>> HoI4WarCreator::neighborWarCreator(std::shared_ptr<HoI4::Country> country,
	 std::ofstream& AILog,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations,
	 const Configuration& theConfiguration)
{
	if (theConfiguration.getDebug())
	{
		auto name = country->getName();
		if (name)
		{
			AILog << "Look for neighbors to attack for " + *name << "\n";
		}
		else
		{
			AILog << "Look for neighbors to attack for a country\n";
		}
	}

	std::vector<std::shared_ptr<HoI4::Faction>> countriesAtWar;

	auto closeNeighbors = getImmediateNeighbors(country, theMapData, provinceDefinitions);
	for (const auto& nonImmediateNeighbor: findCountriesWithin(100, country, theMapData))
	{
		if (closeNeighbors.find(nonImmediateNeighbor.first) == closeNeighbors.end())
		{
			closeNeighbors.insert(nonImmediateNeighbor);
		}
	}
	if (closeNeighbors.empty())
	{
		return countriesAtWar;
	}

	int numWarsWithNeighbors = 0;
	auto focusTree = genericFocusTree->makeCustomizedCopy(*country);

	const auto& coreHolders = focusTree->addReconquestBranch(country, numWarsWithNeighbors, theWorld->getMajorIdeologies(), theWorld->getStates(), hoi4Localisations);
	const auto& conquerTags = focusTree->addConquerBranch(country, numWarsWithNeighbors, theWorld->getMajorIdeologies(), coreHolders, hoi4Localisations);

	for (const auto& target: closeNeighbors)
	{
		if (numWarsWithNeighbors >= 5)
		{
			break;
		}
		if (coreHolders.contains(target.first) || conquerTags.contains(target.first))
		{
			continue;
		}


		auto relations = country->getRelations(target.second->getTag());
		if (!relations || (relations->getRelations() > 0) || (country == target.second))
		{
			continue;
		}

		if (auto allies = country->getAllies(); !allies.contains(target.second->getTag()))
		{
			std::string targetName;
			if (auto possibleTargetName = target.second->getName(); possibleTargetName)
			{
				targetName = *possibleTargetName;
			}
			else
			{
				Log(LogLevel::Warning) << "Could not set target name in neighbor war creator";
			}

			countriesAtWar.push_back(findFaction(country));
			if (theConfiguration.getDebug())
			{
				AILog << "Creating focus to attack " + targetName << "\n";
			}

			date startDate = date("1936.01.01");
			startDate.increaseByMonths((200 + relations->getRelations()) / 8);
			focusTree->addNeighborWarBranch(country->getTag(),
				 closeNeighbors,
				 target.second,
				 targetName,
				 startDate,
				 theWorld->getMajorIdeologies(),
				 hoi4Localisations);

			numWarsWithNeighbors++;
		}
	}

	if (numWarsWithNeighbors > 0)
	{
		country->giveNationalFocus(focusTree);
	}

	return countriesAtWar;
}


vector<shared_ptr<HoI4::Faction>> HoI4WarCreator::radicalWarCreator(shared_ptr<HoI4::Country> country,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions,
	 HoI4::Localisation& hoi4Localisations)
{
	return absolutistWarCreator(country, theMapData, provinceDefinitions, hoi4Localisations);
}

set<int> HoI4WarCreator::findBorderState(shared_ptr<HoI4::Country> country,
	 shared_ptr<HoI4::Country> neighbor,
	 const HoI4::World* world,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	set<int> demandedStates;
	std::map<int, int> provinceToStateIdMapping = world->getProvinceToStateIDMap();
	for (auto leaderprov: country->getProvinces())
	{
		for (int prov: theMapData.getNeighbors(leaderprov))
		{
			if (!provinceDefinitions.isLandProvince(prov))
			{
				continue;
			}

			if (provinceToOwnerMap.contains(prov))
			{
				string owner = provinceToOwnerMap.find(prov)->second;
				if (owner == neighbor->getTag())
				{
					demandedStates.insert(provinceToStateIdMapping[prov]);
				}
			}
		}
	}
	return demandedStates;
}

std::vector<int> HoI4WarCreator::sortStatesByCapitalDistance(const std::set<int>& stateList,
	 std::shared_ptr<HoI4::Country> country,
	 const HoI4::World* world)
{
	std::multimap<double, int> statesWithDistance;
	std::pair<int, int> capitalCoords = getCapitalPosition(country);
	std::map<int, HoI4::State> statesMapping = world->getStates();

	for (int stateID: stateList)
	{
		if (auto state = statesMapping.find(stateID); state != statesMapping.end())
		{
			std::optional<int> provCapID = state->second.getVPLocation();
			std::pair<int, int> stateVPCoords;
			if (provCapID)
			{
				stateVPCoords = getProvincePosition(*provCapID);
			}
			else
			{
				stateVPCoords = std::make_pair(65536, 65536);
			}
			double distanceSquared =
				 pow(capitalCoords.first - stateVPCoords.first, 2) + pow(capitalCoords.second - stateVPCoords.second, 2);
			statesWithDistance.insert(std::pair<double, int>(distanceSquared, stateID));
		}
	}

	std::vector<int> sortedStates;
	for (std::pair<double, int> oneStateDistance: statesWithDistance)
	{
		sortedStates.push_back(oneStateDistance.second);
	}
	return sortedStates;
}


vector<shared_ptr<HoI4::Country>> HoI4WarCreator::findWeakNeighbors(shared_ptr<HoI4::Country> country,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	vector<shared_ptr<HoI4::Country>> weakNeighbors;

	auto allies = country->getAllies();
	for (auto neighbor: findCloseNeighbors(country, theMapData, provinceDefinitions))
	{
		if (allies.contains(neighbor.second->getTag()))
		{
			continue;
		}
		if (neighbor.second->isGreatPower())
		{
			continue;
		}

		double enemystrength = neighbor.second->getStrengthOverTime(1.5);
		double mystrength = country->getStrengthOverTime(1.5);
		if ((enemystrength < (mystrength * 0.5)) && (findFaction(neighbor.second)->getMembers().size() == 1))
		{
			weakNeighbors.push_back(neighbor.second);
		}
	}

	return weakNeighbors;
}


map<string, shared_ptr<HoI4::Country>> HoI4WarCreator::findCloseNeighbors(shared_ptr<HoI4::Country> country,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	map<string, shared_ptr<HoI4::Country>> closeNeighbors;

	for (auto neighbor: getNeighbors(country, theMapData, provinceDefinitions))
	{
		if ((neighbor.second->getCapitalState()) && (neighbor.first != ""))
		{
			auto distance = getDistanceBetweenCapitals(country, neighbor.second);
			if (distance && (*distance <= 500))
			{
				closeNeighbors.insert(neighbor);
			}
		}
	}

	return closeNeighbors;
}


std::map<string, shared_ptr<HoI4::Country>> HoI4WarCreator::findCountriesWithin(int distancePx, shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData)
{
	map<string, shared_ptr<HoI4::Country>> closeNeighbors;

	for (const auto& neighbor: theWorld->getCountries())
	{
		if ((neighbor.second->getCapitalState()) && (!neighbor.first.empty()) && (neighbor.second->hasProvinces()))
		{
			const auto& distance = getDistanceBetweenCountries(country, neighbor.second);
			if (distance && (*distance <= distancePx))
			{
				closeNeighbors.insert(neighbor);
			}
		}
	}

	return closeNeighbors;
}


vector<shared_ptr<HoI4::Country>> HoI4WarCreator::findWeakColonies(shared_ptr<HoI4::Country> country,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	vector<shared_ptr<HoI4::Country>> weakColonies;

	auto allies = country->getAllies();
	for (auto neighbor: findFarNeighbors(country, theMapData, provinceDefinitions))
	{
		if (allies.contains(neighbor.second->getTag()))
		{
			continue;
		}
		if (neighbor.second->isGreatPower())
		{
			continue;
		}

		double enemystrength = neighbor.second->getStrengthOverTime(1.5);
		double mystrength = country->getStrengthOverTime(1.5);
		if ((enemystrength < mystrength * 0.5) && (findFaction(neighbor.second)->getMembers().size() == 1))
		{
			weakColonies.push_back(neighbor.second);
		}
	}

	return weakColonies;
}


map<string, shared_ptr<HoI4::Country>> HoI4WarCreator::findFarNeighbors(shared_ptr<HoI4::Country> country,
	 const HoI4::MapData& theMapData,
	 const HoI4::ProvinceDefinitions& provinceDefinitions)
{
	map<string, shared_ptr<HoI4::Country>> farNeighbors;

	for (auto neighbor: getNeighbors(country, theMapData, provinceDefinitions))
	{
		if (neighbor.second->getCapitalState())
		{
			auto distance = getDistanceBetweenCapitals(country, neighbor.second);
			if (distance && (*distance > 500))
			{
				farNeighbors.insert(neighbor);
			}
		}
	}

	if (farNeighbors.size() == 0) // find all nearby countries
	{
		for (auto otherCountry: theWorld->getCountries())
		{
			if (otherCountry.second->getCapitalState())
			{
				auto distance = getDistanceBetweenCapitals(country, otherCountry.second);
				if (distance && (*distance <= 1000) && (otherCountry.second->hasProvinces()))
				{
					farNeighbors.insert(otherCountry);
				}
			}
		}
	}

	return farNeighbors;
}


vector<shared_ptr<HoI4::Country>> HoI4WarCreator::getGreatPowerTargets(shared_ptr<HoI4::Country> country)
{
	vector<shared_ptr<HoI4::Country>> greatPowerTargets;

	for (auto greatPower: getGPsByDistance(country))
	{
		string prereqsNeeded = HowToTakeLand(greatPower.second, country, 3);
		if (prereqsNeeded == "noactionneeded" || prereqsNeeded == "factionneeded")
		{
			if (greatPower.second != country)
			{
				greatPowerTargets.push_back(greatPower.second);
			}
		}
		if (prereqsNeeded == "morealliesneeded")
		{
		}
	}

	return greatPowerTargets;
}


map<double, shared_ptr<HoI4::Country>> HoI4WarCreator::getGPsByDistance(shared_ptr<HoI4::Country> country)
{
	map<double, shared_ptr<HoI4::Country>> distanceToGPMap;
	for (auto greatPower: theWorld->getGreatPowers())
	{
		auto distance = getDistanceBetweenCapitals(country, greatPower);
		if (distance && (*distance < 1200))
		{
			distanceToGPMap.insert(make_pair(*distance, greatPower));
		}
	}

	return distanceToGPMap;
}


vector<shared_ptr<HoI4::Faction>> HoI4WarCreator::addGreatPowerWars(shared_ptr<HoI4::Country> country,
	 HoI4FocusTree& FocusTree,
	 vector<shared_ptr<HoI4::Country>>& greatPowerTargets,
	 HoI4::Localisation& hoi4Localisations)
{
	vector<shared_ptr<HoI4::Faction>> countriesAtWar;

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

		set<string> Allies = country->getAllies();
		if (!Allies.contains(target->getTag()))
		{
			auto possibleTargetName = target->getName();
			string targetName;
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

			shared_ptr<HoI4Focus> newFocus = make_shared<HoI4Focus>();
			newFocus->id = "War_with" + target->getTag() + country->getTag();
			newFocus->icon = "GFX_goal_generic_major_war";
			newFocus->text = "War_with" + target->getTag();
			newFocus->available = "= {\n";
			newFocus->available += "			has_war = no\n";
			newFocus->available += "			date > 1939.1.1\n";
			newFocus->available += "		}";
			newFocus->xPos = 31 + numWarsWithGreatPowers * 2;
			newFocus->yPos = 5;
			newFocus->cost = 10;
			newFocus->aiWillDo = "= {\n";
			newFocus->aiWillDo += "			factor = " + to_string(10 - numWarsWithGreatPowers * 5) + "\n";
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


void HoI4WarCreator::addTradeEvents(shared_ptr<HoI4::Country> country,
	 const vector<shared_ptr<HoI4::Country>>& greatPowerTargets)
{
	for (auto greatPowerTarget: greatPowerTargets)
	{
		auto relations = country->getRelations(greatPowerTarget->getTag());
		if ((!relations) || (relations->getRelations() >= 0))
		{
			continue;
		}

		theWorld->getEvents().createTradeEvent(*country, *greatPowerTarget);
	}
}