#ifndef LEGACY_SHIP_VARIANT_H
#define LEGACY_SHIP_VARIANT_H



#include "HOI4World/Technologies.h"
#include "external/common_items/ConvenientParser.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class LegacyShipVariant: commonItems::parser
{
  public:
	LegacyShipVariant(std::istream& theStream);

	[[nodiscard]] const auto& getName() const { return name; }

	[[nodiscard]] bool isValidVariant(const technologies& ownedTechs) const;

	friend std::ostream& operator<<(std::ostream& output, const LegacyShipVariant& theVariant);

  private:
	std::string name;
	std::string type;
	std::map<std::string, int> upgrades;
	bool obsolete = false;

	std::set<std::string> requiredTechnologies;
	std::set<std::string> blockingTechnologies;
};

} // namespace HoI4



#endif // LEGACY_SHIP_VARIANT_H