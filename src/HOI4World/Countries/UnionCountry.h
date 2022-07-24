#ifndef SRC_HOI4_WORLD_COUNTRIES_UNION_COUNTRY_H_
#define SRC_HOI4_WORLD_COUNTRIES_UNION_COUNTRY_H_



#include "external/common_items/Color.h"
#include "src/V2World/Countries/Country.h"
#include <string>
#include <vector>



namespace HoI4
{

class UnionCountry
{
  public:
	UnionCountry(const Vic2::Country& source_country, const Vic2::CultureGroups& culture_groups);

	[[nodiscard]] const std::string& GetTag() const { return tag_; }
	[[nodiscard]] const std::set<std::string>& GetCultures() const { return cultures_; }
	[[nodiscard]] const commonItems::Color& GetColor() const { return color_; }

  private:
	std::string tag_;
	std::set<std::string> cultures_;
	commonItems::Color color_;
};

} // namespace HoI4



#endif // SRC_HOI4_WORLD_COUNTRIES_UNION_COUNTRY_H_