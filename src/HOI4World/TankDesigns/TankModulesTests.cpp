#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/TankDesigns/TankModules.h"
#include <sstream>



TEST(HoI4World_TankDesigns_TankModulesTests, modulesDefaultToEmpty)
{
	std::stringstream input;
	input << "";
	HoI4::TankModules theTankModules(input);

	std::stringstream output;
	output << theTankModules;

	std::stringstream expectedOutput;
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankModulesTests, modulesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmodule_slot1 = module1\n";
	input << "\tmodule_slot2 = module2\n";
	input << "}";
	HoI4::TankModules theTankModules(input);

	std::stringstream output;
	output << theTankModules;

	std::stringstream expectedOutput;
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tmodule_slot1 = module1\n";
	expectedOutput << "\t\t\tmodule_slot2 = module2\n";
	expectedOutput << "\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}