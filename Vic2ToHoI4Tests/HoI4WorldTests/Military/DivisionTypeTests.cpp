#include "../Vic2ToHoI4/Source/HOI4World/Military/DivisionType.h"
#include "gtest/gtest.h"



TEST(HoI4World_Military_DivisionTypeTests, AllItemsAreAsSet)
{
	const HoI4::DivisionType division("Test Division", "Light Infantry Brigade", 42, 0.3);
	std::ostringstream output;
	output << division;

	std::ostringstream expectedOutput;
	expectedOutput << "\tdivision = {\n";
	expectedOutput << "\t\tname = \"Test Division\"\n";
	expectedOutput << "\t\tlocation = 42\n";
	expectedOutput << "\t\tdivision_template = \"Light Infantry Brigade\"\n";
	expectedOutput << "\t\tstart_experience_factor = 0.3\n";
	expectedOutput << "\t\tstart_equipment_factor = 0.7\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}