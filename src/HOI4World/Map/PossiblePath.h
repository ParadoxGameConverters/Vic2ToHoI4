#ifndef HOI4WORLD_MAP_POSSIBLE_PATH_H
#define HOI4WORLD_MAP_POSSIBLE_PATH_H



#include <vector>



namespace HoI4
{

class PossiblePath
{
  public:
	explicit PossiblePath(int initialProvince) { provinces_.push_back(initialProvince); }

	void addProvince(int province, double additionalCost)
	{
		provinces_.push_back(province);
		cost_ += additionalCost;
	}

	// higher is prioritized where we want lower to be, so reverse the meaning of less than
	[[nodiscard]] bool operator<(const PossiblePath& rhs) const { return cost_ > rhs.cost_; }
	[[nodiscard]] int getLastProvince() const { return provinces_[provinces_.size() - 1]; }
	[[nodiscard]] std::vector<int> getProvinces() const { return provinces_; }

  private:
	std::vector<int> provinces_;
	double cost_ = 0;
};

} // namespace HoI4



#endif // HOI4WORLD_MAP_POSSIBLE_PATH_H