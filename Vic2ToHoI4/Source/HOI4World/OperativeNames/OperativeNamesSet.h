#ifndef OPERATIVE_NAMES_SET_H
#define OPERATIVE_NAMES_SET_H



#include <string>
#include <vector>



namespace HoI4
{

class OperativeNamesSet
{
  public:
	class Factory;
	class Details;

	[[nodiscard]] const auto& getFilename() const { return filename; }
	[[nodiscard]] const auto& getWrapper() const { return wrapper; }
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getNames() const { return names; }

	void addCountry(std::string country) { countries.push_back(std::move(country)); }

  private:
	std::string filename;
	std::string wrapper;
	std::string name;
	std::vector<std::string> countries;
	std::vector<std::string> names;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_SET_H