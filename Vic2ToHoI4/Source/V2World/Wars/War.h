#ifndef WAR_H_
#define WAR_H_



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

	std::string getOriginalAttacker() const { return originalAttacker; }
	std::set<std::string> getAttackers() const { return attackers; }
	std::string getOriginalDefender() const { return originalDefender; }
	std::set<std::string> getDefenders() const { return defenders; }
	std::string getCB() const { return CB; }

  private:
	std::string originalAttacker;
	std::set<std::string> attackers;
	std::string originalDefender;
	std::set<std::string> defenders;
	std::string CB;
};


} // namespace Vic2



#endif // WAR_H_