#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include <sstream>


TEST(ConfigurationTests, InputNameDefaultsToInputDotV2)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("input.v2", theConfiguration->getInputFile());
}


TEST(ConfigurationTests, InputNameCanBeSet)
{
	std::stringstream input;
	input << R"(SaveGame = "test.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("test.v2", theConfiguration->getInputFile());
}


TEST(ConfigurationTests, InputNameMustHaveSeperator)
{
	std::stringstream input;
	input << R"(SaveGame = "test")";
	const commonItems::ConverterVersion converterVersion;
	ASSERT_THROW(const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion),
		 std::invalid_argument);
}


TEST(ConfigurationTests, InputNameMustEndInV2)
{
	std::stringstream input;
	input << R"(SaveGame = "test.vic")";
	const commonItems::ConverterVersion converterVersion;
	ASSERT_THROW(const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion),
		 std::invalid_argument);
}


TEST(ConfigurationTests, OutputNameDefaultsToInput)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("input", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameDerivedFromInputName)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromWindowsPath)
{
	std::stringstream input;
	input << R"(SaveGame = "C:\\some directory\\hoi4.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromLinuxPath)
{
	std::stringstream input;
	input << R"(SaveGame = "/some directory/hoi4.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromMixedPathEndingLinuxStyle)
{
	std::stringstream input;
	input << R"(SaveGame = "C:\\some directory\\save games/hoi4.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameExtractedFromMixedPathEndingWindowsStyle)
{
	std::stringstream input;
	input << R"(SaveGame = "/some directory/save games\\hoi4.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameHasDashesReplaced)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4-something.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4_something", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameHasSpacesReplaced)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4 something.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4_something", theConfiguration->getOutputName());
}


TEST(ConfigurationTests, OutputNameMustHaveExtension)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4")";
	const commonItems::ConverterVersion converterVersion;
	ASSERT_THROW(Configuration::Factory().importConfiguration(input, converterVersion), std::invalid_argument);
}


TEST(ConfigurationTests, OutputNameMustHaveValidExtension)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4.eu4")";
	const commonItems::ConverterVersion converterVersion;
	ASSERT_THROW(Configuration::Factory().importConfiguration(input, converterVersion), std::invalid_argument);
}


TEST(ConfigurationTests, OutputNameOnlyRemovesFinalExtension)
{
	std::stringstream input;
	input << R"(SaveGame = "hoi4.eu4.v2")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("hoi4.eu4", theConfiguration->getOutputName());
}

TEST(ConfigurationTests, CustomizedOutputNameCanBeSet)
{
	std::stringstream input;
	input << R"(output_name = "Testname")";

	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("Testname", theConfiguration->getOutputName());
}

TEST(ConfigurationTests, HoI4PathDefaultsToEmpty)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_TRUE(theConfiguration->getHoI4Path().empty());
}


TEST(ConfigurationTests, HoI4PathCanBeSetForWindows)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("./HoI4Windows", theConfiguration->getHoI4Path());
}


TEST(ConfigurationTests, HoI4PathCanBeSetForLinux)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Linux")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("./HoI4Linux", theConfiguration->getHoI4Path());
}


TEST(ConfigurationTests, HoI4PathThrowsExceptionOnNonExistentPath)
{
	std::stringstream input;
	input << R"(HoI4directory = "C:\Non-existent folder")";
	const commonItems::ConverterVersion converterVersion;

	ASSERT_THROW(Configuration::Factory().importConfiguration(input, converterVersion), std::runtime_error);
}


TEST(ConfigurationTests, HoI4PathThrowsExceptionOnPathWithoutHoI4)
{
	std::stringstream input;
	input << R"(HoI4directory = "./")";
	const commonItems::ConverterVersion converterVersion;

	ASSERT_THROW(Configuration::Factory().importConfiguration(input, converterVersion), std::runtime_error);
}


TEST(ConfigurationTests, Vic2PathDefaultsToEmpty)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_TRUE(theConfiguration->getVic2Path().empty());
}


TEST(ConfigurationTests, Vic2PathCanBeSetForWindows)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("./Vic2Windows", theConfiguration->getVic2Path());
}


TEST(ConfigurationTests, Vic2PathCanBeSetForLinux)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2Linux")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("./Vic2Linux", theConfiguration->getVic2Path());
}


TEST(ConfigurationTests, Vic2PathCanBeSetForMacApp)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2MacApp")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("./Vic2MacApp", theConfiguration->getVic2Path());
}


TEST(ConfigurationTests, Vic2PathCanBeSetForMac)
{
	std::stringstream input;
	input << R"(Vic2directory = "./somethingWithMacOS/somethingElse/Vic2Path")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ("./somethingWithMacOS/somethingElse/Vic2Path", theConfiguration->getVic2Path());
}


TEST(ConfigurationTests, Vic2PathThrowsExceptionOnNonExistentPath)
{
	std::stringstream input;
	input << R"(Vic2directory = "C:\Non-existent folder")";
	const commonItems::ConverterVersion converterVersion;

	ASSERT_THROW(Configuration::Factory().importConfiguration(input, converterVersion), std::runtime_error);
}


TEST(ConfigurationTests, Vic2PathThrowsExceptionOnPathWithoutVic2)
{
	std::stringstream input;
	input << R"(Vic2directory = "./")";
	const commonItems::ConverterVersion converterVersion;

	ASSERT_THROW(Configuration::Factory().importConfiguration(input, converterVersion), std::runtime_error);
}

TEST(ConfigurationTests, InstallationVersionsAreLogged)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2Windows")";
	input << R"(HoI4directory = "./HoI4Windows")";

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ConverterVersion converterVersion;
	Configuration::Factory().importConfiguration(input, converterVersion);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(
		 "    [INFO] Reading configuration file\n"
		 "    [INFO] \tVictoria 2 install path is ./Vic2Windows\n"
		 "    [INFO] \tHoI4 path install path is ./HoI4Windows\n"
		 "    [INFO] \tVic2 version: 1.3\n"
		 "    [INFO] \tHoI4 version: 1.10.7\n"
		 "    [INFO] Using output name input\n"
		 "    [INFO] No mods were detected in savegame. Skipping mod processing.\n",
		 log.str());
}

TEST(ConfigurationTests, HoI4ModPathIsLogged)
{
	std::stringstream input;
	input << R"(targetGameModPath = "C:\MyDocuments\Paradox Interactive\Hearts of Iron IV\mod")";

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const commonItems::ConverterVersion converterVersion;
	Configuration::Factory().importConfiguration(input, converterVersion);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(
		 "    [INFO] Reading configuration file\n"
		 "    [INFO] \tHoI4 mod path is C:\\MyDocuments\\Paradox Interactive\\Hearts of Iron IV\\mod\n"
		 "   [ERROR] Vic2 version could not be determined, proceeding blind!\n"
		 " [WARNING] Failure extracting version: /launcher-settings.json does not exist.\n"
		 "   [ERROR] HoI4 version could not be determined, proceeding blind!\n"
		 "    [INFO] Using output name input\n"
		 "    [INFO] No mods were detected in savegame. Skipping mod processing.\n",
		 log.str());
}


TEST(ConfigurationTests, Vic2ModsDefaultsToEmpty)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_TRUE(theConfiguration->getVic2Mods().empty());
}

TEST(ConfigurationTests, Vic2ModsCanBeSet)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2")";
	input << "selectedMods = { \n";
	input << "\t\"Test.mod\"\n";
	input << "\t\"NonExistentFile.mod\"\n";
	input << "}";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(1, theConfiguration->getVic2Mods().size());
	ASSERT_EQ("Test Mod", theConfiguration->getVic2Mods()[0].name);
}


TEST(ConfigurationTests, Vic2ModsWithDependenciesAreBeforeTheirDependencies)
{
	std::stringstream input;
	input << R"(Vic2directory = "./Vic2")";
	input << "selectedMods = { \n";
	input << "\t\"DependencyTwo.mod\"\n";
	input << "\t\"DependencyOne.mod\"\n";
	input << "\t\"Test.mod\"\n";
	input << "\t\"Dependent.mod\"\n";
	input << "}";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_THAT(theConfiguration->getVic2Mods(),
		 testing::ElementsAre(Mod("Dependent Mod", "./Vic2/mod/test_directory/", std::set<Name>{"Dependency One"}),
			  Mod("Dependency One", "./Vic2/mod/test_directory/", std::set<Name>{"Dependency Two"}),
			  Mod("Dependency Two", "./Vic2/mod/test_directory/"),
			  Mod("Test Mod", "./Vic2/mod/test_directory/")));
}


TEST(ConfigurationTests, ForceMultiplierDefaultsToOne)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(1.0f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierCanBeSet)
{
	std::stringstream input;
	input << R"(force_multiplier = "0.5")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.5f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierIsMaximumOneHundred)
{
	std::stringstream input;
	input << R"(force_multiplier = "150.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(100.0f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierIsMinimumOneHundredth)
{
	std::stringstream input;
	input << R"(force_multiplier = "-1.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.01f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ForceMultiplierMustBeNumeric)
{
	std::stringstream input;
	input << R"(force_multiplier = "abcd")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.01f, theConfiguration->getForceMultiplier());
}


TEST(ConfigurationTests, ManpowerFactorDefaultsToOne)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(1.0f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorCanBeSet)
{
	std::stringstream input;
	input << R"(manpower_factor = "0.5")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.5f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorIsMaximumTen)
{
	std::stringstream input;
	input << R"(manpower_factor = "15.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(10.0f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorIsMinimumOneHundredth)
{
	std::stringstream input;
	input << R"(manpower_factor = "-1.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.01f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, ManpowerFactorMustBeNumeric)
{
	std::stringstream input;
	input << R"(manpower_factor = "abcd")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.01f, theConfiguration->getManpowerFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorDefaultsToZero)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.0f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorCanBeSet)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "0.5")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.5f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorIsMaximumOne)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "15.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(1.0f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorIsMinimumZero)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "-1.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.0f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, IndustrialShapeFactorFactorMustBeNumeric)
{
	std::stringstream input;
	input << R"(industrial_shape_factor = "abcd")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.00f, theConfiguration->getIndustrialShapeFactor());
}


TEST(ConfigurationTests, FactoryFactorDefaultsToOneTenth)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.1f, theConfiguration->getFactoryFactor());
}


TEST(ConfigurationTests, FactoryFactorFactorCanBeSet)
{
	std::stringstream input;
	input << R"(factory_factor = "0.5")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.5f, theConfiguration->getFactoryFactor());
}


TEST(ConfigurationTests, FactoryFactorFactorIsMaximumOne)
{
	std::stringstream input;
	input << R"(factory_factor = "15.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(1.0f, theConfiguration->getFactoryFactor());
}


TEST(ConfigurationTests, FactoryFactorFactorIsMinimumZero)
{
	std::stringstream input;
	input << R"(factory_factor = "-1.0")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.0f, theConfiguration->getFactoryFactor());
}


TEST(ConfigurationTests, FactoryFactorFactorMustBeNumeric)
{
	std::stringstream input;
	input << R"(factory_factor = "abcd")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.00f, theConfiguration->getFactoryFactor());
}


TEST(ConfigurationTests, IdeologiesOptionsDefaultsToKeepMajor)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(ideologyOptions::keep_major, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepAll)
{
	std::stringstream input;
	input << R"(ideologies = "keep_all")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(ideologyOptions::keep_all, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepDefault)
{
	std::stringstream input;
	input << R"(ideologies = "keep_default")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(ideologyOptions::keep_default, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepSpecified)
{
	std::stringstream input;
	input << R"(ideologies = "specify")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(ideologyOptions::specified, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsCanBeSetToKeepMajor)
{
	std::stringstream input;
	input << "ideologies = \"specified\"\n";
	input << R"(ideologies = "keep_major")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(ideologyOptions::keep_major, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, IdeologiesOptionsRevertsToKeepMajor)
{
	std::stringstream input;
	input << R"(ideologies = "foo")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(ideologyOptions::keep_major, theConfiguration->getIdeologiesOptions());
}


TEST(ConfigurationTests, SpecifiedIdeologiesDefaultsToNeutrality)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	const std::vector<std::string> expectedOutput{{"neutrality"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveCommunismSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "communism" })";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"communism"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveAbsolutistSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "absolutist" })";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"absolutist"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveDemocraticSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "democratic" })";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"democratic"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveFascismSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "fascism" })";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"fascism"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, SpecifiedIdeologiesCanHaveRadicalSpecified)
{
	std::stringstream input;
	input << R"(ideologies_choice = { "radical" })";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	const std::vector<std::string> expectedOutput{{"neutrality"}, {"radical"}};
	ASSERT_EQ(expectedOutput, theConfiguration->getSpecifiedIdeologies());
}


TEST(ConfigurationTests, DebugDefaultsToNo)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_FALSE(theConfiguration->getDebug());
}


TEST(ConfigurationTests, DebugCanBeSetToYes)
{
	std::stringstream input;
	input << R"(debug = "yes")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_TRUE(theConfiguration->getDebug());
}


TEST(ConfigurationTests, DebugCanBeSetToNo)
{
	std::stringstream input;
	input << "debug = \"yes\"\n";
	input << R"(debug = "no")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_FALSE(theConfiguration->getDebug());
}


TEST(ConfigurationTests, RemoveCoresDefaultsToAcceptedCulture)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(removeCoresOptions::remove_accepted_culture_by_owner, theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, RemoveCoresCanBeSetToRemoveAcceptedCulture)
{
	std::stringstream input;
	input << R"(remove_cores = "remove_accepted_culture_by_owner")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(removeCoresOptions::remove_accepted_culture_by_owner, theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, RemoveCoresCanBeSetToRemoveTooLittleCulture)
{
	std::stringstream input;
	input << R"(remove_cores = "remove_too_little_culture")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(removeCoresOptions::remove_too_little_culture, theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, RemoveCoresCanBeSetToRemoveSameCulture)
{
	std::stringstream input;
	input << R"(remove_cores = "remove_same_culture_as_owner")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(removeCoresOptions::remove_same_culture_as_owner, theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, RemoveCoresCanBeSetToRemoveNone)
{
	std::stringstream input;
	input << R"(remove_cores = "remove_none")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(removeCoresOptions::remove_none, theConfiguration->getRemoveCores());
}


TEST(ConfigurationTests, CreateFactionsDefaultsToYes)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_TRUE(theConfiguration->getCreateFactions());
}


TEST(ConfigurationTests, CreateFactionsCanBeSetToNo)
{
	std::stringstream input;
	input << R"(create_factions = "no")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_FALSE(theConfiguration->getCreateFactions());
}


TEST(ConfigurationTests, CreateFactionsCanBeSetToYes)
{
	std::stringstream input;
	input << "create_factions = \"no\"\n";
	input << R"(create_factions = "yes")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_TRUE(theConfiguration->getCreateFactions());
}


TEST(ConfigurationTests, PercentOfCommandersDefaultsToFivePercent)
{
	std::stringstream input;
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.05f, theConfiguration->getPercentOfCommanders());
}


TEST(ConfigurationTests, PercentOfCommandersCanBeSet)
{
	std::stringstream input;
	input << R"(percent_of_commanders = "5")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	ASSERT_EQ(0.05F, theConfiguration->getPercentOfCommanders());
}