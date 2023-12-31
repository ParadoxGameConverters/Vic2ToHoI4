#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Scorers/ScorersFactory.h"



TEST(HoI4World_Scorers_ScorersFactoryTests, ScorersCanBeImported)
{
	const auto scorers = HoI4::Scorers::Factory().getScorers();

	ASSERT_EQ(2, scorers->getScorers().size());
	ASSERT_EQ("scorer_one", scorers->getScorers()[0].getName());
	ASSERT_EQ("scorer_two", scorers->getScorers()[1].getName());
}