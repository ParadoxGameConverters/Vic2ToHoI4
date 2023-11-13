#include "src/HOI4World/Scorers/Scorers.h"
#include <algorithm>



void HoI4::Scorers::updateScorers(const std::set<std::string>& majorIdeologies)
{
	for (const auto& scorer: scorers)
	{
		for (const auto& ideology: majorIdeologies)
		{
			const auto& newScorer = scorer.makeCustomizedCopy(ideology);
			customizedScorers[newScorer->getName()] = *newScorer;
		}
	}
}