#ifndef TANK_DESIGH_H
#define TANK_DESIGH_H



#include "src/HOI4World/Technologies.h"
#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/TankDesigns/TankModules.h"
#include "src/HOI4World/TankDesigns/TankUpgrades.h"



namespace HoI4
{
class TankDesign: commonItems::parser
{
  public:
	explicit TankDesign(std::istream& theStream);

	TankDesign() = default;
	~TankDesign() = default;
	TankDesign(const TankDesign& source);
	TankDesign& operator=(const TankDesign&);
	TankDesign(TankDesign&&) = default;
	TankDesign& operator=(TankDesign&&) = default;

	[[nodiscard]] bool isValidDesign(const technologies& ownedTechs) const;

	[[nodiscard]] std::string getName() const { return name; }

	friend std::ostream& operator<<(std::ostream& output, const TankDesign& theDesign);

  private:
	std::string name;
	std::string type;
	std::unique_ptr<TankModules> modules;
	std::unique_ptr<TankUpgrades> upgrades;
	std::optional<std::string> icon;
	bool obsolete = false;

	std::set<std::string> requiredTechnologies;
	std::set<std::string> blockingTechnologies;
};
} // namespace HoI4
#endif