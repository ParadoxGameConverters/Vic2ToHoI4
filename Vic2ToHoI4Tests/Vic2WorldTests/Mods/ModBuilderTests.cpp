#include "V2World/Mods/ModBuilder.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Vic2World_Mods_ModBuilderTests, NameDefaultsToBlank)
{
	const auto mod = Vic2::Mod::Builder{}.build();
	ASSERT_TRUE(mod->getName().empty());
}


TEST(Vic2World_Mods_ModBuilderTests, NameCanBeSet)
{
	const auto mod = Vic2::Mod::Builder{}.setName("Test Mod Name").build();
	ASSERT_EQ("Test Mod Name", mod->getName());
}


TEST(Vic2World_Mods_ModBuilderTests, DirectoryDefaultsToBlank)
{
	const auto mod = Vic2::Mod::Builder{}.build();
	ASSERT_TRUE(mod->getDirectory().empty());
}


TEST(Vic2World_Mods_ModBuilderTests, DirectoryCanBeSet)
{
	const auto mod = Vic2::Mod::Builder{}.setDirectory("test_directory").build();
	ASSERT_EQ("test_directory", mod->getDirectory());
}

TEST(Vic2World_Mods_ModBuilderTests, DependenciesDefaultToEmpty)
{
	const auto mod = Vic2::Mod::Builder{}.build();

	ASSERT_TRUE(mod->getDependencies().empty());
}


TEST(Vic2World_Mods_ModBuilderTests, DependenciesCanBeSet)
{
	const auto mod = Vic2::Mod::Builder{}.addDependency("dependency_one").addDependency("dependency two").build();

	ASSERT_THAT(mod->getDependencies(), testing::UnorderedElementsAre("dependency_one", "dependency two"));
}