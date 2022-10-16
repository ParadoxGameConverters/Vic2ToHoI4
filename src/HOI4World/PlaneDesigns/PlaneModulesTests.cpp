#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_PlaneModulesTests, ModulesDefaultToEmpty)
{
	std::stringstream input;
	input << "";
	HoI4::PlaneModules the_plane_modules(input);

	std::stringstream output;
	output << the_plane_modules;

	std::stringstream expected_output;
	expected_output << "\t\tmodules = {\n";
	expected_output << "\t\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneModulesTests, ModulesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmodule_slot1 = module1\n";
	input << "\tmodule_slot2 = module2\n";
	input << "}";
	HoI4::PlaneModules the_plane_modules(input);

	std::stringstream output;
	output << the_plane_modules;

	std::stringstream expected_output;
	expected_output << "\t\tmodules = {\n";
	expected_output << "\t\t\tmodule_slot1 = module1\n";
	expected_output << "\t\t\tmodule_slot2 = module2\n";
	expected_output << "\t\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}