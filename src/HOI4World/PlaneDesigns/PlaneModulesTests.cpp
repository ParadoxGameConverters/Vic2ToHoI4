#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_PlaneModulesTests, modulesDefaultToEmpty)
{
	std::stringstream input;
	input << "";
	HoI4::PlaneModules thePlaneModules(input);

	std::stringstream output;
	output << thePlaneModules;

	std::stringstream expectedOutput;
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneModulesTests, modulesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmodule_slot1 = module1\n";
	input << "\tmodule_slot2 = module2\n";
	input << "}";
	HoI4::PlaneModules thePlaneModules(input);

	std::stringstream output;
	output << thePlaneModules;

	std::stringstream expectedOutput;
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tmodule_slot1 = module1\n";
	expectedOutput << "\t\t\tmodule_slot2 = module2\n";
	expectedOutput << "\t\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}