#ifndef HOI4_REGIONS_H
#define HOI4_REGIONS_H



#include <optional>
#include <string>
#include <unordered_map>



namespace HoI4
{

class Regions
{
  public:
	class Factory;
	[[nodiscard]] std::optional<std::string> getRegion(int provinceNumber) const;

  private:
	std::unordered_map<int, std::string> regionsMap;
};

} // namespace HoI4



#endif // HOI4_REGIONS_H