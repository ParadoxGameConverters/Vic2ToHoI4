#include "../Vic2ToHoI4/Source/HoI4World/Military/DivisionTemplate.h"
#include "gtest/gtest.h"



TEST(HoI4World_DivisionTemplateTests, DivisionTempateNameDefaultsToBlank)
{
	std::istringstream input("");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_EQ(std::string(""), divisionTemplate.getName());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateNameCanBeImported)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_EQ(std::string("Light Infantry Brigade"), divisionTemplate.getName());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateNameCopiedWithCopyConstructor)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	HoI4::DivisionTemplateType divisionTemplate2(divisionTemplate);
	ASSERT_EQ(divisionTemplate.getName(), divisionTemplate2.getName());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateRegimentsDefaultToEmpty)
{
	std::istringstream input("");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_EQ(size_t(0), divisionTemplate.getRegiments().size());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateRegimentsCanBeImported)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tregiments = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_EQ(size_t(1), divisionTemplate.getRegiments().size());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateRegimentsCopiedWithCopyConstructor)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tregiments = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	HoI4::DivisionTemplateType divisionTemplate2(divisionTemplate);
	ASSERT_EQ(divisionTemplate.getRegiments().size(), divisionTemplate2.getRegiments().size());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateSupportRegimentsDefaultToEmpty)
{
	std::istringstream input("");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_EQ(size_t(0), divisionTemplate.getSupportRegiments().size());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateSupportRegimentsCanBeImported)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tsupport = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_EQ(size_t(1), divisionTemplate.getSupportRegiments().size());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempateSupportRegimentsCopiedWithCopyConstructor)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tsupport = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	HoI4::DivisionTemplateType divisionTemplate2(divisionTemplate);
	ASSERT_EQ(divisionTemplate.getSupportRegiments().size(), divisionTemplate2.getSupportRegiments().size());
}


TEST(HoI4World_DivisionTemplateTests, BlankDivisionTemplateOutputsProperly)
{
	std::istringstream input("");
	HoI4::DivisionTemplateType divisionTemplate(input);
	std::ostringstream output;
	output << divisionTemplate;

	std::string outputString(
		 "division_template = {\n"
		 "\tname = \"\"\n"
		 "\n"
		 "\tregiments = {\n"
		 "\t}\n"
		 "\tsupport = {\n"
		 "\t}\n"
		 "}\n");
	ASSERT_EQ(outputString, output.str());
}


TEST(HoI4World_DivisionTemplateTests, ImportedDivisionTemplateOutputsProperly)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t\tregiments = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t\tsupport = {\n"
		 "\t\t\t\trecon = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	std::ostringstream output;
	output << divisionTemplate;

	std::string outputString(
		 "division_template = {\n"
		 "\tname = \"Light Infantry Brigade\"\n"
		 "\n"
		 "\tregiments = {\n"
		 "\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t}\n"
		 "\tsupport = {\n"
		 "\t\trecon = { x = 0 y = 0 }\n"
		 "\t}\n"
		 "}\n");
	ASSERT_EQ(outputString, output.str());
}


TEST(HoI4World_DivisionTemplateTests, CopiedDivisionTemplateOutputsProperly)
{
	std::istringstream input("");
	HoI4::DivisionTemplateType divisionTemplate(input);
	std::ostringstream output;
	output << divisionTemplate;

	std::string outputString(
		 "division_template = {\n"
		 "\tname = \"\"\n"
		 "\n"
		 "\tregiments = {\n"
		 "\t}\n"
		 "\tsupport = {\n"
		 "\t}\n"
		 "}\n");
	ASSERT_EQ(outputString, output.str());
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempatesWithDifferentNamesNotEqual)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_FALSE(divisionTemplate == std::string("Light Infantry Brigade2"));
}


TEST(HoI4World_DivisionTemplateTests, DivisionTempatesWithSameNamesEqual)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);
	ASSERT_TRUE(divisionTemplate == std::string("Light Infantry Brigade"));
}