#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/MilitaryMappings.h"


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, missingUnitMapSectionThrowsError)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmtg_unit_map = {\n";
	input << "\t}";
	input << "}";

	ASSERT_THROW(HoI4::militaryMappings theMappings(std::string(), input), std::invalid_argument);
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, unitMapSectionCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tunit_map = {\n";
	input << "\t}";
	input << "\tmtg_unit_map = {\n";
	input << "\t}";
	input << "}";
	HoI4::militaryMappings theMappings(std::string(), input);

	ASSERT_NO_THROW(auto unused = theMappings.getUnitMappings());
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, missingMtgUnitMapSectionThrowsError)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";

	ASSERT_THROW(HoI4::militaryMappings theMappings(std::string(), input), std::invalid_argument);
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, MapSectionCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tunit_map = {\n";
	input << "\t}";
	input << "\tmtg_unit_map = {\n";
	input << "\t}";
	input << "}";
	HoI4::militaryMappings theMappings(std::string(), input);

	ASSERT_NO_THROW(auto unused = theMappings.getMtgUnitMappings());
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, emptyDivisionTemplatesStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tunit_map = {}\n"\
		"\tmtg_unit_map = {}\n"\
		"\tdivision_templates = {\n"\
		"\t}"\
		"}"
	);
	const HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getDivisionTemplates().size());
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, TemplateAddedToDivisionTemplateMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tunit_map = {}\n"\
		"\tmtg_unit_map = {}\n"\
		"\tdivision_templates = {\n"\
		"\t\tdivision_template = {\n"\
		"\t\t\tname = \"Light Infantry Brigade\"\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	const HoI4::militaryMappings theMappings("", input);
	auto templates = theMappings.getDivisionTemplates();
	ASSERT_FALSE(std::find(templates.begin(), templates.end(), "Light Infantry Brigade") == templates.end());
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, emptySubstitutesStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tunit_map = {}\n"\
		"\tmtg_unit_map = {}\n"\
		"\tsubstitutes = {\n"\
		"\t}"\
		"}"
	);
	const HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getSubstitutes().size());
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, substituteAddedToSubstitutes)
{
	std::stringstream input(
		"= {\n"\
		"\tunit_map = {}\n"\
		"\tmtg_unit_map = {}\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	const HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getSubstitutes().size());
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, substituteNameInList)
{
	std::stringstream input(
		"= {\n"\
		"\tunit_map = {}\n"\
		"\tmtg_unit_map = {}\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	const HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getSubstitutes().count("artillery"));
}


TEST(HoI4World_MilitaryMappings_militaryMappingsTests, substituteAlternateInMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tunit_map = {}\n"\
		"\tmtg_unit_map = {}\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	const HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(std::string("artillery_brigade"), theMappings.getSubstitutes().at("artillery"));
}