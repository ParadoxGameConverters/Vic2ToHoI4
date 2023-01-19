#ifndef UNIT_MAP_H
#define UNIT_MAP_H



#include "external/common_items/ConvenientParser.h"
#include <string>



namespace HoI4
{


class HoI4UnitType: commonItems::parser
{
  public:
	explicit HoI4UnitType(std::istream& theStream);

	bool operator==(const HoI4UnitType&) const;

	[[nodiscard]] std::string getCategory() const { return category; }
	[[nodiscard]] std::string getType() const { return type; }
	[[nodiscard]] std::string getEquipment() const { return equipment; }
	[[nodiscard]] std::string getVersion() const { return version; }
	[[nodiscard]] int getSize() const { return size; }

  private:
	std::string category;
	std::string type;
	std::string equipment;
	std::string version;
	int size = 0;
};


} // namespace HoI4



#endif // UNIT_MAP_H