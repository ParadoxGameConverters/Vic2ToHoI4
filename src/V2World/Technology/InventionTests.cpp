#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Configuration.h"
#include "src/V2World/Technology/Inventions.h"
#include "src/V2World/Technology/InventionsFactory.h"
#include <gmock/gmock-matchers.h>



TEST(Vic2World_Technology_InventionTests, MissingInventionLogsErrorAndReturnsNullopt)
{
	const auto inventions = Vic2::Inventions();

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto inventionName = inventions.getInventionName(1);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(),
		 testing::HasSubstr("[WARNING] Invalid invention. Is this using a mod that changed inventions?"));
	ASSERT_EQ(std::nullopt, inventionName);
}


TEST(Vic2World_Technology_InventionTests, InventionZeroLogsErrorAndReturnsNullopt)
{
	const auto inventions = Vic2::Inventions();

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto inventionName = inventions.getInventionName(0);

	std::cout.rdbuf(stdOutBuf);

	EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Invalid invention zero."));
	ASSERT_EQ(std::nullopt, inventionName);
}


#ifndef _DEBUG // disable some test that break code coverage
TEST(Vic2World_Technology_InventionTests, InventionNameIsReturned)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"), {});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_EQ("test_tech_one", inventions->getInventionName(1));
}


TEST(Vic2World_Technology_InventionTests, AllInventionFilesAreRead)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"), {});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_EQ("test_tech_one", inventions->getInventionName(1));
	ASSERT_EQ("test_tech_two", inventions->getInventionName(2));
}


TEST(Vic2World_Technology_InventionTests, InventionsWithAtypicalCharactersAreReturned)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"), {});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_NE(std::nullopt, inventions->getInventionName(3));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesAreRead)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"),
		 {Mod("one", "ModInventions/Mod1")});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_EQ("test_tech_four", inventions->getInventionName(4));
}


TEST(Vic2World_Technology_InventionTests, MultipleModInventionFilesAreRead)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"),
		 {Mod("one", "ModInventions/Mod1"), Mod("two", "ModInventions/Mod2")});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_EQ("test_tech_five", inventions->getInventionName(5));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesOverrideDefaultOnes)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"),
		 {Mod("three", "ModInventions/Mod3")});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_EQ("replacement_tech_one", inventions->getInventionName(1));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesOverrideDependeeMods)
{
	const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("BaseGameInventions"),
		 {Mod("one", "ModInventions/Mod1"),
			  Mod("two", "ModInventions/Mod2"),
			  Mod("Mod3", "ModInventions/Mod3", std::set<Name>{"Mod2"})});
	const auto inventions = Vic2::Inventions::Factory().LoadInventions(mod_filesystem);

	ASSERT_EQ("replacement_tech_two", inventions->getInventionName(4));
}
#endif // _DEBUG