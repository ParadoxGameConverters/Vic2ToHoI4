#ifndef HOI4_SUPPLY_ZONE_H
#define HOI4_SUPPLY_ZONE_H



#include <vector>



namespace HoI4
{

class SupplyZone
{
  public:
	SupplyZone(const int _ID, const int _value): ID(_ID), value(_value) {}

	void addState(const int state) { states.push_back(state); }

	[[nodiscard]] auto getId() const { return ID; }
	[[nodiscard]] const auto& getStates() const { return states; }
	[[nodiscard]] auto getValue() const { return value; }

  private:
	int ID;
	std::vector<int> states;
	int value;
};

} // namespace HoI4



#endif // HOI4_SUPPLY_ZONE_H