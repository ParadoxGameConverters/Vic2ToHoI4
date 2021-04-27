#include "Configuration.h"
#include "V2World/Mods/ModBuilder.h"
#include "V2World/Technology/Inventions.h"
#include "V2World/Technology/InventionsFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Technology_InventionTests, MissingInventionLogsErrorAndReturnsNullopt)
{
	const auto inventions = Vic2::Inventions{};

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
	const auto inventions = Vic2::Inventions{};

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
	const auto configuration = Configuration::Builder{}.setVic2Path("./BaseGameInventions").build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_one", inventions->getInventionName(1));
}


TEST(Vic2World_Technology_InventionTests, AllInventionFilesAreRead)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./BaseGameInventions").build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_one", inventions->getInventionName(1));
	ASSERT_EQ("test_tech_two", inventions->getInventionName(2));
}


TEST(Vic2World_Technology_InventionTests, InventionsWithAtypicalCharactersAreReturned)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./BaseGameInventions").build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_NE(std::nullopt, inventions->getInventionName(3));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesAreRead)
{
	const auto configuration = Configuration::Builder{}
											 .setVic2Path("./BaseGameInventions")
											 .setVic2ModPath(".")
											 .addVic2Mod(*Vic2::Mod::Builder{}.setDirectory("ModInventions/Mod1").build())
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_four", inventions->getInventionName(4));
}


TEST(Vic2World_Technology_InventionTests, MultipleModInventionFilesAreRead)
{
	const auto configuration = Configuration::Builder{}
											 .setVic2Path("./BaseGameInventions")
											 .setVic2ModPath(".")
											 .addVic2Mod(*Vic2::Mod::Builder{}.setDirectory("ModInventions/Mod1").build())
											 .addVic2Mod(*Vic2::Mod::Builder{}.setDirectory("ModInventions/Mod2").build())
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("test_tech_five", inventions->getInventionName(5));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesOverrideDefaultOnes)
{
	const auto configuration = Configuration::Builder{}
											 .setVic2Path("./BaseGameInventions")
											 .setVic2ModPath(".")
											 .addVic2Mod(*Vic2::Mod::Builder{}.setDirectory("ModInventions/Mod3").build())
											 .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("replacement_tech_one", inventions->getInventionName(1));
}


TEST(Vic2World_Technology_InventionTests, ModInventionFilesOverrideDependeeMods)
{
	const auto configuration =
		 Configuration::Builder{}
			  .setVic2Path("./BaseGameInventions")
			  .setVic2ModPath(".")
			  .addVic2Mod(*Vic2::Mod::Builder{}.setName("Mod1").setDirectory("ModInventions/Mod1").build())
			  .addVic2Mod(
					*Vic2::Mod::Builder{}.setName("Mod2").setDirectory("ModInventions/Mod2").addDependency("Mod1").build())
			  .addVic2Mod(
					*Vic2::Mod::Builder{}.setName("Mod3").setDirectory("ModInventions/Mod3").addDependency("Mod2").build())
			  .build();
	const auto inventions = Vic2::Inventions::Factory().loadInventions(*configuration);

	ASSERT_EQ("replacement_tech_two", inventions->getInventionName(4));
}
#endif // _DEBUG