#ifndef LEGACY_SHIP_VARIANT_H
#define LEGACY_SHIP_VARIANT_H



#include "../Technologies.h"
#include "newParser.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class LegacyShipVariant: commonItems::parser
{
  public:
	LegacyShipVariant(std::istream& theStream);

	friend std::ostream& operator<<(std::ostream& output, const LegacyShipVariant& theVariant);

	[[nodiscard]] bool isValidVariant(const technologies& ownedTechs) const;

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