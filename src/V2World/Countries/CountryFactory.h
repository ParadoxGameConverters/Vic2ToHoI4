#ifndef COUNTRY_FACTORY_H
#define COUNTRY_FACTORY_H



#include "CommonCountryData.h"
#include "src/Configuration.h"
#include "Country.h"
#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Ai/AIFactory.h"
#include "src/V2World/Culture/CultureGroups.h"
#include "src/V2World/Diplomacy/RelationsFactory.h"
#include "src/V2World/EU4ToVic2Data/CountryData.h"
#include "src/V2World/Military/ArmyFactory.h"
#include "src/V2World/Military/Leaders/LeaderFactory.h"
#include "src/V2World/States/StateFactory.h"
#include "src/V2World/States/StateLanguageCategories.h"
#include "src/V2World/Stockpiles/StockpileFactory.h"
#include "src/V2World/Technology/Inventions.h"
#include "src/V2World/Technology/TechnologyFactory.h"
#include <memory>
#include <optional>



namespace Vic2
{

class Country::Factory: commonItems::parser
{
  public:
	Factory(const Configuration& theConfiguration,
		 const StateDefinitions& theStateDefinitions,
		 std::shared_ptr<CultureGroups> theCultureGroups_);
	std::unique_ptr<Country> createCountry(const std::string& theTag,
		 std::istream& theStream,
		 const CommonCountryData& commonCountryData,
		 const std::vector<Party>& allParties,
		 const StateLanguageCategories& stateLanguageCategories,
		 float percentOfCommanders,
		 const std::optional<CountryData>& countryData);

  private:
	void setParties(const std::vector<Party>& allParties);
	void limitCommanders(float percentOfCommanders);
	void setStateLanguageCategories(const StateLanguageCategories& stateLanguageCategories);

	std::shared_ptr<CultureGroups> theCultureGroups;
	std::unique_ptr<Inventions> theInventions;
	Relations::Factory relationsFactory;
	Army::Factory armyFactory;
	std::unique_ptr<Leader::Factory> leaderFactory;
	std::unique_ptr<State::Factory> stateFactory;
	TechnologyFactory technologyFactory;
	AI::Factory aiFactory;
	StockpileFactory stockpileFactory;

	std::unique_ptr<Country> country;
	unsigned int rulingPartyID;
};

} // namespace Vic2



#endif // COUNTRY_FACTORY_H