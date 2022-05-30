#include "HOI4World/Military/Airplane.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Military_AirplaneTests, AllItemsAreAsSet)
{
	const HoI4::Airplane airplane("test_airplane", "TAG", 42);

	std::stringstream output;
	output << airplane;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttest_airplane = {\n";
	expectedOutput << "\t\t\towner = \"TAG\"\n";
	expectedOutput << "\t\t\tamount = 42\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}