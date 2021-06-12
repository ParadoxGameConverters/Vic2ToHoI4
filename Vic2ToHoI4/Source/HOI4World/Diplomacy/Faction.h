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
			std::vector<std::shared_ptr<Country>> members, 
			std::optional<std::string> name = ""
		): factionLeader(std::move(leader)), factionMembers(std::move(members)), factionName(name) {}

		[[nodiscard]] std::shared_ptr<Country> getLeader() const { return factionLeader; }
		[[nodiscard]] std::vector<std::shared_ptr<Country>> getMembers() const { return factionMembers; }
		[[nodiscard]] std::optional<std::string> getFactionName() const { return factionName; }

		void addMember(const std::shared_ptr<Country>& member) { factionMembers.push_back(member); }

	private:
		std::shared_ptr<Country> factionLeader;
		std::vector<std::shared_ptr<Country>> factionMembers;
		std::optional<std::string> factionName;

};

}



#endif // FACTION_H