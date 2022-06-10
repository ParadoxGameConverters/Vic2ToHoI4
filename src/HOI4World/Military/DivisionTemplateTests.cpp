#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Military/DivisionTemplate.h"



TEST(HoI4World_Military_DivisionTemplateTests, NameDefaultsToBlank)
{
	std::istringstream input;
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_EQ("", divisionTemplate.getName());
}


TEST(HoI4World_Military_DivisionTemplateTests, NameCanBeSet)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_EQ("Light Infantry Brigade", divisionTemplate.getName());
}


TEST(HoI4World_Military_DivisionTemplateTests, RegimentsDefaultToEmpty)
{
	std::istringstream input;
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_TRUE(divisionTemplate.getRegiments().empty());
}


TEST(HoI4World_Military_DivisionTemplateTests, RegimentsCanBeSet)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tregiments = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_EQ(1, divisionTemplate.getRegiments().size());
	ASSERT_EQ("infantry", divisionTemplate.getRegiments()[0].getType());
}


TEST(HoI4World_Military_DivisionTemplateTests, SupportRegimentsDefaultToEmpty)
{
	std::istringstream input;
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_TRUE(divisionTemplate.getSupportRegiments().empty());
}


TEST(HoI4World_Military_DivisionTemplateTests, SupportRegimentsCanBeSet)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tsupport = {\n"
		 "\t\t\t\tinfantry = { x = 0 y = 0 }\n"
		 "\t\t\t}\n"
		 "\t\t}\n");
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_EQ(1, divisionTemplate.getSupportRegiments().size());
	ASSERT_EQ("infantry", divisionTemplate.getSupportRegiments()[0].getType());
}


TEST(HoI4World_Military_DivisionTemplateTests, DivisionTemplatesWithDifferentNamesNotEqual)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_FALSE(divisionTemplate == std::string("Light Infantry Brigade2"));
}


TEST(HoI4World_Military_DivisionTemplateTests, DivisionTemplatesWithSameNamesEqual)
{
	std::istringstream input(
		 "= {\n"
		 "\t\t\tname = \"Light Infantry Brigade\"\n"
		 "\t\t}\n");
	const HoI4::DivisionTemplateType divisionTemplate(input);

	ASSERT_EQ(divisionTemplate, std::string("Light Infantry Brigade"));
}