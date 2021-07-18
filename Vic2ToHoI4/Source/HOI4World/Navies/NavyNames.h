#ifndef NAVY_NAMES_H
#define NAVY_NAMES_H



#include "LegacyShipTypeNames.h"
#include "MtgShipTypeNames.h"
#include <set>



namespace HoI4
{

class NavyNames
{
  public:
	[[nodiscard]] std::set<LegacyShipTypeNames> getLegacyShipTypeNames() const { return legacyShipTypeNames; }
	[[nodiscard]] std::set<MtgShipTypeNames> getMtgShipTypeNames() const { return mtgShipTypeNames; }

	void addLegacyShipTypeNames(const LegacyShipTypeNames& newShipTypeNames)
	{
		legacyShipTypeNames.insert(newShipTypeNames);
	}
	void addMtgShipTypeNames(const MtgShipTypeNames& newShipTypeNames) { mtgShipTypeNames.insert(newShipTypeNames); }

  private:
	std::set<LegacyShipTypeNames> legacyShipTypeNames;
	std::set<MtgShipTypeNames> mtgShipTypeNames;
};

} // namespace HoI4



#endif // NAVY_NAMES_H
