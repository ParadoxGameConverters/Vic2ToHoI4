#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/AllMilitaryMappings.h"
#include <sstream>


class HoI4World_MilitaryMappings_allMilitaryMappingsTests: public testing::Test
{
	protected:
	HoI4World_MilitaryMappings_allMilitaryMappingsTests();

		std::unique_ptr<HoI4::allMilitaryMappings> allTheMappings;
};


HoI4World_MilitaryMappings_allMilitaryMappingsTests::HoI4World_MilitaryMappings_allMilitaryMappingsTests()
{
	std::stringstream input;
	input << "default = {\n";
	input << "\tunit_map = {}\n";
	input << "\tmtg_unit_map = {}\n";
	input << "}\n";
	input << "PDM = {\n";
	input << "\tunit_map = {}\n";
	input << "\tmtg_unit_map = {}\n";
	input << "}\n";
	allTheMappings = std::make_unique<HoI4::allMilitaryMappings>(input);
}



TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getDefaultMappingsWithNoMods)
{
	const std::vector<std::string> mods;
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getDefaultMappingsWithInvalidMod)
{
	const std::vector<std::string> mods = { "NotAMod" };
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getPDMMappingsWithPDM)
{
	const std::vector<std::string> mods = { "PDM" };
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("PDM"), specificMappings.getMappingsName());
}