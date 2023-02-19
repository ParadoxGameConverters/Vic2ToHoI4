#ifndef WORLD_FACTORY_H
#define WORLD_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/V2World/Countries/CountryFactory.h"
#include "src/V2World/Culture/CultureGroups.h"
#include "src/V2World/Diplomacy/DiplomacyFactory.h"
#include "src/V2World/EU4ToVic2Data/CountriesDataFactory.h"
#include "src/V2World/Issues/Issues.h"
#include "src/V2World/Provinces/ProvinceFactory.h"
#include "src/V2World/Wars/WarFactory.h"
#include "src/V2World/World/World.h"
#include <memory>



namespace Vic2
{

class World::Factory: commonItems::parser
{
  public:
	explicit Factory(const commonItems::ModFilesystem& mod_filesystem, float percentage_of_commanders);
	std::unique_ptr<World> importWorld(const Configuration& theConfiguration,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const commonItems::ModFilesystem& mod_filesystem);

  private:
	void setLocalisations(Localisations& vic2Localisations);
	void setGreatPowerStatus();
	void setProvinceOwners();
	void addProvinceCoreInfoToCountries();
	void removeSimpleLandlessNations(removeCoresOptions option);
	[[nodiscard]] bool shouldCoreBeRemoved(const Province& core,
		 const Country& country,
		 removeCoresOptions option) const;
	void determineEmployedWorkers();
	void RecordUnionCountries(const CultureGroups& culture_groups);
	void removeEmptyNations();
	void consolidatePartialStates();
	void addWarsToCountries(const std::vector<War>& wars);
	void overallMergeNations(bool debug);
	void mergeNations(const std::string& masterTag, const std::vector<std::string>& slaveTags, bool debug);
	void checkAllProvincesMapped(const Mappers::ProvinceMapper& provinceMapper, const Mods& vic2Mods) const;
	void consolidateConquerStrategies();
	void moveArmiesHome();
	void removeBattles();
	void ImportMapData(const commonItems::ModFilesystem& mod_filesystem);
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

	std::unique_ptr<CountriesData> countriesData;
};

} // namespace Vic2



#endif // WORLD_FACTORY_H