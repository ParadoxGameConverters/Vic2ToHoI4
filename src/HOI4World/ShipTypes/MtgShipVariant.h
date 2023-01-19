#ifndef MTG_SHIP_VARIANT_H
#define MTG_SHIP_VARIANT_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/ShipTypes/ShipModules.h"
#include "src/HOI4World/Technologies.h"
#include <memory>
#include <set>
#include <string>



namespace HoI4
{

class MtgShipVariant: commonItems::parser
{
  public:
	explicit MtgShipVariant(std::istream& theStream);

	MtgShipVariant() = default;
	~MtgShipVariant() = default;
	MtgShipVariant(const MtgShipVariant& source);
	MtgShipVariant& operator=(const MtgShipVariant&);
	MtgShipVariant(MtgShipVariant&&) = default;
	MtgShipVariant& operator=(MtgShipVariant&&) = default;

	void setOwningCountryTag(const std::string& tag);

	[[nodiscard]] bool isValidVariant(const technologies& ownedTechs) const;

	[[nodiscard]] std::string getName() const { return name; }

	friend std::ostream& operator<<(std::ostream& output, const MtgShipVariant& theVariant);

  private:
	std::string name;
	std::string type;
	std::string owningCountryTag;
	std::string nameGroup;
	std::unique_ptr<shipModules> modules;
	bool obsolete = false;

	std::string ownerTag;

	std::set<std::string> requiredTechnologies;
	std::set<std::string> blockingTechnologies;
};

} // namespace HoI4



#endif // MTG_SHIP_VARIANT_H