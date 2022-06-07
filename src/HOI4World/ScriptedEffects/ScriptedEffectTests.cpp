#include "src/HOI4World/ScriptedEffects/ScriptedEffect.h"
#include "src/HOI4World/ScriptedEffects/ScriptedEffectFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ScriptedEffects_ScriptedEffectTests, NameCanBeSet)
{
	std::stringstream input;
	const auto theEffect = HoI4::ScriptedEffect::Factory().getScriptedEffect("test_name", input);

	ASSERT_EQ("test_name", theEffect->getName());
}


TEST(HoI4World_ScriptedEffects_ScriptedEffectTests, ItemsDefaultToEmpty)
{
	std::stringstream input;
	const auto theEffect = HoI4::ScriptedEffect::Factory().getScriptedEffect("test_name", input);

	ASSERT_TRUE(theEffect->getItems().empty());
}


TEST(HoI4World_ScriptedEffects_ScriptedEffectTests, ItemsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tif = { whatever }\n";
	input << "\tfoo = { bar }\n";
	input << "}";
	const auto theEffect = HoI4::ScriptedEffect::Factory().getScriptedEffect("test_name", input);

	const std::vector<std::pair<std::string, std::string>> expectedItems{{"if", "= { whatever }"}, {"foo", "= { bar }"}};
	ASSERT_EQ(expectedItems, theEffect->getItems());
}


TEST(HoI4World_ScriptedEffects_ScriptedEffectTests, ItemsCanBeModified)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tif = { whatever }\n";
	input << "\tfoo = { bar }\n";
	input << "}";
	const auto theEffect = HoI4::ScriptedEffect::Factory().getScriptedEffect("test_name", input);

	auto& items = theEffect->getMutableItems();
	for (auto& [itemName, itemBody]: items)
	{
		if (itemName == "if")
		{
			itemBody = "= { something }";
			break;
		}
	}
	items.emplace_back(std::make_pair("baz", "= { qux }"));

	const std::vector<std::pair<std::string, std::string>> expectedItems{{"if", "= { something }"},
		 {"foo", "= { bar }"},
		 {"baz", "= { qux }"}};
	ASSERT_EQ(expectedItems, theEffect->getItems());
}