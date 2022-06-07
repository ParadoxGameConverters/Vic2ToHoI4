#include "src/HOI4World/MilitaryMappings/DivisionTemplatesImporter.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_MilitaryMappings_DivisionTemplateImporterTests, DivisionTemplatesDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::DivisionTemplatesImporter divisionTemplatesImporter(input);

	ASSERT_TRUE(divisionTemplatesImporter.takeDivisionTemplates().empty());
}


TEST(HoI4World_MilitaryMappings_DivisionTemplateImporterTests, DivisionTemplatesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdivision_template = {}";
	input << "}";
	const HoI4::DivisionTemplatesImporter divisionTemplatesImporter(input);

	ASSERT_EQ(1, divisionTemplatesImporter.takeDivisionTemplates().size());
}