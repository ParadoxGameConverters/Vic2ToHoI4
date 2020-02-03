#ifndef HOI4_FACTION_H
#define HOI4_FACTION_H



#include <memory>
#include <vector>
using namespace std;



namespace HoI4
{
class Country;
}



class HoI4Faction
{

	public:
		HoI4Faction(shared_ptr<HoI4::Country> leader, const vector<shared_ptr<HoI4::Country>>& members): Factionleader(leader), Factionmembers(members) {}

		shared_ptr<HoI4::Country> getLeader() const { return Factionleader; }
		vector<shared_ptr<HoI4::Country>> getMembers() const { return Factionmembers; }
		void addMember(shared_ptr<HoI4::Country> addedCon) { Factionmembers.push_back(addedCon); }

	private:
		shared_ptr<HoI4::Country> Factionleader;
		vector<shared_ptr<HoI4::Country>> Factionmembers;

};



#endif // HOI4_FACTION_H