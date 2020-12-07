#ifndef COUNTRY_FACTORY_H
#define COUNTRY_FACTORY_H



#include "CommonCountryData.h"
#include "Configuration.h"
#include "Country.h"
#include "Parser.h"
#include "V2World/Culture/CultureGroups.h"
#include "V2World/Diplomacy/RelationsFactory.h"
#include "V2World/Military/ArmyFactory.h"
#include "V2World/Military/Leaders/LeaderFactory.h"
#include "V2World/States/StateFactory.h"
#include "V2World/Technology/Inventions.h"
#include <memory>



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
		 const std::vector<Party>& allParties);

  private:
	void setParties(const std::vector<Party>& allParties);
	void limitCommanders();

	std::shared_ptr<CultureGroups> theCultureGroups;
	std::unique_ptr<Inventions> theInventions;
	Relations::Factory relationsFactory;
	Army::Factory armyFactory;
	std::unique_ptr<Leader::Factory> leaderFactory;
	std::unique_ptr<State::Factory> stateFactory;

	std::unique_ptr<Country> country;
};

} // namespace Vic2



#endif // COUNTRY_FACTORY_H