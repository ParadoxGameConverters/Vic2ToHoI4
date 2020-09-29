#ifndef VIC2_WORLD_H_
#define VIC2_WORLD_H_



#include "Culture/CultureGroups.h"
#include "Diplomacy/Diplomacy.h"
#include "Mods/Mod.h"
#include "Parser.h"
#include "Politics/Party.h"
#include "States/StateDefinitions.h"
#include "Wars/War.h"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>



namespace mappers
{
class ProvinceMapper;
}


namespace Vic2
{
class Country;
class Localisations;
class Party;
class Province;


class World: commonItems::parser
{
  public:
	World() = default;
	explicit World(const mappers::ProvinceMapper& provinceMapper, const Configuration& theConfiguration);
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	World(World&&) = delete;
	World& operator=(World&&) = delete;
	virtual ~World() = default;

	[[nodiscard]] std::optional<const std::shared_ptr<Province>> getProvince(int provNum) const;

	[[nodiscard]] std::map<std::string, Country*> getCountries() const { return countries; }
	[[nodiscard]] const auto& getDiplomacy() const { return diplomacy; }
	[[nodiscard]] std::vector<std::string> getGreatPowers() const { return greatPowers; }
	[[nodiscard]] auto getProvinces() const { return provinces; }
	[[nodiscard]] const auto& getStateDefinitions() const { return *theStateDefinitions; }
	[[nodiscard]] const auto& getLocalisations() const { return *theLocalisations; }

  private:
	void setLocalisations(Localisations& vic2Localisations);
	void checkStateCategories();
	void handleMissingCountryCultures();

	void setGreatPowerStatus(const std::vector<int>& GPIndexes, const std::vector<std::string>& tagsInOrder);

	void setProvinceOwners();
	void addProvinceCoreInfoToCountries();
	void removeSimpleLandlessNations();
	bool shouldCoreBeRemoved(const Province& core, const Country* country) const;
	void determineEmployedWorkers();
	void removeEmptyNations();
	void addWarsToCountries(const std::vector<War>& wars);

	void overallMergeNations(bool debug);
	void mergeNations(const std::string& masterTag, const std::vector<std::string>& slaveTags, bool debug);

	void checkAllProvincesMapped(const mappers::ProvinceMapper& provinceMapper) const;

	void readCountryFiles(const Configuration& theConfiguration);
	bool processCountriesDotTxt(const std::string& countryListFile,
		 const std::optional<Vic2::Mod>& mod,
		 const Configuration& theConfiguration);
	static bool shouldLineBeSkipped(const std::string& line);
	static std::string extractCountryFileName(const std::string& countryFileLine);

	[[nodiscard]] std::optional<Country*> getCountry(const std::string& tag) const;


	std::map<int, std::shared_ptr<Province>> provinces;
	std::map<std::string, Country*> countries;
	std::unique_ptr<Diplomacy> diplomacy;
	std::vector<std::string> greatPowers;

	std::unique_ptr<CultureGroups> theCultureGroups;

	std::unique_ptr<StateDefinitions> theStateDefinitions;
	std::unique_ptr<Localisations> theLocalisations;
};


} // namespace Vic2



#endif // VIC2_WORLD_H_