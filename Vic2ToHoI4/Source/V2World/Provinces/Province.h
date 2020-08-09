#ifndef VIC2_PROVINCE_H_
#define VIC2_PROVINCE_H_



#include "../Pops/Pop.h"
#include "../Pops/PopFactory.h"
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{

class Province
{
  public:
	class Factory;
	Province() = default;

	int getTotalPopulation() const;
	int getPopulation(std::optional<std::string> type = {}) const;
	int getLiteracyWeightedPopulation(std::optional<std::string> type = {}) const;
	double getPercentageWithCultures(const std::set<std::string>& cultures) const;

	void setOwner(const std::string& _owner) { owner = _owner; }
	void addCore(const std::string& core) { cores.insert(core); }
	void removeCore(const std::string& core) { cores.erase(core); }

	int getNumber() const { return number; }
	const std::string getOwner() const { return owner; }
	const std::string getController() const { return controller; }
	const std::set<std::string> getCores() const { return cores; }
	const std::vector<Pop> getPops() const { return pops; }
	int getNavalBaseLevel() const { return navalBaseLevel; }
	int getRailLevel() const { return railLevel; }

  private:
	int calculateLiteracyWeightedPop(const Pop& thePop) const;

	int number;

	std::string owner;
	std::string controller;
	std::set<std::string> cores;

	std::vector<Pop> pops;

	int navalBaseLevel = 0;
	int railLevel = 0;
};

} // namespace Vic2



#endif // VIC2_PROVINCE_H_
