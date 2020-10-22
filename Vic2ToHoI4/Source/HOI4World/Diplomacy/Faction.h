#ifndef FACTION_H
#define FACTION_H



#include <memory>
#include <vector>



namespace HoI4
{

class Country; // forward include to break circular dependency with Country


class Faction
{

	public:
		Faction(
			std::shared_ptr<Country> leader,
			std::vector<std::shared_ptr<Country>> members
		): factionLeader(std::move(leader)), factionMembers(std::move(members)) {}

		[[nodiscard]] std::shared_ptr<Country> getLeader() const { return factionLeader; }
		[[nodiscard]] std::vector<std::shared_ptr<Country>> getMembers() const { return factionMembers; }

		void addMember(const std::shared_ptr<Country>& member) { factionMembers.push_back(member); }

	private:
		std::shared_ptr<Country> factionLeader;
		std::vector<std::shared_ptr<Country>> factionMembers;

};

}



#endif // FACTION_H