#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Landmarks/LandmarkBuildings.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "src/V2World/States/StateBuilder.h"
#include <gmock/gmock-matchers.h>
#include <sstream>



TEST(HoI4World_Landmarks_LandmarkBuildingsTests, DefaultLandmarkBuildingsCanBeImported)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);

	std::stringstream output;
	output << landmarkBuildings;

	std::stringstream expectedOutput;
	expectedOutput << "@landmark_constant = 0.1\n";
	expectedOutput << "\n";
	expectedOutput << "buildings = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tlandmark_test = {\n";
	expectedOutput << "\t\tproperty_one = test_string\n";
	expectedOutput << "\t\tproperty_two = 42\n";
	expectedOutput << "\t\tproperty_three = {\n";
	expectedOutput << "\t\t\tvariable = 1\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tcountry_modifiers = {\n";
	expectedOutput << "\t\t\tenable_for_controllers = { TAG }\n";
	expectedOutput << "\t\t\tmodifiers = {\n";
	expectedOutput << "\t\t\t\tmodifier_one = 0.1\n";
	expectedOutput << "\t\t\t\tmodifier_two = 0.2\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tlandmark_unbuilt = {\n";
	expectedOutput << "\t\tcountry_modifiers = {\n";
	expectedOutput << "\t\t\tenable_for_controllers = { }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\tlandmark_unmapped = {\n";
	expectedOutput << "\t\tcountry_modifiers = {\n";
	expectedOutput << "\t\t\tenable_for_controllers = { }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "spawn_points = {\n";
	expectedOutput << "\tlandmark_spawn = {\n";
	expectedOutput << "\t\ttype = province\n";
	expectedOutput << "\t\tmax = 1\n";
	expectedOutput << "\t\tdisable_auto_nudging = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";

	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Landmarks_LandmarkBuildingsTests, ConstantsCanBeImported)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);

	const auto& constants = landmarkBuildings.getConstants();
	ASSERT_FALSE(constants.empty());

	const auto& [firstConstantKey, firstConstantValue] = *constants.begin();
	EXPECT_EQ("@landmark_constant", firstConstantKey);
	EXPECT_EQ(0.1f, firstConstantValue);
}


TEST(HoI4World_Landmarks_LandmarkBuildingsTests, SpawnPointsCanBeImported)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);

	std::stringstream spawnPoints;
	spawnPoints << "= {\n";
	spawnPoints << "\tlandmark_spawn = {\n";
	spawnPoints << "\t\ttype = province\n";
	spawnPoints << "\t\tmax = 1\n";
	spawnPoints << "\t\tdisable_auto_nudging = yes\n";
	spawnPoints << "\t}\n";
	spawnPoints << "}";

	EXPECT_EQ(spawnPoints.str(), landmarkBuildings.getSpawnPoints());
}


TEST(HoI4World_Landmarks_LandmarkBuildingsTests, LandmarksCanBeImported)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);
	const auto& landmarks = landmarkBuildings.getBuildings();

	ASSERT_FALSE(landmarks.empty());

	std::stringstream output;
	output << *landmarks.begin()->second;

	std::stringstream expectedOutput;
	expectedOutput << "\tlandmark_test = {\n";
	expectedOutput << "\t\tproperty_one = test_string\n";
	expectedOutput << "\t\tproperty_two = 42\n";
	expectedOutput << "\t\tproperty_three = {\n";
	expectedOutput << "\t\t\tvariable = 1\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tcountry_modifiers = {\n";
	expectedOutput << "\t\t\tenable_for_controllers = { TAG }\n";
	expectedOutput << "\t\t\tmodifiers = {\n";
	expectedOutput << "\t\t\t\tmodifier_one = 0.1\n";
	expectedOutput << "\t\t\t\tmodifier_two = 0.2\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";

	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Landmarks_LandmarkBuildingsTests, EnabledControllersCanBeSet)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);

	const auto mapper = Mappers::LandmarksMapper();

	const auto sourceState = *Vic2::State::Builder().build();
	HoI4::State theState(sourceState, 123, "X01");
	theState.addProvince(42);
	std::map<int, HoI4::State> states = {{123, theState}};

	landmarkBuildings.updateBuildings(states, mapper);

	const auto& landmarks = landmarkBuildings.getBuildings();
	ASSERT_TRUE(landmarks.contains("landmark_test"));

	const auto& controllers = landmarks.at("landmark_test")->getEnabledControllers();

	EXPECT_EQ(std::vector<std::string>{"X01"}, controllers);
}


TEST(HoI4World_Landmarks_LandmarkBuildingsTests, UnmappedLandmarksLogWarning)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);

	const auto mapper = Mappers::LandmarksMapper();
	std::map<int, HoI4::State> states;

	const std::stringstream log;
	auto* const stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	landmarkBuildings.updateBuildings(states, mapper);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] No landmark location mapping for landmark_unmapped"));
}


TEST(HoI4World_Landmarks_LandmarkBuildingsTests, UnmappedLandmarksAreNotOutput)
{
	std::stringstream input;
	input << R"(HoI4directory = "./HoI4Windows")";
	const commonItems::ConverterVersion converterVersion;
	const auto theConfiguration = Configuration::Factory().importConfiguration(input, converterVersion);

	auto landmarkBuildings = HoI4::LandmarkBuildings(*theConfiguration);

	const auto mapper = Mappers::LandmarksMapper();
	std::map<int, HoI4::State> states;

	landmarkBuildings.updateBuildings(states, mapper);

	std::stringstream output;
	output << landmarkBuildings;

	std::stringstream expectedOutput;
	expectedOutput << "@landmark_constant = 0.1\n";
	expectedOutput << "\n";
	expectedOutput << "buildings = {\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	expectedOutput << "spawn_points = {\n";
	expectedOutput << "\tlandmark_spawn = {\n";
	expectedOutput << "\t\ttype = province\n";
	expectedOutput << "\t\tmax = 1\n";
	expectedOutput << "\t\tdisable_auto_nudging = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}";

	EXPECT_EQ(expectedOutput.str(), output.str());
}