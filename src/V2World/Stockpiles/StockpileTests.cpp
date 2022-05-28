#include "V2World/Stockpiles/StockpileFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Vic2World_Stockpiles_StockpileTests, StockpilesDefaultToEmpty)
{
	std::stringstream input;

	const auto stockpile = Vic2::StockpileFactory().importStockpile(input);

	ASSERT_TRUE(stockpile.empty());
}


TEST(Vic2World_Stockpiles_StockpileTests, StockpilesCanBeImported)
{
	std::stringstream input;
	input << "good1 = 1.0\n";
	input << "good2 = 2.0\n";

	const auto stockpile = Vic2::StockpileFactory().importStockpile(input);

	ASSERT_THAT(stockpile, testing::ElementsAre(testing::Pair("good1", 1.0F), testing::Pair("good2", 2.0F)));
}