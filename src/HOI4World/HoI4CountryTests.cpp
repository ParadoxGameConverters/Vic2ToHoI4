#include "external/common_items/Date.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/CharacterFactory.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/HoI4Localisation.h"
#include "src/HOI4World/Names/Names.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "src/Mappers/Graphics/GraphicsMapper.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"


class CountryTest: public ::testing::Test
{
  protected:
	void SetUp() override
	{
		country = std::make_unique<HoI4::Country>(tag,
			 sourceCountry,
			 names,
			 graphicsMapper,
			 countryMapper,
			 flagsToIdeasMapper,
			 localisation,
			 startDate,
			 provinceMapper,
			 worldStates,
			 characterFactory);
	}

	std::string tag = "TAG";
	Vic2::Country sourceCountry;
	HoI4::Names names{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
	Mappers::GraphicsMapper graphicsMapper;
	Mappers::CountryMapper countryMapper;
	Mappers::FlagsToIdeasMapper flagsToIdeasMapper;
	HoI4::Localisation localisation{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
	date startDate{"1936.1.1"};
	Mappers::ProvinceMapper provinceMapper;
	HoI4::States worldStates;
	HoI4::Character::Factory characterFactory;

	std::unique_ptr<HoI4::Country> country;
};

TEST_F(CountryTest, CharacterFlagIsSetCorrectly)
{
	country->setCharacterFlag("test_character", "test_flag");

	const auto& flags = country->getCharacterFlags();
	ASSERT_TRUE(flags.contains("test_character"));
	EXPECT_EQ("test_flag", flags.at("test_character"));
}