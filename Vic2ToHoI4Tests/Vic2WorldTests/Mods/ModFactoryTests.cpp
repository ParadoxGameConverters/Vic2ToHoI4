#include "../Vic2ToHoI4/Source/V2World/Mods/ModFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Mods_ModFactoryTests, NameMissingCausesException)
{
	ASSERT_THROW(Vic2::Mod::Factory{}.getMod("EmptyModFile.mod", "./Vic2/Mod"), std::runtime_error);
}


TEST(Vic2World_Mods_ModFactoryTests, NameCanBeSet)
{
	const auto mod = Vic2::Mod::Factory{}.getMod("Test.mod", "./Vic2/Mod");
	ASSERT_EQ("Test Mod", mod->getName());
}


TEST(Vic2World_Mods_ModFactoryTests, DirectoryUnspecifiedThrowsException)
{
	ASSERT_THROW(Vic2::Mod::Factory{}.getMod("DirectoryUnspecified.mod", "./Vic2/Mod"), std::runtime_error);
}


TEST(Vic2World_Mods_ModFactoryTests, DirectoryMissingThrowsException)
{
	ASSERT_THROW(Vic2::Mod::Factory{}.getMod("DirectoryMissing.mod", "./Vic2/Mod"), std::runtime_error);
}


TEST(Vic2World_Mods_ModFactoryTests, DirectoryCanBeSet)
{
	const auto mod = Vic2::Mod::Factory{}.getMod("Test.mod", "./Vic2/Mod");
	ASSERT_EQ("test_directory", mod->getDirectory());
}