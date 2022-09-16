#ifndef HOI4STATE_H
#define HOI4STATE_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/CoastalProvinces.h"
#include "src/HOI4World/States/StateCategories.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/V2World/Provinces/Province.h"
#include "src/V2World/States/State.h"
#include <map>
#include <optional>
#include <set>
#include <string>



namespace HoI4
{

class State
{
  public:
	State() = default;
	State(const Vic2::State& sourceState, int _ID, const std::string& _ownerTag);
	~State() = default;

	class Builder;

	void addProvince(int province) { provinces.insert(province); }
	void setAsCapitalState()
	{
		capitalState = true;
		civFactories++;
	}
	void makeImpassable()
	{
		impassable = true;
		infrastructure = 0;
	}
	void markHadImpassablePart() { hadImpassablePart = true; }
	void addResource(const std::string& resource, double amount) { resources[resource] += amount; }
	void addAirBase(int newAirBase)
	{
		airbaseLevel += newAirBase;
		if (airbaseLevel > 10)
			airbaseLevel = 10;
	}
	void addVictoryPointValue(int additionalValue) { victoryPointValue += additionalValue; }
	void setVPValue(int value) { victoryPointValue = value; }
	void setVPLocation(int province) { victoryPointPosition = province; }
	void setOwnerAveragePopPerProvince(int ownerAvrgPopPerProv_) { ownerAvrgPopPerProvince = ownerAvrgPopPerProv_; }
	void setAveragePopPerProvince(int avrgPopPerProv_) { avrgPopPerProvince = avrgPopPerProv_; }
	void finishInfrastructureConversion();
	void convertNavalBases(const std::map<int, int>& sourceNavalBases,
		 const CoastalProvinces& theCoastalProvinces,
		 const Mappers::ProvinceMapper& theProvinceMapper);
	void addNavalBase(int level, int location);
	void smashNavalBases();
	void addCores(const std::set<std::string>& newCores);
	void removeCore(const std::string& theCore) { cores.erase(theCore); }
	void addClaims(const std::set<std::string>& newClaims);
	void convertControlledProvinces(const std::vector<std::pair<int, std::string>>& foreignControlledProvinces,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const Mappers::CountryMapper& countryMapper);
	void removeControlledProvince(int provinceNum);
	void setControlledProvince(int provinceNum, const std::string& country);
	void setOwner(std::string newOwner) { ownerTag = std::move(newOwner); }

	int getID() const { return ID; }
	const std::set<int>& getProvinces() const { return provinces; }
	const int& getPopulation() const { return population; }
	const std::string& getOwner() const { return ownerTag; }
	const std::set<std::string>& getCores() const { return cores; }
	[[nodiscard]] const auto& getClaims() const { return claims; }
	const std::map<std::string, std::set<int>>& getControlledProvinces() const { return controlledProvinces; }
	bool isImpassable() const { return impassable; }
	int getDockyards() const { return dockyards; }
	int getCivFactories() const { return civFactories; }
	int getMilFactories() const { return milFactories; }
	const std::string& getCategory() const { return category; }
	[[nodiscard]] auto getInfrastructure() const { return infrastructure; }
	const std::map<int, int>& getNavalBases() const { return navalBases; }
	int getAirbaseLevel() const { return airbaseLevel; }
	bool hasResources() const { return !resources.empty(); }
	const std::map<std::string, double>& getResources() const { return resources; }
	std::optional<int> getVPLocation() const { return victoryPointPosition; }
	int getVpValue() const { return victoryPointValue; }
	const std::set<int>& getDebugVPs() const { return debugVictoryPoints; }
	const std::set<int>& getSecondaryDebugVPs() const { return secondaryDebugVictoryPoints; }
	[[nodiscard]] bool IsCapitalState() const { return capitalState; }

	std::optional<int> getMainNavalLocation() const;
	[[nodiscard]] int getManpower() const;

	void tryToCreateVP(const Vic2::State& sourceState,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const Configuration& theConfiguration);
	void addManpower(const std::vector<std::shared_ptr<Vic2::Province>>& sourceProvinces,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const Configuration& theConfiguration);

	void convertIndustry(double workerFactoryRatio,
		 int ownerIndustryRemainder,
		 const HoI4::StateCategories& theStateCategories,
		 const CoastalProvinces& theCoastalProvinces);
	[[nodiscard]] const auto& getEmployedWorkers() const { return employedWorkers; }
	[[nodiscard]] int getIndustryRemainder() const { return industryRemainder; }

  private:
	int determineFactoryNumbers(double workerFactoryRatio, int ownerIndustryRemainder);
	int constrainFactoryNumbers(double rawFactories);
	void determineCategory(int factories, const HoI4::StateCategories& theStateCategories);
	void addInfrastructureFromRails(float averageRailLevel);
	void addInfrastructureFromFactories(int factories);
	void setIndustry(int factories, const CoastalProvinces& theCoastalProvinces);
	bool amICoastal(const CoastalProvinces& theCoastalProvinces) const;
	[[nodiscard]] bool ownerHasNoCore() const;

	static int determineNavalBaseLevel(int sourceLevel);
	static std::optional<int> determineNavalBaseLocation(int sourceProvince,
		 const CoastalProvinces& theCoastalProvinces,
		 const Mappers::ProvinceMapper& theProvinceMapper);

	bool assignVPFromVic2Province(int Vic2ProvinceNumber, const Mappers::ProvinceMapper& theProvinceMapper);
	void assignVP(int location);
	bool isProvinceInState(int provinceNum) const;
	void addDebugVPs(const Vic2::State& sourceState, const Mappers::ProvinceMapper& theProvinceMapper);

	int population = 0;
	long employedWorkers = 0;

	int ID = 0;
	std::set<int> provinces;
	std::string ownerTag;
	std::optional<int> ownerAvrgPopPerProvince = 0;
	int avrgPopPerProvince = 0;
	std::set<std::string> cores;
	std::set<std::string> claims;
	std::map<std::string, std::set<int>> controlledProvinces;

	bool capitalState = false;
	bool impassable = false;
	bool hadImpassablePart = false;

	int manpower = 0;

	int civFactories = 0;
	int milFactories = 0;
	int dockyards = 0;
	int industryRemainder = 0;
	std::string category = "wasteland";
	float infrastructure = 1.0F;

	std::map<int, int> navalBases;

	int airbaseLevel = 0;

	std::map<std::string, double> resources;

	std::optional<int> victoryPointPosition;
	int victoryPointValue = 0;
	std::set<int> debugVictoryPoints;
	std::set<int> secondaryDebugVictoryPoints;

	std::map<int, int> landFortLevels;
	std::map<int, int> coastFortLevels;
};

} // namespace HoI4



#endif // HOI4STATE_H