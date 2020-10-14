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


TEST(Vic2World_Localisations_LocalisationsTests, RegionTextCanBeReplaced)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);
	localisations->updateDomainCountry("TAG", "Replace Region");

	ASSERT_EQ(localisations->getTextInLanguage("TAG", "english"), "Localisation for Replace Region replacement English");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "french"), "Localisation for Replace Region replacement French");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "german"), "Localisation for Replace Region replacement German");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "polish"), "Localisation for Replace Region replacement Polish");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "spanish"), "Localisation for Replace Region replacement Spanish");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "italian"), "Localisation for Replace Region replacement Italian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "swedish"), "Localisation for Replace Region replacement Swedish");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "czech"), "Localisation for Replace Region replacement Czech");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "hungarian"),
		 "Localisation for Replace Region replacement Hungarian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "dutch"), "Localisation for Replace Region replacement Dutch");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "braz_por"),
		 "Localisation for Replace Region replacement Brazilian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "russian"), "Localisation for Replace Region replacement Russian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "finnish"), "Localisation for Replace Region replacement Finnish");
}


TEST(Vic2World_Localisations_LocalisationsTests, ReplacementRegionTextCanBeFromLocalisation)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);
	localisations->updateDomainCountry("TAG", "Replacement Region English");

	ASSERT_EQ(localisations->getTextInLanguage("TAG", "english"),
		 "Localisation for Replacement Region English replacement English");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "french"),
		 "Localisation for Replacement Region French replacement French");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "german"),
		 "Localisation for Replacement Region German replacement German");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "polish"),
		 "Localisation for Replacement Region Polish replacement Polish");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "spanish"),
		 "Localisation for Replacement Region Spanish replacement Spanish");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "italian"),
		 "Localisation for Replacement Region Italian replacement Italian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "swedish"),
		 "Localisation for Replacement Region Swedish replacement Swedish");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "czech"),
		 "Localisation for Replacement Region Czech replacement Czech");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "hungarian"),
		 "Localisation for Replacement Region Hungarian replacement Hungarian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "dutch"),
		 "Localisation for Replacement Region Dutch replacement Dutch");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "braz_por"),
		 "Localisation for Replacement Region Brazilian replacement Brazilian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "russian"),
		 "Localisation for Replacement Region Russian replacement Russian");
	ASSERT_EQ(localisations->getTextInLanguage("TAG", "finnish"),
		 "Localisation for Replacement Region Finnish replacement Finnish");
}


TEST(Vic2World_Localisations_LocalisationsTests, UpdateDomainCountrySkipsMissingTag)
{
	const auto configuration = Configuration::Builder{}.setVic2Path("./").build();
	auto localisations = Vic2::Localisations::Factory{}.importLocalisations(*configuration);

	ASSERT_NO_THROW(localisations->updateDomainCountry("NON", "Replacement Region English"));
}