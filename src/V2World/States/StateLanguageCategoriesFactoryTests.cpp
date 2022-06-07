#include "src/V2World/States/StateLanguageCategories.h"
#include "src/V2World/States/StateLanguageCategoriesFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_States_StateLanguageCategories, StateCategoriesCanBeImported)
{
	const auto theCategories = Vic2::StateLanguageCategories::Factory().getCategories();

	ASSERT_EQ("test_category", theCategories->getStateCategory("test_state"));
}