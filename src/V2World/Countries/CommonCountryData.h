#ifndef COMMON_COUNTRY_DATA_H_
#define COMMON_COUNTRY_DATA_H_



#include "external/common_items/Color.h"
#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Politics/Party.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class CommonCountryData
{
  public:
	class Factory;
	class Builder;
	CommonCountryData() = default;

	[[nodiscard]] auto getColor() const { return theColor; }
	[[nodiscard]] auto getUnitNames() const { return unitNames; }
	[[nodiscard]] auto getParties() const { return parties; }

  private:
	std::optional<commonItems::Color> theColor;
	std::map<std::string, std::vector<std::string>> unitNames;
	std::vector<Party> parties;
};

} // namespace Vic2



#endif // COMMON_COUNTRY_DATA_H_