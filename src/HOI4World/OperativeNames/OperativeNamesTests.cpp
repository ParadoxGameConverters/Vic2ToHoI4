#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/OperativeNames/OperativeNames.h"
#include "src/HOI4World/OperativeNames/OperativeNamesFactory.h"
#include <sstream>



TEST(HoI4World_OperativeNames_OperativeNamesTests, OperativeNamesDefaultsToEmpty)
{
	const auto operativeNames = HoI4::OperativeNames::Factory::getOperativeNames("bad_path");

	ASSERT_TRUE(operativeNames->getOperativeNamesSets().empty());
}


TEST(HoI4World_OperativeNames_OperativeNamesTests, OperativeNamesCanBeAdded)
{
	const auto operativeNames = HoI4::OperativeNames::Factory::getOperativeNames(".");

	ASSERT_EQ(2, operativeNames->getOperativeNamesSets().size());
}