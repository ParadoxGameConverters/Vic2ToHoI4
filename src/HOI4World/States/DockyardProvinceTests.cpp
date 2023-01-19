#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/States/DockyardProvince.h"
#include <sstream>



TEST(HoI4World_States_DockyardProvinceTests, DockyardsLevelDefaultsToZero)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DockyardProvince theDockyardProvince(input);

	ASSERT_EQ(0, theDockyardProvince.getDockyardsLevel());
}


TEST(HoI4World_States_DockyardProvinceTests, DockyardsLevelCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\t\tnaval_base = 3";
	input << "}";
	const HoI4::DockyardProvince theDockyardProvince(input);

	ASSERT_EQ(3, theDockyardProvince.getDockyardsLevel());
}