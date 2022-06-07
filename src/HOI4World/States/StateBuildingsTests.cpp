#include "src/HOI4World/States/StateBuildings.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_States_StateBuildingsTests, CivFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(0, theStateBuildings.getCivFactories());
}


TEST(HoI4World_States_StateBuildingsTests, VivFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tindustrial_complex = 5\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(5, theStateBuildings.getCivFactories());
}


TEST(HoI4World_States_StateBuildingsTests, MilFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(0, theStateBuildings.getMilFactories());
}


TEST(HoI4World_States_StateBuildingsTests, MilFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tarms_factory = 7\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(7, theStateBuildings.getMilFactories());
}


TEST(HoI4World_States_StateBuildingsTests, dockyardsDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(0, theStateBuildings.getMilFactories());
}


TEST(HoI4World_States_StateBuildingsTests, DockyardsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(1, theStateBuildings.getDockyards());
}


TEST(HoI4World_States_StateBuildingsTests, DockyardsAreAdditive)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t\t5678 = {\n";
	input << "\t\t\t\tnaval_base = 3";
	input << "\t\t\t}\n";
	input << "\t\t}";
	const HoI4::StateBuildings theStateBuildings(input);

	ASSERT_EQ(4, theStateBuildings.getDockyards());
}