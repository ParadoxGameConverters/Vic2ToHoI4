#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Characters/OutPortrait.h"
#include <sstream>



TEST(OutHoI4World_Characters_OutPortrait, PortraitIsOutput)
{
	const HoI4::Portrait portrait("test_type", "test_size", "portrait_directory/portrait_file.tga");
	std::stringstream output;
	output << portrait;

	std::stringstream expected;
	expected << "\t\t\ttest_type={\n";
	expected << "\t\t\t\ttest_size=\"portrait_directory/portrait_file.tga\"\n";
	expected << "\t\t\t}\n";

	EXPECT_EQ(output.str(), expected.str());
}