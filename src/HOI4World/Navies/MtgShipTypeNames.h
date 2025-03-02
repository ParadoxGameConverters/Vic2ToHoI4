#ifndef MTG_SHIP_TYPE_NAMES_H
#define MTG_SHIP_TYPE_NAMES_H



#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class MtgShipTypeNames
{
  public:
	explicit MtgShipTypeNames(std::string _type,
		 std::string _theme,
		 std::set<std::string> _shipTypes,
		 std::string _fallbackName,
		 std::vector<std::string> _names):
		 type(std::move(_type)), theme(std::move(_theme)), shipTypes(std::move(_shipTypes)),
		 fallbackName(std::move(_fallbackName)), names(std::move(_names))
	{
	}

	bool operator<(const MtgShipTypeNames& rhs) const { return type < rhs.type; }

	[[nodiscard]] std::string_view getType() const { return type; }
	[[nodiscard]] std::string_view getTheme() const { return theme; }
	[[nodiscard]] std::set<std::string> getShipTypes() const { return shipTypes; }
	[[nodiscard]] std::string_view getPrefix() const { return ""; }
	[[nodiscard]] std::string_view getFallbackName() const { return fallbackName; }
	[[nodiscard]] std::vector<std::string> getNames() const { return names; }

  private:
	std::string type;
	std::string theme;
	std::set<std::string> shipTypes;
	std::string fallbackName;
	std::vector<std::string> names;
};

} // namespace HoI4



#endif // MTG_SHIP_TYPE_NAMES_H