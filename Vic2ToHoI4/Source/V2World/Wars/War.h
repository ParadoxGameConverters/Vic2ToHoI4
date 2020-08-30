#ifndef WAR_H
#define WAR_H



#include <set>
#include <string>



namespace Vic2
{


class War
{
  public:
	class Factory;
	class Builder;
	War() = default;

	[[nodiscard]] std::string getOriginalAttacker() const { return originalAttacker; }
	[[nodiscard]] std::set<std::string> getAttackers() const { return attackers; }
	[[nodiscard]] std::string getOriginalDefender() const { return originalDefender; }
	[[nodiscard]] std::set<std::string> getDefenders() const { return defenders; }
	[[nodiscard]] std::string getCB() const { return CB; }

  private:
	std::string originalAttacker;
	std::set<std::string> attackers;
	std::string originalDefender;
	std::set<std::string> defenders;
	std::string CB;
};


} // namespace Vic2



#endif // WAR_H