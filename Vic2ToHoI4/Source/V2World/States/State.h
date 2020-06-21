#ifndef VIC2_STATE_H_
#define VIC2_STATE_H_



#include <memory>
#include <optional>
#include <set>
#include <string>



namespace Vic2
{
class StateDefinitions;

class Province;



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
	class Factory;
	State() = default;
	State(const State&) = default;
	State(State&&) = default;
	State& operator=(const State&) = default;
	State& operator=(State&&) = default;
	virtual ~State() = default;

	void determineEmployedWorkers();

	void addProvince(std::shared_ptr<Province> province) { provinces.insert(std::move(province)); }
	void setOwner(std::string newOwner) { owner = std::move(newOwner); }

	[[nodiscard]] virtual int getPopulation() const;
	[[nodiscard]] virtual float getAverageRailLevel() const;

	[[nodiscard]] std::string getOwner() const { return owner; }
	[[nodiscard]] std::string getStateID() const { return stateID; }
	[[nodiscard]] bool isPartialState() const { return partialState; }
	[[nodiscard]] virtual std::set<int> getProvinceNumbers() const { return provinceNumbers; }
	[[nodiscard]] virtual std::set<std::shared_ptr<Province>> getProvinces() const { return provinces; }
	[[nodiscard]] virtual std::optional<int> getCapitalProvince() const { return capitalProvince; }
	[[nodiscard]] virtual int getEmployedWorkers() const { return employedWorkers; }

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

	int factoryLevel = 0;
	int employedWorkers = 0;
};

} // namespace Vic2



#endif // VIC2_STATE_H_
