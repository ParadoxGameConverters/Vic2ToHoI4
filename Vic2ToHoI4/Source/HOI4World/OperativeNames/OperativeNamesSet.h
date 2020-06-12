#ifndef OPERATIVE_NAMES_SET_H
#define OPERATIVE_NAMES_SET_H



#include <string>
#include <vector>



namespace HoI4
{

class OperativeNamesSet
{
  public:
	[[nodiscard]] const auto& getFilename() const { return filename; }
	[[nodiscard]] const auto& getWrapper() const { return wrapper; }
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getNames() const { return names; }

  private:
	std::string filename = "generic_opertive_codenames.txt";
	std::string wrapper = "GENERIC_ENG_OPERATIVE_CODENAME_HISTORICAL";
	std::string name = "NAME_THEME_HISTORICAL_OPERATIVES";
	std::vector<std::string> countries{"ABC", "DEF"};
	std::vector<std::string> names{"007", "008"};
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_SET_H