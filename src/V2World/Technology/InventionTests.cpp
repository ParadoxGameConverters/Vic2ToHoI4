#include "src/Configuration.h"
#include "src/V2World/Technology/Inventions.h"
#include "src/V2World/Technology/InventionsFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(Vic2World_Technology_InventionTests, MissingInventionLogsErrorAndReturnsNullopt)
{
	const auto inventions = Vic2::Inventions();

	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto inventionName = inventions.getInventionName(1);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] Invalid invention. Is this using a mod that changed inventions?\n", log.str());
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

	ASSERT_EQ(" [WARNING] Invalid invention zero.\n", log.str());
	ASSERT_EQ(std::nullopt, inventionName);
}


#ifndef _DEBUG // disable some test that break code coverage
TEST(Vic2World_Technology_InventionTests, InventionNameIsReturned)
{
	const auto configuration = Configuration::Builder().setVic2Path("./BaseGameInventions").build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_one", inventions->getInventionName(1));
}


TEST(Vic2World_Technology_InventionTests, AllInventionFilesAreRead)
{
	const auto configuration = Configuration::Builder().setVic2Path("./BaseGameInventions").build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_one", inventions->getInventionName(1));
	ASSERT_EQ("test_tech_two", inventions->getInventionName(2));
}


TEST(Vic2World_Technology_InventionTests, InventionsWithAtypicalCharactersAreReturned)
{
	const auto configuration = Configuration::Builder().setVic2Path("./BaseGameInventions").build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_NE(std::nullopt, inventions->getInventionName(3));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesAreRead)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./BaseGameInventions")
											 .addVic2Mod(Mod("one", "ModInventions/Mod1"))
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_four", inventions->getInventionName(4));
}


TEST(Vic2World_Technology_InventionTests, MultipleModInventionFilesAreRead)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./BaseGameInventions")
											 .addVic2Mod(Mod("one", "ModInventions/Mod1"))
											 .addVic2Mod(Mod("two", "ModInventions/Mod2"))
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_five", inventions->getInventionName(5));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesOverrideDefaultOnes)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./BaseGameInventions")
											 .addVic2Mod(Mod("three", "ModInventions/Mod3"))
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("replacement_tech_one", inventions->getInventionName(1));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesOverrideDependeeMods)
{
	const auto configuration = Configuration::Builder()
											 .setVic2Path("./BaseGameInventions")
											 .addVic2Mod(Mod("Mod1", "ModInventions/Mod1"))
											 .addVic2Mod(Mod("Mod2", "ModInventions/Mod2", std::set<Name>{"Mod1"}))
											 .addVic2Mod(Mod("Mod3", "ModInventions/Mod3", std::set<Name>{"Mod2"}))
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("replacement_tech_two", inventions->getInventionName(4));
}
#endif // _DEBUG