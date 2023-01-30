#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Ideologies/Ideology.h"
#include "src/OutHoi4/Ideologies/OutIdeology.h"
#include <sstream>



TEST(HoI4World_Ideologies_IdeologyTests, DefaultsAreAsExpected)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, NameIsAsSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t}";
	const HoI4::Ideology ideology("ideology_name", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\tideology_name = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, TypesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\ttypes = {\n";
	input << "\t\t\ttype_one = {\n";
	input << "\t\t\t}\n";
	input << "\t\t\ttype_two = {\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	const auto expectedTypes = std::vector<std::string>{"type_one", "type_two"};
	ASSERT_EQ(expectedTypes, ideology.getTypes());
}


TEST(HoI4World_Ideologies_IdeologyTests, DynamicFactionNamesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\tdynamic_faction_names = {\n";
	input << "\t\t\t\"faction_name_one\"\n";
	input << "\t\t\t\"faction_name_two\"\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t\t\"faction_name_one\"\n";
	expectedOutput << "\t\t\t\"faction_name_two\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, ColorCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 1 2 3 }\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 1 2 3 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, WarImpactOnWorldTensionCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\twar_impact_on_world_tension = 5.5\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, FactionImpactOnWorldTensionCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\tfaction_impact_on_world_tension = 5.5\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, RulesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\trules = {\n";
	input << "\t\t\trule_one = yes\n";
	input << "\t\t\trule_two = yes\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t\trule_one = yes\n";
	expectedOutput << "\t\t\trule_two = yes\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, ModifiersCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\tmodifiers = {\n";
	input << "\t\t\tnavy_intel_to_others = 10.0\n";
	input << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	expectedOutput << "\t\t\tnavy_intel_to_others = 10.0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, FactionModifiersCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\tfaction_modifiers = {\n";
	input << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, AiCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\tai_foo = yes\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tai_foo = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, CansCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tcolor = { 0 0 0 }\n";
	input << "\t\tcan_foo = yes\n";
	input << "\t\tcan_bar = no\n";
	input << "\t}";
	const HoI4::Ideology ideology("", input);

	std::stringstream output;
	output << ideology;

	std::stringstream expectedOutput;
	expectedOutput << "\t = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 0 0 0 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 0\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 0\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcan_bar = no\n";
	expectedOutput << "\t\tcan_foo = yes\n";
	expectedOutput << "\n";
	expectedOutput << "\t\t = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, IdeologyCanBeCopyConstructed)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttypes = {\n";
	input << "\t\t\ttype_one = {\n";
	input << "\t\t\t}\n";
	input << "\t\t\ttype_two = {\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\tdynamic_faction_names = {\n";
	input << "\t\t\t\"faction_name_one\"\n";
	input << "\t\t\t\"faction_name_two\"\n";
	input << "\t\t}\n";
	input << "\t\tcolor = { 1 2 3 }\n";
	input << "\t\trules = {\n";
	input << "\t\t\trule_one = yes\n";
	input << "\t\t\trule_two = yes\n";
	input << "\t\t}\n";
	input << "\t\twar_impact_on_world_tension = 5.5\n";
	input << "\t\tfaction_impact_on_world_tension = 5.5\n";
	input << "\t\tmodifiers = {\n";
	input << "\t\t\tnavy_intel_to_others = 10.0\n";
	input << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	input << "\t\t}\n";
	input << "\t\tfaction_modifiers = {\n";
	input << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	input << "\t\t}\n";
	input << "\t\tcan_bar = no\n";
	input << "\t\tcan_foo = yes\n";
	input << "\t\tai_foo = yes\n";
	input << "\t}";
	const HoI4::Ideology ideology("ideology_name", input);
	const auto ideologyTwo(ideology);

	std::stringstream output;
	output << ideologyTwo;

	std::stringstream expectedOutput;
	expectedOutput << "\tideology_name = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t\t\t\n";
	expectedOutput << "\t\t\ttype_one = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\t\ttype_two = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t\t\"faction_name_one\"\n";
	expectedOutput << "\t\t\t\"faction_name_two\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 1 2 3 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t\trule_one = yes\n";
	expectedOutput << "\t\t\trule_two = yes\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	expectedOutput << "\t\t\tnavy_intel_to_others = 10.0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcan_bar = no\n";
	expectedOutput << "\t\tcan_foo = yes\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tai_foo = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, IdeologyCanBeMoveConstructed)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttypes = {\n";
	input << "\t\t\ttype_one = {\n";
	input << "\t\t\t}\n";
	input << "\t\t\ttype_two = {\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\tdynamic_faction_names = {\n";
	input << "\t\t\t\"faction_name_one\"\n";
	input << "\t\t\t\"faction_name_two\"\n";
	input << "\t\t}\n";
	input << "\t\tcolor = { 1 2 3 }\n";
	input << "\t\trules = {\n";
	input << "\t\t\trule_one = yes\n";
	input << "\t\t\trule_two = yes\n";
	input << "\t\t}\n";
	input << "\t\twar_impact_on_world_tension = 5.5\n";
	input << "\t\tfaction_impact_on_world_tension = 5.5\n";
	input << "\t\tmodifiers = {\n";
	input << "\t\t\tnavy_intel_to_others = 10.0\n";
	input << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	input << "\t\t}\n";
	input << "\t\tfaction_modifiers = {\n";
	input << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	input << "\t\t}\n";
	input << "\t\tcan_bar = no\n";
	input << "\t\tcan_foo = yes\n";
	input << "\t\tai_foo = yes\n";
	input << "\t}";
	HoI4::Ideology ideology("ideology_name", input);
	const auto ideologyTwo(std::move(ideology));

	std::stringstream output;
	output << ideologyTwo;

	std::stringstream expectedOutput;
	expectedOutput << "\tideology_name = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t\t\t\n";
	expectedOutput << "\t\t\ttype_one = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\t\ttype_two = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t\t\"faction_name_one\"\n";
	expectedOutput << "\t\t\t\"faction_name_two\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 1 2 3 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t\trule_one = yes\n";
	expectedOutput << "\t\t\trule_two = yes\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	expectedOutput << "\t\t\tnavy_intel_to_others = 10.0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcan_bar = no\n";
	expectedOutput << "\t\tcan_foo = yes\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tai_foo = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, IdeologyCanBeAssigned)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttypes = {\n";
	input << "\t\t\ttype_one = {\n";
	input << "\t\t\t}\n";
	input << "\t\t\ttype_two = {\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\tdynamic_faction_names = {\n";
	input << "\t\t\t\"faction_name_one\"\n";
	input << "\t\t\t\"faction_name_two\"\n";
	input << "\t\t}\n";
	input << "\t\tcolor = { 1 2 3 }\n";
	input << "\t\trules = {\n";
	input << "\t\t\trule_one = yes\n";
	input << "\t\t\trule_two = yes\n";
	input << "\t\t}\n";
	input << "\t\twar_impact_on_world_tension = 5.5\n";
	input << "\t\tfaction_impact_on_world_tension = 5.5\n";
	input << "\t\tmodifiers = {\n";
	input << "\t\t\tnavy_intel_to_others = 10.0\n";
	input << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	input << "\t\t}\n";
	input << "\t\tfaction_modifiers = {\n";
	input << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	input << "\t\t}\n";
	input << "\t\tcan_bar = no\n";
	input << "\t\tcan_foo = yes\n";
	input << "\t\tai_foo = yes\n";
	input << "\t}";
	const HoI4::Ideology ideology("ideology_name", input);
	const auto ideologyTwo = ideology;

	std::stringstream output;
	output << ideologyTwo;

	std::stringstream expectedOutput;
	expectedOutput << "\tideology_name = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t\t\t\n";
	expectedOutput << "\t\t\ttype_one = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\t\ttype_two = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t\t\"faction_name_one\"\n";
	expectedOutput << "\t\t\t\"faction_name_two\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 1 2 3 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t\trule_one = yes\n";
	expectedOutput << "\t\t\trule_two = yes\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	expectedOutput << "\t\t\tnavy_intel_to_others = 10.0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcan_bar = no\n";
	expectedOutput << "\t\tcan_foo = yes\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tai_foo = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Ideologies_IdeologyTests, IdeologyCanBeMoveAssigned)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttypes = {\n";
	input << "\t\t\ttype_one = {\n";
	input << "\t\t\t}\n";
	input << "\t\t\ttype_two = {\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t\tdynamic_faction_names = {\n";
	input << "\t\t\t\"faction_name_one\"\n";
	input << "\t\t\t\"faction_name_two\"\n";
	input << "\t\t}\n";
	input << "\t\tcolor = { 1 2 3 }\n";
	input << "\t\trules = {\n";
	input << "\t\t\trule_one = yes\n";
	input << "\t\t\trule_two = yes\n";
	input << "\t\t}\n";
	input << "\t\twar_impact_on_world_tension = 5.5\n";
	input << "\t\tfaction_impact_on_world_tension = 5.5\n";
	input << "\t\tmodifiers = {\n";
	input << "\t\t\tnavy_intel_to_others = 10.0\n";
	input << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	input << "\t\t}\n";
	input << "\t\tfaction_modifiers = {\n";
	input << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	input << "\t\t}\n";
	input << "\t\tcan_bar = no\n";
	input << "\t\tcan_foo = yes\n";
	input << "\t\tai_foo = yes\n";
	input << "\t}";
	const HoI4::Ideology ideology("ideology_name", input);
	const auto ideologyTwo = std::move(ideology);

	std::stringstream output;
	output << ideologyTwo;

	std::stringstream expectedOutput;
	expectedOutput << "\tideology_name = {\n";
	expectedOutput << "\t\n";
	expectedOutput << "\t\ttypes = {\n";
	expectedOutput << "\t\t\t\n";
	expectedOutput << "\t\t\ttype_one = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\t\ttype_two = {\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tdynamic_faction_names = {\n";
	expectedOutput << "\t\t\t\"faction_name_one\"\n";
	expectedOutput << "\t\t\t\"faction_name_two\"\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tcolor = { 1 2 3 }\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\trules = {\n";
	expectedOutput << "\t\t\trule_one = yes\n";
	expectedOutput << "\t\t\trule_two = yes\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\twar_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\tfaction_impact_on_world_tension = 5.5\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tmodifiers = {\n";
	expectedOutput << "\t\t\thidden_modifier = { join_faction_tension = -0.1 }\n";
	expectedOutput << "\t\t\tnavy_intel_to_others = 10.0\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\t\n";
	expectedOutput << "\t\tfaction_modifiers = {\n";
	expectedOutput << "\t\t\tfaction_trade_opinion_factor = 0.50\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcan_bar = no\n";
	expectedOutput << "\t\tcan_foo = yes\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tai_foo = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n\n\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}