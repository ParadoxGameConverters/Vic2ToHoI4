#ifndef SUPPLY_AREA
#define SUPPLY_AREA



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class SupplyArea: commonItems::parser
{
  public:
	explicit SupplyArea(std::istream& theStream);

	[[nodiscard]] auto getID() const { return ID; }
	[[nodiscard]] auto getValue() const { return value; }
	[[nodiscard]] const auto& getStates() const { return states; }

  private:
	int ID = 0;
	int value = 0;
	std::vector<int> states;
};

} // namespace HoI4



#endif // SUPPLY_AREA