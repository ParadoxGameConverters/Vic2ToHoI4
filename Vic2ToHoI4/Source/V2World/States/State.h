#ifndef VIC2_STATE_H_
#define VIC2_STATE_H_



#include "Parser.h"
#include <set>
#include <vector>



namespace Vic2
{
class StateDefinitions;

class Province;



typedef struct workerStruct
{
	int craftsmen = 0;
	int clerks = 0;
	int artisans = 0;
	int capitalists = 0;
} workerStruct;



class State: commonItems::parser
{
  public:
	class Factory;
	State() = default;
	virtual ~State() = default;

	void determineEmployedWorkers();

	virtual int getPopulation() const;
	virtual float getAverageRailLevel() const;

	void addProvince(std::shared_ptr<Province> province) { provinces.insert(province); }
	void setOwner(std::string newOwner) { owner = std::move(newOwner); }

	virtual std::set<std::shared_ptr<Province>> getProvinces() const { return provinces; }
	virtual std::set<int> getProvinceNumbers() const { return provinceNums; }
	std::string getOwner() const { return owner; }
	std::string getStateID() const { return stateID; }
	virtual std::optional<int> getCapitalProvince() const { return capitalProvince; }
	bool isPartialState() const { return partialState; }
	virtual int getEmployedWorkers() const { return employedWorkers; }

  private:
	workerStruct countEmployedWorkers() const;
	workerStruct limitWorkersByFactoryLevels(const workerStruct& workers) const;
	int determineEmployedWorkersScore(const workerStruct& workers) const;
	bool ownerHasNoCores() const;


	std::string owner;
	std::string stateID = "";
	bool partialState = false;

	std::set<int> provinceNums;
	std::set<std::shared_ptr<Province>> provinces;
	std::optional<int> capitalProvince;

	int factoryLevel = 0;
	int employedWorkers = 0;
};

} // namespace Vic2



#endif // VIC2_STATE_H_
