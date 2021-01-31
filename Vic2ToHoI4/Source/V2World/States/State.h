#ifndef VIC2_STATE_H_
#define VIC2_STATE_H_



#include "V2World/Provinces/Province.h"
#include "V2World/States/StateDefinitions.h"
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{

typedef struct workerStruct
{
	float craftsmen = 0;
	float clerks = 0;
	float artisans = 0;
	float capitalists = 0;
} workerStruct;


class State
{
  public:
	class Builder;
	class Factory;

	void determineEmployedWorkers();
	void eatState(const State& state, const StateDefinitions& stateDefinitions);

	void addProvince(std::shared_ptr<Province> province) { provinces.insert(std::move(province)); }
	void setOwner(std::string newOwner) { owner = std::move(newOwner); }
	void setLanguageCategory(std::string newLanguageCategory) { languageCategory = std::move(newLanguageCategory); }

	[[nodiscard]] int getPopulation() const;
	[[nodiscard]] float getAverageRailLevel() const;
	[[nodiscard]] std::optional<int> getUpperClassLocation() const;
	[[nodiscard]] std::vector<int> getProvincesOrderedByPopulation() const;
	[[nodiscard]] std::vector<std::pair<int, std::string>> getForeignControlledProvinces() const;
	[[nodiscard]] std::map<int, int> getNavalBases() const; // location, level

	[[nodiscard]] std::string getOwner() const { return owner; }
	[[nodiscard]] std::string getStateID() const { return stateID; }
	[[nodiscard]] bool isPartialState() const { return partialState; }
	[[nodiscard]] std::set<int> getProvinceNumbers() const { return provinceNumbers; }
	[[nodiscard]] std::set<std::shared_ptr<Province>> getProvinces() const { return provinces; }
	[[nodiscard]] std::optional<int> getCapitalProvince() const { return capitalProvince; }
	[[nodiscard]] const std::string& getLanguageCategory() const { return languageCategory; }
	[[nodiscard]] int getEmployedWorkers() const { return employedWorkers; }

  private:
	[[nodiscard]] workerStruct countEmployedWorkers() const;
	[[nodiscard]] workerStruct limitWorkersByFactoryLevels(const workerStruct& workers) const;
	[[nodiscard]] static int determineEmployedWorkersScore(const workerStruct& workers);

	std::string owner;
	std::string stateID;
	bool partialState = false;

	std::set<int> provinceNumbers;
	std::set<std::shared_ptr<Province>> provinces;
	std::optional<int> capitalProvince;

	std::string languageCategory;

	int factoryLevel = 0;
	int employedWorkers = 0;
};

} // namespace Vic2



#endif // VIC2_STATE_H_