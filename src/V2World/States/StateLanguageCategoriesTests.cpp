#include "src/V2World/States/StateLanguageCategories.h"
#include "src/V2World/States/StateLanguageCategoriesBuilder.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(Vic2World_States_StateLanguageCategories, StateCategoryCanBeReturned)
{
	const auto theCategories =
		 Vic2::StateLanguageCategories::Builder().setCategories({{"test_state", "test_category"}}).build();

	ASSERT_EQ("test_category", theCategories->getStateCategory("test_state"));
}


TEST(Vic2World_States_StateLanguageCategories, MissingStateReturnsNullopt)
{
	const auto theCategories = Vic2::StateLanguageCategories::Builder().build();

	ASSERT_EQ(std::nullopt, theCategories->getStateCategory("test_state"));
}