#include "Configuration.h"
#include "V2World/Localisations/LocalisationsFactory.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Mods/ModBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Localisations_LocalisationsTests, MissingKeyGivesNullopt)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_EQ(localisations->getTextInLanguage("bad_key", "english"), std::nullopt);
}


TEST(Vic2World_Localisations_LocalisationsTests, MissingLanguageGivesNullopt)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_EQ(localisations->getTextInLanguage("test_key", "bad_language"), std::nullopt);
}


TEST(Vic2World_Localisations_LocalisationsTests, MissingTextInAllLanguagesGivesEmptyMap)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_TRUE(localisations->getTextInEachLanguage("bad_key").empty());
}


TEST(Vic2World_Localisations_LocalisationsTests, TextInLanguageIsReturned)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_EQ(localisations->getTextInLanguage("test_key", "english"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "french"), "french_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "german"), "german_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "polish"), "polish_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "spanish"), "spanish_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "italian"), "italian_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "swedish"), "swedish_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "czech"), "czech_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "hungarian"), "hungarian_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "dutch"), "dutch_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "braz_por"), "braz_por_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "russian"), "russian_loc");
	ASSERT_EQ(localisations->getTextInLanguage("test_key", "finnish"), "finnish_loc");
}


TEST(Vic2World_Localisations_LocalisationsTests, MissingLocalisationsReplacedWithEnglish)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "english"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "french"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "german"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "polish"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "spanish"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "italian"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "swedish"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "czech"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "hungarian"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "dutch"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "braz_por"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "russian"), "english_loc");
	ASSERT_EQ(localisations->getTextInLanguage("replace_key", "finnish"), "english_loc");
}


TEST(Vic2World_Localisations_LocalisationsTests, TextInAllLanguagesTextInAllLanguages)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	const Vic2::LanguageToLocalisationMap expected{
		 {"english", "english_loc"},
		 {"french", "french_loc"},
		 {"german", "german_loc"},
		 {"polish", "polish_loc"},
		 {"spanish", "spanish_loc"},
		 {"italian", "italian_loc"},
		 {"swedish", "swedish_loc"},
		 {"czech", "czech_loc"},
		 {"hungarian", "hungarian_loc"},
		 {"dutch", "dutch_loc"},
		 {"braz_por", "braz_por_loc"},
		 {"russian", "russian_loc"},
		 {"finnish", "finnish_loc"},
	};
	ASSERT_EQ(expected, localisations->getTextInEachLanguage("test_key"));
}


TEST(Vic2World_Localisations_LocalisationsTests, LocalisationsCanBeLoadedFromMod)
{
	const auto configuration = Configuration::Builder{}
											 .setVic2Path("./")
											 .setVic2ModPath("./")
											 .addVic2Mod(*Vic2::Mod::Builder{}.setDirectory("ModLocalisations").build())
											 .build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "english"), "english_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "french"), "french_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "german"), "german_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "polish"), "polish_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "spanish"), "spanish_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "italian"), "italian_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "swedish"), "swedish_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "czech"), "czech_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "hungarian"), "hungarian_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "dutch"), "dutch_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "braz_por"), "braz_por_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "russian"), "russian_mod_loc");
	ASSERT_EQ(localisations->getTextInLanguage("mod_key", "finnish"), "finnish_mod_loc");
}


TEST(Vic2World_Localisations_LocalisationsTests, LocalisationsCanBeLoadedFromConverter)
{
	const auto configuration = Configuration::Builder{}.build();
	const auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "english"), "english_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "french"), "french_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "german"), "german_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "polish"), "polish_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "spanish"), "spanish_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "italian"), "italian_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "swedish"), "swedish_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "czech"), "czech_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "hungarian"), "hungarian_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "dutch"), "dutch_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "braz_por"), "braz_por_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "russian"), "russian_converter_loc");
	ASSERT_EQ(localisations->getTextInLanguage("converter_key", "finnish"), "finnish_converter_loc");
}