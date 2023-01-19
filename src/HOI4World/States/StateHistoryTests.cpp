#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/States/StateHistory.h"
#include <sstream>



TEST(HoI4World_States_StateHistoryTests, OwnerDefaultsToBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_TRUE(theStateHistory.getOwner().empty());
}


TEST(HoI4World_States_StateHistoryTests, OwnerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\towner = TAG\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ("TAG", theStateHistory.getOwner());
}


TEST(HoI4World_States_StateHistoryTests, CivFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(0, theStateHistory.getCivFactories());
}


TEST(HoI4World_States_StateHistoryTests, CivFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\tindustrial_complex = 5\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(5, theStateHistory.getCivFactories());
}


TEST(HoI4World_States_StateHistoryTests, MilFactoriesDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(0, theStateHistory.getMilFactories());
}


TEST(HoI4World_States_StateHistoryTests, MilFactoriesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\tarms_factory = 7\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(7, theStateHistory.getMilFactories());
}


TEST(HoI4World_States_StateHistoryTests, DockyardsDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(0, theStateHistory.getMilFactories());
}


TEST(HoI4World_States_StateHistoryTests, DockyardsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(1, theStateHistory.getDockyards());
}


TEST(HoI4World_States_StateHistoryTests, DockyardsAreAdditive)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tbuildings = {\n";
	input << "\t\t\t1234 = {\n";
	input << "\t\t\t\tnaval_base = 1";
	input << "\t\t\t}\n";
	input << "\t\t\t5678 = {\n";
	input << "\t\t\t\tnaval_base = 3";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::StateHistory theStateHistory(input);

	ASSERT_EQ(4, theStateHistory.getDockyards());
}