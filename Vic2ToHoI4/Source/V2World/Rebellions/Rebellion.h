#ifndef REBELLION_H
#define REBELLION_H



#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class Rebellion
{
  public:
	class Factory;
	
	std::optional<std::string> getIdeology() const;

	[[nodiscard]] const auto& getCountry() const { return country; }
	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getProvinces() const { return provinces; }

  private:
	std::string country;
	std::string type;
	std::vector<int> provinces;
};

} // namespace Vic2



#endif // REBELLION_H