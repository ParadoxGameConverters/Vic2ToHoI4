#ifndef SUPPLY_AREA
#define SUPPLY_AREA



#include "newParser.h"



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




#endif // SUPPLY_AREA