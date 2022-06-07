#include "src/HOI4World/States/DefaultState.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_States_DefaultStateTests, impassibleDefaultsToFalse)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_FALSE(theState.isImpassable());
}


TEST(HoI4World_States_DefaultStateTests, impassibleCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\timpassable = yes\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_TRUE(theState.isImpassable());
}


TEST(HoI4World_States_DefaultStateTests, provincesDefaultToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_TRUE(theState.getProvinces().empty());
}


TEST(HoI4World_States_DefaultStateTests, provincesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = {\n";
	input << "\t\t1 2 3 4\n";
	input << "\t}\n";
	input << "}";
	HoI4::DefaultState theState(input);

	ASSERT_EQ(4, theState.getProvinces().size());
	ASSERT_TRUE(theState.getProvinces().contains(1));
	ASSERT_TRUE(theState.getProvinces().contains(2));
	ASSERT_TRUE(theState.getProvinces().contains(3));
	ASSERT_TRUE(theState.getProvinces().contains(4));
}


TEST(HoI4World_States_DefaultStateTests, ownerDefaultsToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_TRUE(theState.getOwner().empty());
}


TEST(HoI4World_States_DefaultStateTests, ownerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thistory = {\n";
	input << "\t\towner = TAG\n";
	input << "\t}\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ("TAG", theState.getOwner());
}


TEST(HoI4World_States_DefaultStateTests, civFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(0, theState.getCivFactories());
}


TEST(HoI4World_States_DefaultStateTests, civFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thistory = {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\tindustrial_complex = 5\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(5, theState.getCivFactories());
}


TEST(HoI4World_States_DefaultStateTests, milFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(0, theState.getMilFactories());
}


TEST(HoI4World_States_DefaultStateTests, milFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thistory = {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\tarms_factory = 7\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(7, theState.getMilFactories());
}


TEST(HoI4World_States_DefaultStateTests, dockyardsDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(0, theState.getMilFactories());
}


TEST(HoI4World_States_DefaultStateTests, dockyardsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thistory = {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(1, theState.getDockyards());
}


TEST(HoI4World_States_DefaultStateTests, dockyardsCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thistory = {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t\t5678 = {\n";
	input << "\t\t\t\tnaval_base = 3";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";
	const HoI4::DefaultState theState(input);

	ASSERT_EQ(4, theState.getDockyards());
}