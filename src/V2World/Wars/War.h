#ifndef WAR_H
#define WAR_H



#include <optional>
#include <set>
#include <string>



namespace Vic2
{

struct WarOptions
{
	std::string originalAttacker;
	std::set<std::string> attackers;
	std::string originalDefender;
	std::set<std::string> defenders;
	std::string casusBelli;
	std::optional<int> province;
};


class War
{
  public:
	class Factory;
	War(const WarOptions& options):
		 originalAttacker(options.originalAttacker), attackers(options.attackers),
		 originalDefender(options.originalDefender), defenders(options.defenders), casusBelli(options.casusBelli),
		 province(options.province)
	{
	}

	[[nodiscard]] const auto& getOriginalAttacker() const { return originalAttacker; }
	[[nodiscard]] const auto& getAttackers() const { return attackers; }
	[[nodiscard]] const auto& getOriginalDefender() const { return originalDefender; }
	[[nodiscard]] const auto& getDefenders() const { return defenders; }
	[[nodiscard]] const auto& getCasusBelli() const { return casusBelli; }
	[[nodiscard]] const auto& getProvince() const { return province; }

  private:
	std::string originalAttacker;
	std::set<std::string> attackers;
	std::string originalDefender;
	std::set<std::string> defenders;
	std::string casusBelli;
	std::optional<int> province;
};


} // namespace Vic2



#endif // WAR_H