#include "HOI4World/Map/ActualResources.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Map_ActualResources, ResourcesDefaultToEmpty)
{
	std::stringstream input;
	HoI4::ActualResources actualResources(input);

	ASSERT_TRUE(actualResources.takeResources().empty());
}


TEST(HoI4World_Map_ActualResources, ResourcesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tresource = 2.5\n";
	input << "}";
	HoI4::ActualResources actualResources(input);

	auto resources = actualResources.takeResources();
	ASSERT_EQ(resources.size(), 1);
	ASSERT_EQ(resources.find("resource")->second, 2.5);
}