#ifndef SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_H_
#define SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_H_



#include "external/common_items/Color.h"
#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Politics/Party.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

struct CommonCountryDataOptions
{
	std::optional<commonItems::Color> color_;
	std::map<std::string, std::vector<std::string>> unit_names_;
	std::vector<Party> parties_;
};


class CommonCountryData
{
  public:
	class Factory;
	CommonCountryData() = default;
	explicit CommonCountryData(CommonCountryDataOptions&& options):
		 color_(std::move(options.color_)), unit_names_(std::move(options.unit_names_)),
		 parties_(std::move(options.parties_))
	{
	}

	[[nodiscard]] auto GetColor() const { return color_; }
	[[nodiscard]] auto GetUnitNames() const { return unit_names_; }
	[[nodiscard]] auto GetParties() const { return parties_; }

	[[nodiscard]] bool operator==(const CommonCountryData& rhs) const;

  private:
	std::optional<commonItems::Color> color_;
	std::map<std::string, std::vector<std::string>> unit_names_;
	std::vector<Party> parties_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_H_