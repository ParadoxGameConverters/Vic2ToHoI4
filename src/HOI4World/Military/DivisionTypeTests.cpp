#include "HOI4World/Military/DivisionType.h"
#include "gtest/gtest.h"



TEST(HoI4World_Military_DivisionTypeTests, AllItemsAreAsSet)
{
	const HoI4::DivisionType division("Test Division", "Light Infantry Brigade", 42, 0.3, 0.8, {});
	std::ostringstream output;
	output << division;

	std::ostringstream expectedOutput;
	expectedOutput << "\tdivision = {\n";
	expectedOutput << "\t\tname = \"Test Division\"\n";
	expectedOutput << "\t\tlocation = 42\n";
	expectedOutput << "\t\tdivision_template = \"Light Infantry Brigade\"\n";
	expectedOutput << "\t\tstart_experience_factor = 0.3\n";
	expectedOutput << "\t\tstart_equipment_factor = 0.8\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Military_DivisionTypeTests, TypeCanBeRead)
{
	const HoI4::DivisionType division("Test Division", "Light Infantry Brigade", 42, 0.3, 0.8, {});

	ASSERT_EQ("Light Infantry Brigade", division.getType());
}


TEST(HoI4World_Military_DivisionTypeTests, RegimentsAreAsSet)
{
	std::map<std::string, int> regiments{{"type_one", 1}, {"type_2", 2}};
	const HoI4::DivisionType division("Test Division", "Light Infantry Brigade", 42, 0.3, 0.8, regiments);

	ASSERT_EQ(regiments, division.getRegiments());
}