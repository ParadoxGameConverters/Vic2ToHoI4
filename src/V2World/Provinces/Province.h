#ifndef VIC2_PROVINCE_H_
#define VIC2_PROVINCE_H_



#include "src/V2World/Pops/Pop.h"
#include "src/V2World/Pops/PopFactory.h"
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{

class Province
{
  public:
	class Builder;
	class Factory;
	Province() = default;

	[[nodiscard]] int getTotalPopulation() const;
	[[nodiscard]] int getPopulation(const std::optional<std::string>& type = {}) const;
	[[nodiscard]] int getLiteracyWeightedPopulation(const std::optional<std::string>& type = {}) const;
	[[nodiscard]] double getPercentageWithCulture(const std::string& culture) const;
	[[nodiscard]] double getPercentageWithCultures(const std::set<std::string>& cultures) const;
	[[nodiscard]] std::set<std::string> getCultures() const;

	void setOwner(const std::string& _owner) { owner = _owner; }
	void addCore(const std::string& core) { cores.insert(core); }
	void removeCore(const std::string& core) { cores.erase(core); }

	[[nodiscard]] const auto& getNumber() const { return number; }
	[[nodiscard]] auto isLandProvince() const { return landProvince_; }
	[[nodiscard]] const auto& getOwner() const { return owner; }
	[[nodiscard]] const auto& getController() const { return controller; }
	[[nodiscard]] const auto& getCores() const { return cores; }
	[[nodiscard]] const auto& getPops() const { return pops; }
	[[nodiscard]] const auto& getNavalBaseLevel() const { return navalBaseLevel; }
	[[nodiscard]] const auto& getRailLevel() const { return railLevel; }
	[[nodiscard]] const auto& getFlags() const { return flags; }

  private:
	[[nodiscard]] static int calculateLiteracyWeightedPop(const Pop& thePop);

	int number = 0;

	bool landProvince_ = false;

	std::string owner;
	std::string controller;
	std::set<std::string> cores;

	std::vector<Pop> pops;

	int navalBaseLevel = 0;
	int railLevel = 0;

	std::set<std::string> flags;
};

} // namespace Vic2



#endif // VIC2_PROVINCE_H_
