#ifndef HOI4_SUPPLY_ZONE_H
#define HOI4_SUPPLY_ZONE_H



#include <string>
#include <vector>
using namespace std;



class HoI4SupplyZone
{
	public:
		HoI4SupplyZone(int _ID, int _value);

		void addState(int state)	{ states.push_back(state); }

		[[nodiscard]] auto getId() const { return ID; }
		[[nodiscard]] const auto& getStates() const { return states; }
		[[nodiscard]] auto getValue() const { return value; }

	private:
		HoI4SupplyZone(const HoI4SupplyZone&) = delete;
		HoI4SupplyZone& operator=(const HoI4SupplyZone&) = delete;

		int			ID;
		vector<int>	states;
		int			value;
};


#endif // HOI4_SUPPLY_ZONE_H