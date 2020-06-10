#ifndef OPERATIVE_NAMES_SET_H
#define OPERATIVE_NAMES_SET_H



#include <string>
#include <vector>



namespace HoI4
{

class OperativeNamesSet
{
  public:
	[[nodiscard]] const auto& getTag() const { return tag; }
	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getNames() const { return names; }

  private:
	std::string tag = "TAG";
	std::vector<std::string> countries{"ABC", "DEF"};
	std::vector<std::string> names{"007", "008"};
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_SET_H