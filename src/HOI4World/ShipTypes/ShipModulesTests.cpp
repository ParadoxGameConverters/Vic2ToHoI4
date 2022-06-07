#include "src/HOI4World/ShipTypes/ShipModules.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_shipModulesTests, modulesDefaultToEmpty)
{
	std::stringstream input;
	input << "";
	HoI4::shipModules theShipModules(input);

	std::stringstream output;
	output << theShipModules;

	std::stringstream expectedOutput;
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipModulesTests, modulesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmodule_slot1 = module1\n";
	input << "\tmodule_slot2 = module2\n";
	input << "}";
	HoI4::shipModules theShipModules(input);

	std::stringstream output;
	output << theShipModules;

	std::stringstream expectedOutput;
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tmodule_slot1 = module1\n";
	expectedOutput << "\t\t\tmodule_slot2 = module2\n";
	expectedOutput << "\t\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}