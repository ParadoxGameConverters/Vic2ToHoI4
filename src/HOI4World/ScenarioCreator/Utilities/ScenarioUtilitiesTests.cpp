#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"

TEST(HoI4World_ScenarioCreator_ScenarioCreatorTests, GetSaveNameRemovesPathAndSaveTpye)
{
	std::string save = "C:\\Users\\Tester\\Documents\\Paradox Interactive\\Victoria II\\save games\\Vanilla.v2";

	EXPECT_THAT(ScenarioUtilities::GetSaveName(save), "Vanilla");
};