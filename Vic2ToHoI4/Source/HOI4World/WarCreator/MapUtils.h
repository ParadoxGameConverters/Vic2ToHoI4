#ifndef MAP_UTILS_H
#define MAP_UTILS_H



#include "HOI4World/HoI4Country.h"
#include <memory>
#include <optional>



namespace HoI4
{

class MapUtils
{
  public:
	std::optional<double> getDistanceBetweenCountries(std::shared_ptr<Country> Country1,
		 std::shared_ptr<Country> Country2);
	std::optional<double> getDistanceBetweenCapitals(std::shared_ptr<Country> Country1,
		 std::shared_ptr<Country> Country2);
	bool bothCountriesHaveCapitals(std::shared_ptr<Country> Country1, std::shared_ptr<Country> Country2) const;
	std::pair<int, int> getCapitalPosition(std::shared_ptr<Country> country);
	std::pair<int, int> getProvincePosition(int provinceNum);
	void establishProvincePositions();
	void processPositionLine(const std::string& line);
	std::vector<std::string> tokenizeLine(const std::string& line);
	void addProvincePosition(const std::vector<std::string>& tokenizedLine);
	double getDistanceBetweenPoints(std::pair<int, int> point1, std::pair<int, int> point2) const;

  private:
	std::map<int, std::pair<int, int>> provincePositions;
};

} // namespace HoI4



#endif // MAP_UTILS_H