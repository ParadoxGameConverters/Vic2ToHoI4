/*Copyright (c) 2017 The Paradox Game Converters Project

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



#include <fstream>
#include <optional>
#include <map>
#include <string>
#include "HoI4Country.h"
using namespace std;



namespace HoI4
{

class MapData;
class World;

}


namespace Vic2
{

class World;

}


const int maxGCWars = 1;



class HoI4WarCreator
{
	public:
		explicit HoI4WarCreator(const HoI4::World* world, const HoI4::MapData& theMapData);

	private:
		HoI4WarCreator(const HoI4WarCreator&) = delete;
		HoI4WarCreator& operator=(const HoI4WarCreator&) = delete;

		void determineProvinceOwners();
		void addAllTargetsToWorldTargetMap();
		void addTargetsToWorldTargetMap(shared_ptr<HoI4::Country> country);
		map<double, shared_ptr<HoI4::Country>> getDistancesToGreatPowers(shared_ptr<HoI4::Country> country);
		double calculateWorldStrength(ofstream& AILog) const;
		void generateMajorWars(ofstream& AILog, set<shared_ptr<HoI4Faction>>& factionsAtWar, const std::set<std::string>& majorIdeologies, const HoI4::World* world, const HoI4::MapData& theMapData);
		double calculatePercentOfWorldAtWar(ofstream& AILog, const set<shared_ptr<HoI4Faction>>& factionsAtWar, double worldStrength) const;
		void generateAdditionalWars(ofstream& AILog, set<shared_ptr<HoI4Faction>>& factionsAtWar, double worldStrength, const HoI4::MapData& theMapData);
		bool isImportantCountry(shared_ptr<HoI4::Country> country);

		vector<shared_ptr<HoI4Faction>> fascistWarMaker(shared_ptr<HoI4::Country> country, ofstream& AILog, const HoI4::World *world, const HoI4::MapData& theMapData);
		vector<shared_ptr<HoI4Faction>> communistWarCreator(shared_ptr<HoI4::Country> country, const std::set<std::string>& majorIdeologies, ofstream& AILog, const HoI4::MapData& theMapData);
		vector<shared_ptr<HoI4Faction>> democracyWarCreator(shared_ptr<HoI4::Country> country);
		vector<shared_ptr<HoI4Faction>> absolutistWarCreator(shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);
		vector<shared_ptr<HoI4Faction>> neighborWarCreator(shared_ptr<HoI4::Country> country, ofstream& AILog, const HoI4::MapData& theMapData);
		vector<shared_ptr<HoI4Faction>> radicalWarCreator(shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);

		vector<shared_ptr<HoI4::Country>> findEvilCountries() const;

		set<int> findBorderState(shared_ptr<HoI4::Country> country, shared_ptr<HoI4::Country> neighbor, const HoI4::World* world, const HoI4::MapData& theMapData);
		vector<int> sortStatesByCapitalDistance(set<int> stateList, shared_ptr<HoI4::Country> country, const HoI4::World* world);
		vector<shared_ptr<HoI4::Country>> findWeakNeighbors(shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);
		map<string, shared_ptr<HoI4::Country>> findCloseNeighbors(shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);
		vector<shared_ptr<HoI4::Country>> findWeakColonies(shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);
		map<string, shared_ptr<HoI4::Country>> findFarNeighbors(shared_ptr<HoI4::Country> country, const HoI4::MapData& theMapData);
		vector<shared_ptr<HoI4::Country>> getGreatPowerTargets(shared_ptr<HoI4::Country> country);
		map<double, shared_ptr<HoI4::Country>> getGPsByDistance(shared_ptr<HoI4::Country> country);
		vector<shared_ptr<HoI4Faction>> addGreatPowerWars(shared_ptr<HoI4::Country> country, HoI4FocusTree& FocusTree, vector<shared_ptr<HoI4::Country>>& greatPowerTargets);
		void addTradeEvents(shared_ptr<HoI4::Country> country, const vector<shared_ptr<HoI4::Country>>& greatPowerTargets);

		void    setSphereLeaders(const Vic2::World* sourceWorld);
		double    GetFactionStrength(const shared_ptr<HoI4Faction> Faction, int years) const;
		string HowToTakeLand(shared_ptr<HoI4::Country> TargetCountry, shared_ptr<HoI4::Country> AttackingCountry, double time);
		vector<shared_ptr<HoI4::Country>> GetMorePossibleAllies(shared_ptr<HoI4::Country> CountryThatWantsAllies);
		optional<double> getDistanceBetweenCountries(shared_ptr<HoI4::Country> Country1, shared_ptr<HoI4::Country> Country2);
		bool bothCountriesHaveCapitals(shared_ptr<HoI4::Country> Country1, shared_ptr<HoI4::Country> Country2) const;
		pair<int, int> getCapitalPosition(shared_ptr<HoI4::Country> country);
		pair<int, int> getProvincePosition(int provinceNum);
		void establishProvincePositions();
		void processPositionLine(const string& line);
		vector<string> tokenizeLine(const string& line);
		void addProvincePosition(const vector<string>& tokenizedLine);
		double getDistanceBetweenPoints(pair<int, int> point1, pair<int, int> point2) const;
		double GetFactionStrengthWithDistance(shared_ptr<HoI4::Country> HomeCountry, vector<shared_ptr<HoI4::Country>> Faction, double time);
		shared_ptr<HoI4Faction> findFaction(shared_ptr<HoI4::Country> checkingCountry);

		map<string, shared_ptr<HoI4::Country>> getNeighbors(shared_ptr<HoI4::Country> checkingCountry, const HoI4::MapData& theMapData);
		map<string, shared_ptr<HoI4::Country>> getImmediateNeighbors(shared_ptr<HoI4::Country> checkingCountry, const HoI4::MapData& theMapData);
		map<string, shared_ptr<HoI4::Country>> getNearbyCountries(shared_ptr<HoI4::Country> checkingCountry);


		HoI4FocusTree* genericFocusTree;
		const HoI4::World* theWorld;

		vector<HoI4::Country*> AggressorFactions;
		map<shared_ptr<HoI4::Country>, vector<shared_ptr<HoI4::Country>>> WorldTargetMap;
		map<int, pair<int, int>> provincePositions;

		map<int, string> provinceToOwnerMap;
};