#ifndef WAR_BUILDER_H
#define WAR_BUILDER_H



#include "War.h"
#include <memory>



namespace Vic2
{

class War::Builder
{
  public:
	Builder() { theWar = std::make_unique<War>(); }
	std::unique_ptr<War> build() { return std::move(theWar); }

	Builder& setOriginalAttacker(std::string originalAttacker)
	{
		theWar->originalAttacker = std::move(originalAttacker);
		return *this;
	}

	Builder& setAttackers(std::set<std::string> attackers)
	{
		theWar->attackers = std::move(attackers);
		return *this;
	}

	Builder& setOriginalDefender(std::string originalDefender)
	{
		theWar->originalDefender = std::move(originalDefender);
		return *this;
	}

	Builder& setDefenders(std::set<std::string> defenders)
	{
		theWar->defenders = std::move(defenders);
		return *this;
	}

	Builder& setCB(std::string CB)
	{
		theWar->CB = std::move(CB);
		return *this;
	}

  private:
	std::unique_ptr<War> theWar;
};

} // namespace Vic2



#endif // WAR_BUILDER_H