#include "src/HOI4World/Scorers/Scorer.h"

std::shared_ptr<HoI4::Scorer> HoI4::Scorer::makeCustomizedCopy(const std::string& ideology) const
{
	constexpr std::string ideologyToken = "$IDEOLOGY";
	const std::map<std::string, std::string> ideologyNameMap = {{"fascism", "fascist"},
		 {"communism", "communist"},
		 {"democratic", "democratic"},
		 {"neutrality", "non_aligned"},
		 {"absolutist", "absolutist"},
		 {"radical", "radical"}};


	auto newScorer = std::make_shared<Scorer>(*this);

	if (const auto& ideologyNameItr = newScorer->name.find(ideologyToken); ideologyNameItr != std::string::npos)
	{
		newScorer->name.replace(ideologyNameItr, ideologyToken.size(), ideologyNameMap.at(ideology));
	}
	if (const auto& ideologyTargetItr = newScorer->targets.find(ideologyToken); ideologyTargetItr != std::string::npos)
	{
		newScorer->targets.replace(ideologyTargetItr, ideologyToken.size(), ideology);
	}
	return newScorer;
}