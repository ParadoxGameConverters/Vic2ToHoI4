#include "HOI4World/MilitaryMappings/AllMilitaryMappings.h"
#include "gtest/gtest.h"
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
	input << "\"POPs of Darkness\" = {\n";
	input << "\tunit_map = {}\n";
	input << "\tmtg_unit_map = {}\n";
	input << "}\n";
	allTheMappings = std::make_unique<HoI4::allMilitaryMappings>(input);
}



TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getDefaultMappingsWithNoMods)
{
	const Mods mods;
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getDefaultMappingsWithInvalidMod)
{
	Mods mods;
	mods.emplace_back(Mod("NotAMod", ""));
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getModMappingsWithSimpleName)
{
	Mods mods;
	mods.emplace_back(Mod("PDM", "PDM/"));
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("PDM"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getModMappingsWithQuotedName)
{
	Mods mods;
	mods.emplace_back(Mod("POPs of Darkness", "POP/"));
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("POPs of Darkness"), specificMappings.getMappingsName());
}