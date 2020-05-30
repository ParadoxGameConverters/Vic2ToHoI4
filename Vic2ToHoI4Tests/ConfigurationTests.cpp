#include "../Vic2ToHoI4/Source/Configuration.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(ConfigurationTests, InputNameDefaultsToInputDotV2)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("input.v2", theConfiguration->getInputFile());
}


TEST(ConfigurationTests, InputNameCanBeSet)
{
	std::stringstream input;
	input << R"(SaveGame = "test.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("test.v2", theConfiguration->getInputFile());
}


TEST(ConfigurationTests, InputNameMustHaveSeperator)
{
	std::stringstream input;
	input << R"(SaveGame = "test")";
	ASSERT_THROW(const auto theConfiguration = Configuration::Factory{}.importConfiguration(input),
		 std::invalid_argument);
}


TEST(ConfigurationTests, InputNameMustEndInV2)
{
	std::stringstream input;
	input << R"(SaveGame = "test.vic")";
	ASSERT_THROW(const auto theConfiguration = Configuration::Factory{}.importConfiguration(input),
		 std::invalid_argument);
}


TEST(ConfigurationTests, OutputNameDefaultsToInput)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("input", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameDerivedFromInputName)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromWindowsPath)
{
	std::stringstream input;
	input << R"(SaveGame = "C:\\some directory\\hoi4.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromLinuxPath)
{
	std::stringstream input;
	input << R"(SaveGame = "/some directory/hoi4.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromMixedPathEndingLinuxStyle)
{
	std::stringstream input;
	input << R"(SaveGame = "C:\\some directory\\save games/hoi4.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromMixedPathEndingWindowsStyle)
{
	std::stringstream input;
	input << R"(SaveGame = "/some directory/save games\\hoi4.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameHasDashesReplaced)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4-something.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4_something", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameHasSpacesReplaced)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4 something.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4_something", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameMustHaveExtension)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4")";
	ASSERT_THROW(Configuration::Factory{}.importConfiguration(input), std::invalid_argument);
}


TEST(ConfigurationTests, OutputNameMustHaveValidExtension)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4.eu4")";
	ASSERT_THROW(Configuration::Factory{}.importConfiguration(input), std::invalid_argument);
}


TEST(ConfigurationTests, OutputNameOnlyRemovesFinalExtension)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4.eu4.v2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("hoi4.eu4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, HoI4PathDefaultsToEmpty)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getHoI4Path().empty());
}


TEST(ConfigurationTests, HoI4PathCanBeSetForWindows)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("./HoI4Windows", theConfiguration->getHoI4Path());
}


TEST(ConfigurationTests, HoI4PathCanBeSetForLinux)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Linux")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("./HoI4Linux", theConfiguration->getHoI4Path());
}


TEST(ConfigurationTests, HoI4PathThrowsExceptionOnNonExistentPath)
{
	std::stringstream input;
	input << R"(HoI4directory = "C:\Non-existent folder")";

	ASSERT_THROW(Configuration::Factory{}.importConfiguration(input), std::runtime_error);
}


TEST(ConfigurationTests, HoI4PathThrowsExceptionOnPathWithoutHoI4)
{
	std::stringstream input;
	input << R"(HoI4directory = "./")";

	ASSERT_THROW(Configuration::Factory{}.importConfiguration(input), std::runtime_error);
}


TEST(ConfigurationTests, Vic2PathDefaultsToEmpty)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getVic2Path().empty());
}


TEST(ConfigurationTests, Vic2PathCanBeSetForWindows)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2Windows")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("./Vic2Windows", theConfiguration->getVic2Path());
}


TEST(ConfigurationTests, Vic2PathCanBeSet)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2Linux")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ("./Vic2Linux", theConfiguration->getVic2Path());
}


TEST(ConfigurationTests, Vic2PathThrowsExceptionOnNonExistentPath)
{
	std::stringstream input;
	input << R"(Vic2directory = "C:\Non-existent folder")";

	ASSERT_THROW(Configuration::Factory{}.importConfiguration(input), std::runtime_error);
}


TEST(ConfigurationTests, Vic2PathThrowsExceptionOnPathWithoutVic2)
{
	std::stringstream input;
	input << R"(Vic2directory = "./")";

	ASSERT_THROW(Configuration::Factory{}.importConfiguration(input), std::runtime_error);
}


TEST(ConfigurationTests, Vic2ModsDefaultsToEmpty)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getVic2Mods().empty());
}

TEST(ConfigurationTests, Vic2ModsCanBeSet)
{
	std::stringstream input;
	input << R"(Vic2Mods = "Mod")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(1, theConfiguration->getVic2Mods().size());
	ASSERT_EQ("Mod", theConfiguration->getVic2Mods()[0]);
}

TEST(ConfigurationTests, Vic2ModsCanBeSetWithDoubleQuotedMod)
{
	std::stringstream input;
	input << R"(Vic2Mods = ""Mod"")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(1, theConfiguration->getVic2Mods().size());
	ASSERT_EQ("Mod", theConfiguration->getVic2Mods()[0]);
}

TEST(ConfigurationTests, Vic2ModsCanBeSetWithMultipleMods)
{
	std::stringstream input;
	input << R"(Vic2Mods = ""Mod One" Mod2")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(2, theConfiguration->getVic2Mods().size());
	ASSERT_EQ("Mod One", theConfiguration->getVic2Mods()[0]);
	ASSERT_EQ("Mod2", theConfiguration->getVic2Mods()[1]);
}


TEST(ConfigurationTests, ForceMultiplierDefaultsToOne)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(1.0f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierCanBeSet)
{
	std::stringstream input;
	input << R"(force_multiplier = "0.5")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.5f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierIsMaximumOneHundred)
{
	std::stringstream input;
	input << R"(force_multiplier = "150.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(100.0f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierIsMinimumOneHundredth)
{
	std::stringstream input;
	input << R"(force_multiplier = "-1.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.01f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierMustBeNumeric)
{
	std::stringstream input;
	input << R"(force_multiplier = "abcd")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.01f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ManpowerFactorDefaultsToOne)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(1.0f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorCanBeSet)
{
	std::stringstream input;
	input << R"(manpower_factor = "0.5")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.5f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorIsMaximumTen)
{
	std::stringstream input;
	input << R"(manpower_factor = "15.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(10.0f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorIsMinimumOneHundredth)
{
	std::stringstream input;
	input << R"(manpower_factor = "-1.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.01f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorMustBeNumeric)
{
	std::stringstream input;
	input << R"(manpower_factor = "abcd")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.01f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorDefaultsToZero)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.0f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorCanBeSet)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "0.5")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.5f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorIsMaximumOne)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "15.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(1.0f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorIsMinimumZero)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "-1.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.0f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorMustBeNumeric)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "abcd")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.00f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, ICFactorDefaultsToOneTenth)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.1f, theConfiguration->getIcFactor());
}


TEST(ConfigurationTests, ICFactorFactorCanBeSet)
{
	std::stringstream input;
	input << R"(ic_factor = "0.5")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.5f, theConfiguration->getIcFactor());
}


TEST(ConfigurationTests, ICFactorFactorIsMaximumOne)
{
	std::stringstream input;
	input << R"(ic_factor = "15.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(1.0f, theConfiguration->getIcFactor());
}


TEST(ConfigurationTests, ICFactorFactorIsMinimumZero)
{
	std::stringstream input;
	input << R"(ic_factor = "-1.0")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.0f, theConfiguration->getIcFactor());
}


TEST(ConfigurationTests, ICFactorFactorMustBeNumeric)
{
	std::stringstream input;
	input << R"(ic_factor = "abcd")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(0.00f, theConfiguration->getIcFactor());
}


TEST(ConfigurationTests, IdeologiesOptionsDefaultsToKeepMajor)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(ideologyOptions::keep_major, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepAll)
{
	std::stringstream input;
	input << R"(ideologies = "keep_all")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(ideologyOptions::keep_all, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepDefault)
{
	std::stringstream input;
	input << R"(ideologies = "keep_default")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(ideologyOptions::keep_default, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepSpecified)
{
	std::stringstream input;
	input << R"(ideologies = "specified")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(ideologyOptions::specified, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepMajor)
{
	std::stringstream input;
	input << "ideologies = \"specified\"\n";
	input << R"(ideologies = "keep_major")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(ideologyOptions::keep_major, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsRevertsToKeepMajor)
{
	std::stringstream input;
	input << R"(ideologies = "foo")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_EQ(ideologyOptions::keep_major, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, SpecifiedIdeologiesDefaultsToNeutrality)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	const std::vector<std::string> expectedOutput{{"neutrality"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveCommunismSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "communism" })";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"communism"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveAbsolutistSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "absolutist" })";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"absolutist"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveDemocraticSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "democratic" })";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"democratic"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveFascismSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "fascism" })";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"fascism"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveRadicalSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "radical" })";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"radical"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, DebugDefaultsToNo)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_FALSE(theConfiguration->getDebug());
}


TEST(ConfigurationTests, DebugCanBeSetToYes)
{
	std::stringstream input;
	input << R"(debug = "yes")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getDebug());
}


TEST(ConfigurationTests, DebugCanBeSetToNo)
{
	std::stringstream input;
	input << "debug = \"yes\"\n";
	input << R"(debug = "no")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_FALSE(theConfiguration->getDebug());
}


TEST(ConfigurationTests, RemoveCoresDefaultsToYes)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, RemoveCoresCanBeSetToNo)
{
	std::stringstream input;
	input << R"(remove_cores = "no")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_FALSE(theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, RemoveCoresCanBeSetToYes)
{
	std::stringstream input;
	input << "remove_cores = \"no\"\n";
	input << R"(remove_cores = "yes")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, CreateFactionsDefaultsToYes)
{
	std::stringstream input;
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getCreateFactions());
}


TEST(ConfigurationTests, CreateFactionsCanBeSetToNo)
{
	std::stringstream input;
	input << R"(create_factions = "no")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_FALSE(theConfiguration->getCreateFactions());
}


TEST(ConfigurationTests, CreateFactionsCanBeSetToYes)
{
	std::stringstream input;
	input << "create_factions = \"no\"\n";
	input << R"(create_factions = "yes")";
	const auto theConfiguration = Configuration::Factory{}.importConfiguration(input);

	ASSERT_TRUE(theConfiguration->getCreateFactions());
}