#ifndef WORLD_FACTORY_H
#define WORLD_FACTORY_H



#include "Configuration.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Parser.h"
#include "V2World/Countries/CountryFactory.h"
#include "V2World/Culture/CultureGroups.h"
#include "V2World/Diplomacy/DiplomacyFactory.h"
#include "V2World/Issues/Issues.h"
#include "V2World/Provinces/ProvinceFactory.h"
#include "V2World/Wars/WarFactory.h"
#include "World.h"
#include <memory>



namespace Vic2
{

class World::Factory: commonItems::parser
{
  public:
	explicit Factory(const Configuration& theConfiguration);
	std::unique_ptr<World> importWorld(const Configuration& theConfiguration,
		 const mappers::ProvinceMapper& provinceMapper);

  private:
	void setLocalisations(Localisations& vic2Localisations);
	void setGreatPowerStatus();
	void setProvinceOwners();
	void addProvinceCoreInfoToCountries();
	void removeSimpleLandlessNations();
	[[nodiscard]] bool shouldCoreBeRemoved(const Province& core, const Country& country) const;
	void determineEmployedWorkers();
	void removeEmptyNations();
	void addWarsToCountries(const std::vector<War>& wars);
	void overallMergeNations(bool debug);
	void mergeNations(const std::string& masterTag, const std::vector<std::string>& slaveTags, bool debug);
	void checkAllProvincesMapped(const mappers::ProvinceMapper& provinceMapper) const;
	void consolidateConquerStrategies();
	void removeBattles();
	[[nodiscard]] std::map<int, std::vector<Army*>> determineArmyLocations() const;
	[[nodiscard]] static bool armiesHaveDifferentOwners(const std::vector<Army*>& armies);

	std::unique_ptr<World> world;

	std::vector<int> greatPowerIndexes;
	std::vector<std::string> tagsInOrder;
	std::vector<War> wars;

	std::shared_ptr<CultureGroups> theCultureGroups;
	std::unique_ptr<Issues> theIssues;
	std::unique_ptr<Province::Factory> provinceFactory;
	War::Factory warFactory;
	std::unique_ptr<StateDefinitions> theStateDefinitions;
	std::unique_ptr<Country::Factory> countryFactory;
	std::unique_ptr<StateLanguageCategories> stateLanguageCategories;
	std::unique_ptr<Diplomacy::Factory> diplomacyFactory;
	std::map<std::string, CommonCountryData> commonCountriesData;
	std::vector<Party> allParties;
};
} // namespace Vic2



#endif // WORLD_FACTORY_H