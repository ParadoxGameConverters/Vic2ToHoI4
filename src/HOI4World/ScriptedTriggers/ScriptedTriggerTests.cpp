#include "src/HOI4World/ScriptedTriggers/ScriptedTrigger.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ScriptedTriggers_SciptedTriggerTests, NameCanBeSet)
{
	const HoI4::ScriptedTrigger theTrigger("name");

	ASSERT_EQ("name", theTrigger.getName());
}


TEST(HoI4World_ScriptedTriggers_SciptedTriggerTests, BodyDefaultsToEmpty)
{
	const HoI4::ScriptedTrigger theTrigger("name");
	std::stringstream output;
	output << theTrigger;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "name \n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ScriptedTriggers_SciptedTriggerTests, BodyCanBeSet)
{
	HoI4::ScriptedTrigger theTrigger("name");
	theTrigger.setBody("the_body");
	std::stringstream output;
	output << theTrigger;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "name the_body\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}