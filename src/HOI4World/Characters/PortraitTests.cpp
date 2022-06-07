#include "src/HOI4World/Characters/Portrait.h"
#include "gtest/gtest.h"



TEST(HoI4World_Characters_Portrait, ItemsAreAsSet)
{
	const HoI4::Portrait portrait("test_type", "test_size", "test_definition");

	EXPECT_EQ(portrait.getType(), "test_type");
	EXPECT_EQ(portrait.getSize(), "test_size");
	EXPECT_EQ(portrait.getDefinition(), "test_definition");
}