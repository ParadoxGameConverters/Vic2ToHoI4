#include "../Vic2ToHoI4/Source/V2World/Mods/ModFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Mods_ModFactoryTests, NameDefaultsToBlank)
{
	const auto mod = Vic2::Mod::Factory{}.getMod("Vic2/Mod/EmptyModFile.mod", "./");
	ASSERT_TRUE(mod->getName().empty());
}


TEST(Vic2World_Mods_ModFactoryTests, NameCanBeSet)
{
	const auto mod = Vic2::Mod::Factory{}.getMod("Vic2/Mod/Test.mod", "./");
	ASSERT_EQ("Test Mod", mod->getName());
}


TEST(Vic2World_Mods_ModFactoryTests, DirectoryDefaultsToBlank)
{
	const auto mod = Vic2::Mod::Factory{}.getMod("Vic2/Mod/EmptyModFile.mod", "./");
	ASSERT_TRUE(mod->getDirectory().empty());
}


TEST(Vic2World_Mods_ModFactoryTests, DirectoryCanBeSet)
{
	const auto mod = Vic2::Mod::Factory{}.getMod("Vic2/Mod/Test.mod", "./");
	ASSERT_EQ("test_directory", mod->getDirectory());
}