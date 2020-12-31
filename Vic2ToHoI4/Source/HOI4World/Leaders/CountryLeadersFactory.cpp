#include "CountryLeadersFactory.h"
#include "CommonRegexes.h"
#include "CountryLeaderFactory.h"
#include "ParserHelpers.h"



std::multimap<std::string, HoI4::CountryLeader> HoI4::CountryLeadersFactory::importCountryLeaders()
{
	CountryLeader::Factory leaderFactory;
	std::multimap<std::string, CountryLeader> countryLeaders;

	registerRegex(commonItems::catchallRegex,
		 [&countryLeaders, &leaderFactory](const std::string& tag, std::istream& theStream) {
			 const auto leader = leaderFactory.importCountryLeader(theStream);
			 countryLeaders.emplace(std::make_pair(tag, *leader));
		 });

	parseFile("./Configurables/HoI4CountryLeaders.txt");
	return countryLeaders;
}