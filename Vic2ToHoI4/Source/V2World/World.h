#ifndef VIC2_WORLD_H_
#define VIC2_WORLD_H_



#include "Configuration.h"
#include "Countries/Country.h"
#include "Diplomacy/Diplomacy.h"
#include "Localisations/Vic2Localisations.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mods/Mod.h"
#include "Parser.h"
#include "Provinces/Province.h"
#include "States/StateDefinitions.h"
#include "Wars/War.h"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class World: commonItems::parser
{
  public:
	World() = default;
	explicit World(const mappers::ProvinceMapper& provinceMapper, const Configuration& theConfiguration);
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	World(World&&) = delete;
	World& operator=(World&&) = delete;
	~World() = default;

	[[nodiscard]] std::optional<const std::shared_ptr<Province>> getProvince(int provNum) const;

	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getDiplomacy() const { return diplomacy; }
	[[nodiscard]] std::vector<std::string> getGreatPowers() const { return greatPowers; }
	[[nodiscard]] auto getProvinces() const { return provinces; }
	[[nodiscard]] const auto& getStateDefinitions() const { return *theStateDefinitions; }
	[[nodiscard]] const auto& getLocalisations() const { return *theLocalisations; }

  private:
	void setLocalisations(Localisations& vic2Localisations);
	void checkStateCategories();

	void setGreatPowerStatus(const std::vector<int>& GPIndexes, const std::vector<std::string>& tagsInOrder);

	void setProvinceOwners();
	void limitCommanders();
	void addProvinceCoreInfoToCountries();
	void removeSimpleLandlessNations();
	bool shouldCoreBeRemoved(const Province& core, const Country& country) const;
	void determineEmployedWorkers();
	void removeEmptyNations();
	void addWarsToCountries(const std::vector<War>& wars);

	void overallMergeNations(bool debug);
	void mergeNations(const std::string& masterTag, const std::vector<std::string>& slaveTags, bool debug);

	void checkAllProvincesMapped(const mappers::ProvinceMapper& provinceMapper) const;
	void consolidateConquerStrategies();

	std::map<int, std::shared_ptr<Province>> provinces;
	std::map<std::string, std::unique_ptr<Country>> countries;
	std::unique_ptr<Diplomacy> diplomacy;
	std::vector<std::string> greatPowers;

	std::unique_ptr<StateDefinitions> theStateDefinitions;
	std::unique_ptr<Localisations> theLocalisations;
};


} // namespace Vic2



#endif // VIC2_WORLD_H_