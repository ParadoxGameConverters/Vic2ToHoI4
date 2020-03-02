#include "../Vic2ToHoI4/Source/HoI4World/Military/Division.h"
#include "gtest/gtest.h"



TEST(HoI4World_DivisionTests, BlankDivisionTypeOutputsProperly)
{
	HoI4::DivisionType division("", "", 0, 0.0);
	std::ostringstream output;
	output << division;

	std::ostringstream expectedOutput;
	expectedOutput << "\tdivision = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\tlocation = 0\n";
	expectedOutput << "\t\tdivision_template = \"\"\n";
	expectedOutput << "\t\tstart_experience_factor = 0.0\n";
	expectedOutput << "\t\tstart_equipment_factor = 0.7\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_DivisionTests, ConfiguredDivisionTypeOutputsProperly)
{
	HoI4::DivisionType division("Test Division", "Light Infantry Brigade", 42, 0.3);
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


TEST(HoI4World_DivisionTests, CopiedDivisionTypeOutputsProperly)
{
	HoI4::DivisionType division("Test Division", "Light Infantry Brigade", 42, 0.3);
	HoI4::DivisionType division2 = division;
	std::ostringstream output;
	output << division2;

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