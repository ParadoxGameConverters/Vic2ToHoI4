#include "Configuration.h"
#include "V2World/Countries/CommonCountryDataBuilder.h"
#include "V2World/Countries/Country.h"
#include "V2World/Countries/CountryFactory.h"
#include "V2World/States/StateDefinitionsBuilder.h"
#include "V2World/Politics/PartyBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Countries_CountryTests, tagIsAsSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\truling_party = 1";
	theStream << "}";
	const auto country = Vic2::Country::Factory
	{*Configuration::Builder{}.setVic2Path("./countries/blank/").build(), *Vic2::StateDefinitions::Builder{}.build()}
			  .createCountry(
					"TAG",
					theStream,
					*Vic2::CommonCountryData::Builder{}.Build(),
					std::vector<Vic2::Party> { *Vic2::Party::Builder{}.Build() });

	ASSERT_EQ("TAG", country->getTag());
}