#ifndef HOI4WORLD_MAP_RAILWAY_H
#define HOI4WORLD_MAP_RAILWAY_H



#include <stdexcept>
#include <vector>



namespace HoI4
{

class Railway
{
  public:
	Railway(int level, const std::vector<int>& provinces): level_(level), provinces_(provinces)
	{
		if (provinces.size() < 2)
		{
			throw std::runtime_error("Railways must have at least two provinces.");
		}
	}

	[[nodiscard]] int getLevel() const { return level_; }
	[[nodiscard]] const auto& getProvinces() const { return provinces_; }
	[[nodiscard]] int getLength() const { return static_cast<int>(provinces_.size()); }

  private:
	int level_ = 0;
	std::vector<int> provinces_;
};

} // namespace HoI4



#endif // HOI4WORLD_MAP_RAILWAY_H