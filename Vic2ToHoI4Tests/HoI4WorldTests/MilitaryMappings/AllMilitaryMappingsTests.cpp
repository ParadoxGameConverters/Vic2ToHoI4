#include "HOI4World/MilitaryMappings/AllMilitaryMappings.h"
#include "V2World/Mods/ModBuilder.h"
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
	const std::vector<Vic2::Mod> mods;
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getDefaultMappingsWithInvalidMod)
{
	std::vector<Vic2::Mod> mods;
	mods.push_back(*Vic2::Mod::Builder().setName("NotAMod").build());
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("default"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getModMappingsWithSimpleName)
{
	std::vector<Vic2::Mod> mods;
	mods.push_back(*Vic2::Mod::Builder().setName("PDM").build());
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("PDM"), specificMappings.getMappingsName());
}


TEST_F(HoI4World_MilitaryMappings_allMilitaryMappingsTests, getModMappingsWithQuotedName)
{
	std::vector<Vic2::Mod> mods;
	mods.push_back(*Vic2::Mod::Builder().setName("POPs of Darkness").build());
	const auto& specificMappings = allTheMappings->getMilitaryMappings(mods);
	ASSERT_EQ(std::string("POPs of Darkness"), specificMappings.getMappingsName());
}