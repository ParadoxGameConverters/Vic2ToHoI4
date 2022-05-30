#include "HOI4World/Events/Event.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Events_EventTests, TypeDefaultsToBlank)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TypeCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveType("eventType");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TypeCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, IdDefaultsToBlank)
{
	const HoI4::Event theEvent;
	ASSERT_EQ(theEvent.getId(), "");
}


TEST(HoI4World_Events_EventTests, IdCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveId("testId");

	ASSERT_EQ(theEvent.getId(), "testId");
}


TEST(HoI4World_Events_EventTests, IdCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tid = testId\n";
	input << "}";
	const HoI4::Event theEvent("eventType", input);

	ASSERT_EQ(theEvent.getId(), "testId");
}


TEST(HoI4World_Events_EventTests, TitleDefaultsToNullopt)
{
	const HoI4::Event theEvent;

	ASSERT_FALSE(theEvent.getTitle());
}


TEST(HoI4World_Events_EventTests, TitleCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveTitle("eventTitle");

	ASSERT_EQ(theEvent.getTitle(), "eventTitle");
}


TEST(HoI4World_Events_EventTests, TitleCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttitle = eventTitle\n";
	input << "}";
	const HoI4::Event theEvent("eventType", input);

	ASSERT_EQ(theEvent.getTitle(), "eventTitle");
}


TEST(HoI4World_Events_EventTests, DescriptionsDefaultToEmpty)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, DescriptionsCanBeCleared)
{
	HoI4::Event theEvent;
	theEvent.giveDescription("= \"description one\"");
	theEvent.clearDescriptions();

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, DescriptionsCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveDescription("= \"description one\"");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\tdesc = \"description one\"\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, DescriptionsCanBeGivenMultipleTimes)
{
	HoI4::Event theEvent;
	theEvent.giveDescription("= \"description one\"");
	theEvent.giveDescription("= \"description two\"");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\tdesc = \"description one\"\n";
	expectedOutput += "\tdesc = \"description two\"\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, DescriptionsCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdesc = eventDescription\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\tdesc = eventDescription\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, PictureDefaultsToNullopt)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, PictureCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.givePicture("eventPicture");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\tpicture = eventPicture\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, PictureCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpicture = eventPicture\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\tpicture = eventPicture\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, MajorEventDefaultsToFalse)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, MajorEventCanBeSetTrue)
{
	HoI4::Event theEvent;
	theEvent.setMajor();

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\t\n";
	expectedOutput += "\tmajor = yes\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, MajorEventCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmajor = yes\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\t\n";
	expectedOutput += "\tmajor = yes\n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TriggeredOnlyDefaultsToFalse)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TriggeredOnlyCanBeSetTrue)
{
	HoI4::Event theEvent;
	theEvent.setTriggeredOnly();

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\tis_triggered_only = yes\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TriggeredOnlyCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tis_triggered_only = yes\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\tis_triggered_only = yes\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, HiddenDefaultsToFalse)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, HiddenCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thidden = yes\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\thidden = yes\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TriggerDefaultsToEmpty)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TriggerCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveTrigger(
		 "= {\n"
		 "\t\tfoo = bar\n"
		 "\t}");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\ttrigger = {\n";
	expectedOutput += "\t\tfoo = bar\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, TriggerCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttrigger = {\n";
	input << "\t\tfoo = bar\n";
	input << "\t}\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\ttrigger = {\n";
	expectedOutput += "\t\tfoo = bar\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, FireOnlyOnceDefaultsToFalse)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, FireOnlyOnceCanBeSet)
{
	HoI4::Event theEvent;
	theEvent.setFireOnlyOnce();

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n\n";
	expectedOutput += "\tfire_only_once = yes\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, FireOnlyOnceCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tfire_only_once = yes\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n\n";
	expectedOutput += "\tfire_only_once = yes\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, MeanTimeToHappenDefaultsToEmpty)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, MeanTimeToHappenCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveMeanTimeToHappen(
		 "= {\n"
		 "\t\tdays = 150\n"
		 "\t}");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\tmean_time_to_happen = {\n";
	expectedOutput += "\t\tdays = 150\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, MeanTimeToHappenCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmean_time_to_happen = {\n";
	input << "\t\tdays = 150\n";
	input << "\t}\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\tmean_time_to_happen = {\n";
	expectedOutput += "\t\tdays = 150\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, ImmediateDefaultsToEmpty)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, ImmediateCanBeGiven)
{
	HoI4::Event theEvent;
	theEvent.giveImmediate(
		 "= {\n"
		 "\t\tfoo = bar\n"
		 "\t}");

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\timmediate = {\n";
	expectedOutput += "\t\tfoo = bar\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, ImmediateCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\timmediate = {\n";
	input << "\t\tfoo = bar\n";
	input << "\t}\n";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\timmediate = {\n";
	expectedOutput += "\t\tfoo = bar\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, OptionsDefaultToEmpty)
{
	const HoI4::Event theEvent;

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, OptionsCanBeGiven)
{
	HoI4::Event theEvent;
	HoI4::EventOption optionOne;
	theEvent.giveOption(std::move(optionOne));

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, OptionsCanBeGivenMultipleTimes)
{
	HoI4::Event theEvent;
	HoI4::EventOption optionOne;
	theEvent.giveOption(std::move(optionOne));
	HoI4::EventOption optionTwo;
	theEvent.giveOption(std::move(optionTwo));

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += " = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "\n";
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, OptionsCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toption = {\n";
	input << "\t\tname = optionalName\n";
	input << "\t}";
	input << "}";
	HoI4::Event theEvent("eventType", input);

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "\n";
	expectedOutput += "\toption = {\n";
	expectedOutput += "\t\tname = optionalName\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}


TEST(HoI4World_Events_EventTests, OptionsCanBeCleared)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toption = {\n";
	input << "\t\tname = \n";
	input << "\t}";
	input << "}";
	HoI4::Event theEvent("eventType", input);
	theEvent.clearOptions();

	std::stringstream actualOutput;
	actualOutput << theEvent;

	std::string expectedOutput;
	expectedOutput += "eventType = {\n";
	expectedOutput += "\tid = \n";
	expectedOutput += "\n";
	expectedOutput += "}\n";

	ASSERT_EQ(actualOutput.str(), expectedOutput);
}