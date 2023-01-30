#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/ResourcesLink.h"



TEST(HoI4World_Map_ResourcesLink, ProvinceNumDefaultsToZero)
{
	std::stringstream input;
	const HoI4::ResourcesLink link(input);

	ASSERT_EQ(0, link.getProvinceNum());
}


TEST(HoI4World_Map_ResourcesLink, ProvinceNumCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovince = 42\n";
	input << "}";
	const HoI4::ResourcesLink link(input);

	ASSERT_EQ(42, link.getProvinceNum());
}


TEST(HoI4World_Map_ResourcesLink, ResourcesDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::ResourcesLink link(input);

	ASSERT_EQ(0, link.getProvinceNum());
}


TEST(HoI4World_Map_ResourcesLink, ResourcesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tresources = {\n";
	input << "\t\tresource_one = 1.5\n";
	input << "\t\tresource_two = 2.5\n";
	input << "\t}\n";
	input << "}";
	HoI4::ResourcesLink link(input);

	const std::map<std::string, double> expectedResources{{"resource_one", 1.5}, {"resource_two", 2.5}};
	ASSERT_EQ(expectedResources, link.takeResources());
}