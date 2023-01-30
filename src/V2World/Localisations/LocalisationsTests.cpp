#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Localisations/LocalisationsFactory.h"
#include "src/V2World/Localisations/Vic2Localisations.h"
#include <sstream>



TEST(Vic2World_Localisations_LocalisationsTests, MissingKeyGivesNullopt)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_EQ(std::nullopt, localisations->getTextInLanguage("bad_key", "english"));
}


TEST(Vic2World_Localisations_LocalisationsTests, MissingLanguageGivesNullopt)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_EQ(std::nullopt, localisations->getTextInLanguage("test_key", "bad_language"));
}


TEST(Vic2World_Localisations_LocalisationsTests, MissingTextInAllLanguagesGivesEmptyMap)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_TRUE(localisations->getTextInEachLanguage("bad_key").empty());
}


TEST(Vic2World_Localisations_LocalisationsTests, TextInLanguageIsReturned)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_EQ("english_loc", localisations->getTextInLanguage("test_key", "english"));
	ASSERT_EQ("french_loc", localisations->getTextInLanguage("test_key", "french"));
	ASSERT_EQ("german_loc", localisations->getTextInLanguage("test_key", "german"));
	ASSERT_EQ("polish_loc", localisations->getTextInLanguage("test_key", "polish"));
	ASSERT_EQ("spanish_loc", localisations->getTextInLanguage("test_key", "spanish"));
	ASSERT_EQ("italian_loc", localisations->getTextInLanguage("test_key", "italian"));
	ASSERT_EQ("swedish_loc", localisations->getTextInLanguage("test_key", "swedish"));
	ASSERT_EQ("czech_loc", localisations->getTextInLanguage("test_key", "czech"));
	ASSERT_EQ("hungarian_loc", localisations->getTextInLanguage("test_key", "hungarian"));
	ASSERT_EQ("dutch_loc", localisations->getTextInLanguage("test_key", "dutch"));
	ASSERT_EQ("braz_por_loc", localisations->getTextInLanguage("test_key", "braz_por"));
	ASSERT_EQ("russian_loc", localisations->getTextInLanguage("test_key", "russian"));
	ASSERT_EQ("finnish_loc", localisations->getTextInLanguage("test_key", "finnish"));
}


TEST(Vic2World_Localisations_LocalisationsTests, MissingLocalisationsReplacedWithEnglish)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "english"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "french"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "german"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "polish"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "spanish"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "italian"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "swedish"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "czech"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "hungarian"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "dutch"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "braz_por"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "russian"));
	ASSERT_EQ("english_loc", localisations->getTextInLanguage("replace_key", "finnish"));
}


TEST(Vic2World_Localisations_LocalisationsTests, TextInAllLanguagesTextInAllLanguages)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

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
	const commonItems::ModFilesystem mod_filesystem("./", {Mod("Mod Locs", "modLocalisations/")});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_EQ("english_mod_loc", localisations->getTextInLanguage("mod_key", "english"));
	ASSERT_EQ("french_mod_loc", localisations->getTextInLanguage("mod_key", "french"));
	ASSERT_EQ("german_mod_loc", localisations->getTextInLanguage("mod_key", "german"));
	ASSERT_EQ("polish_mod_loc", localisations->getTextInLanguage("mod_key", "polish"));
	ASSERT_EQ("spanish_mod_loc", localisations->getTextInLanguage("mod_key", "spanish"));
	ASSERT_EQ("italian_mod_loc", localisations->getTextInLanguage("mod_key", "italian"));
	ASSERT_EQ("swedish_mod_loc", localisations->getTextInLanguage("mod_key", "swedish"));
	ASSERT_EQ("czech_mod_loc", localisations->getTextInLanguage("mod_key", "czech"));
	ASSERT_EQ("hungarian_mod_loc", localisations->getTextInLanguage("mod_key", "hungarian"));
	ASSERT_EQ("dutch_mod_loc", localisations->getTextInLanguage("mod_key", "dutch"));
	ASSERT_EQ("braz_por_mod_loc", localisations->getTextInLanguage("mod_key", "braz_por"));
	ASSERT_EQ("russian_mod_loc", localisations->getTextInLanguage("mod_key", "russian"));
	ASSERT_EQ("finnish_mod_loc", localisations->getTextInLanguage("mod_key", "finnish"));
}


TEST(Vic2World_Localisations_LocalisationsTests, LocalisationsCanBeLoadedFromConverter)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	const auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_EQ("english_converter_loc", localisations->getTextInLanguage("converter_key", "english"));
	ASSERT_EQ("french_converter_loc", localisations->getTextInLanguage("converter_key", "french"));
	ASSERT_EQ("german_converter_loc", localisations->getTextInLanguage("converter_key", "german"));
	ASSERT_EQ("polish_converter_loc", localisations->getTextInLanguage("converter_key", "polish"));
	ASSERT_EQ("spanish_converter_loc", localisations->getTextInLanguage("converter_key", "spanish"));
	ASSERT_EQ("italian_converter_loc", localisations->getTextInLanguage("converter_key", "italian"));
	ASSERT_EQ("swedish_converter_loc", localisations->getTextInLanguage("converter_key", "swedish"));
	ASSERT_EQ("czech_converter_loc", localisations->getTextInLanguage("converter_key", "czech"));
	ASSERT_EQ("hungarian_converter_loc", localisations->getTextInLanguage("converter_key", "hungarian"));
	ASSERT_EQ("dutch_converter_loc", localisations->getTextInLanguage("converter_key", "dutch"));
	ASSERT_EQ("braz_por_converter_loc", localisations->getTextInLanguage("converter_key", "braz_por"));
	ASSERT_EQ("russian_converter_loc", localisations->getTextInLanguage("converter_key", "russian"));
	ASSERT_EQ("finnish_converter_loc", localisations->getTextInLanguage("converter_key", "finnish"));
}


TEST(Vic2World_Localisations_LocalisationsTests, RegionTextCanBeReplaced)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);
	localisations->updateDomainCountry("TAG", "Replace Region");

	ASSERT_EQ("Localisation for Replace Region replacement English", localisations->getTextInLanguage("TAG", "english"));
	ASSERT_EQ("Localisation for Replace Region replacement French", localisations->getTextInLanguage("TAG", "french"));
	ASSERT_EQ("Localisation for Replace Region replacement German", localisations->getTextInLanguage("TAG", "german"));
	ASSERT_EQ("Localisation for Replace Region replacement Polish", localisations->getTextInLanguage("TAG", "polish"));
	ASSERT_EQ("Localisation for Replace Region replacement Spanish", localisations->getTextInLanguage("TAG", "spanish"));
	ASSERT_EQ("Localisation for Replace Region replacement Italian", localisations->getTextInLanguage("TAG", "italian"));
	ASSERT_EQ("Localisation for Replace Region replacement Swedish", localisations->getTextInLanguage("TAG", "swedish"));
	ASSERT_EQ("Localisation for Replace Region replacement Czech", localisations->getTextInLanguage("TAG", "czech"));
	ASSERT_EQ("Localisation for Replace Region replacement Hungarian",
		 localisations->getTextInLanguage("TAG", "hungarian"));
	ASSERT_EQ("Localisation for Replace Region replacement Dutch", localisations->getTextInLanguage("TAG", "dutch"));
	ASSERT_EQ("Localisation for Replace Region replacement Brazilian",
		 localisations->getTextInLanguage("TAG", "braz_por"));
	ASSERT_EQ("Localisation for Replace Region replacement Russian", localisations->getTextInLanguage("TAG", "russian"));
	ASSERT_EQ("Localisation for Replace Region replacement Finnish", localisations->getTextInLanguage("TAG", "finnish"));
}


TEST(Vic2World_Localisations_LocalisationsTests, ReplacementRegionTextCanBeFromLocalisation)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);
	localisations->updateDomainCountry("TAG", "Replacement Region English");

	ASSERT_EQ("Localisation for Replacement Region English replacement English",
		 localisations->getTextInLanguage("TAG", "english"));
	ASSERT_EQ("Localisation for Replacement Region French replacement French",
		 localisations->getTextInLanguage("TAG", "french"));
	ASSERT_EQ("Localisation for Replacement Region German replacement German",
		 localisations->getTextInLanguage("TAG", "german"));
	ASSERT_EQ("Localisation for Replacement Region Polish replacement Polish",
		 localisations->getTextInLanguage("TAG", "polish"));
	ASSERT_EQ("Localisation for Replacement Region Spanish replacement Spanish",
		 localisations->getTextInLanguage("TAG", "spanish"));
	ASSERT_EQ("Localisation for Replacement Region Italian replacement Italian",
		 localisations->getTextInLanguage("TAG", "italian"));
	ASSERT_EQ("Localisation for Replacement Region Swedish replacement Swedish",
		 localisations->getTextInLanguage("TAG", "swedish"));
	ASSERT_EQ("Localisation for Replacement Region Czech replacement Czech",
		 localisations->getTextInLanguage("TAG", "czech"));
	ASSERT_EQ("Localisation for Replacement Region Hungarian replacement Hungarian",
		 localisations->getTextInLanguage("TAG", "hungarian"));
	ASSERT_EQ("Localisation for Replacement Region Dutch replacement Dutch",
		 localisations->getTextInLanguage("TAG", "dutch"));
	ASSERT_EQ("Localisation for Replacement Region Brazilian replacement Brazilian",
		 localisations->getTextInLanguage("TAG", "braz_por"));
	ASSERT_EQ("Localisation for Replacement Region Russian replacement Russian",
		 localisations->getTextInLanguage("TAG", "russian"));
	ASSERT_EQ("Localisation for Replacement Region Finnish replacement Finnish",
		 localisations->getTextInLanguage("TAG", "finnish"));
}


TEST(Vic2World_Localisations_LocalisationsTests, UpdateDomainCountrySkipsMissingTag)
{
	const commonItems::ModFilesystem mod_filesystem("./", {});
	auto localisations = Vic2::Localisations::Factory().ImportLocalisations(mod_filesystem);

	ASSERT_NO_THROW(localisations->updateDomainCountry("NON", "Replacement Region English"));
}