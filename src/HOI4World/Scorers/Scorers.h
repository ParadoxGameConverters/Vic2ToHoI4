#ifndef SCORERS_H
#define SCORERS_H



#include "src/HOI4World/Scorers/Scorer.h"
#include <set>
#include <vector>



namespace HoI4
{

class Scorers
{
  public:
	class Factory;
	[[nodiscard]] const auto& getScorers() const { return scorers; }
	[[nodiscard]] const auto& getCustomizedScorers() const { return customizedScorers; }

	void giveScorer(Scorer&& scorer) { scorers.emplace_back(scorer); }

	void updateScorers(const std::set<std::string>& majorIdeologies);

  private:
	std::vector<Scorer> scorers;
	std::map<std::string, Scorer> customizedScorers;
};

} // namespace HoI4



#endif // SCORERS_H