#ifndef SRC_HOI4_WORLD_MAP_POSSIBLE_PATH_H_
#define SRC_HOI4_WORLD_MAP_POSSIBLE_PATH_H_



#include <vector>



namespace HoI4
{

class PossiblePath
{
  public:
	explicit PossiblePath(int initial_province) { provinces_.push_back(initial_province); }

	void AddProvince(int province, double additional_cost)
	{
		provinces_.push_back(province);
		cost_ += additional_cost;
	}
	void ReplaceProvinces(std::vector<int> new_provinces) { provinces_ = std::move(new_provinces); }
	void SetLevel(int level) { level_ = level; }

	[[nodiscard]] int GetLastProvince() const { return provinces_[provinces_.size() - 1]; }
	[[nodiscard]] int GetFirstProvince() const { return provinces_[0]; }
	[[nodiscard]] std::vector<int> GetProvinces() const { return provinces_; }
	[[nodiscard]] int GetLevel() const { return level_; }
	[[nodiscard]] double GetCost() const { return cost_; }

	// higher is prioritized where we want lower to be in priority queues, so reverse the meaning of <
	[[nodiscard]] bool operator<(const PossiblePath& rhs) const { return cost_ > rhs.cost_; }
	[[nodiscard]] bool operator==(const PossiblePath&) const = default;

  private:
	std::vector<int> provinces_;
	double cost_ = 0;
	int level_ = 0;
};

} // namespace HoI4



#endif // SRC_HOI4_WORLD_MAP_POSSIBLE_PATH_H_