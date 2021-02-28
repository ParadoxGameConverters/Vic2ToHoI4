#ifndef COUNTRY_DATA_H
#define COUNTRY_DATA_H



#include <optional>
#include <string>



namespace Vic2
{

class CountryData
{
  public:
	class Factory;

	[[nodiscard]] const auto& getLastDynasty() const { return lastDynasty; }

  private:
	std::optional<std::string> lastDynasty;
};

} // namespace Vic2



#endif // COUNTRY_DATA_H