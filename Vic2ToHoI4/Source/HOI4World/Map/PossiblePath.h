#ifndef HOI4WORLD_MAP_POSSIBLE_PATH_H
#define HOI4WORLD_MAP_POSSIBLE_PATH_H



#include <vector>



namespace HoI4
{

class PossiblePath
{
  public:
	explicit PossiblePath(int initialProvince) { provinces.push_back(initialProvince); }

	void addProvince(int province, int additionalCost)
	{
		provinces.push_back(province);
		cost += additionalCost;
	}

	// higher is prioritized where we want lower to be, so reverse the meaning of less than
	[[nodiscard]] bool operator<(const PossiblePath& rhs) const { return cost > rhs.cost; }
	[[nodiscard]] int getLastProvince() const { return provinces[provinces.size() - 1]; }
	[[nodiscard]] std::vector<int> getProvinces() const { return provinces; }

  private:
	std::vector<int> provinces;
	int cost = 0;
};

} // namespace HoI4



#endif // HOI4WORLD_MAP_POSSIBLE_PATH_H