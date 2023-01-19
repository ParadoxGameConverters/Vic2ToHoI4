#ifndef MAP_REGION_H
#define MAP_REGION_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class MapRegion: commonItems::parser
{
  public:
	explicit MapRegion(std::istream& theStream);

	[[nodiscard]] auto getID() const { return ID; }
	[[nodiscard]] auto takeName() { return std::move(name); }
	[[nodiscard]] auto takeProvinces() { return std::move(provinces); }
	[[nodiscard]] auto takeNavalTerrain() { return std::move(navalTerrain); }
	[[nodiscard]] auto takeStaticModifiers() { return std::move(staticModifiers); }
	[[nodiscard]] auto takeWeather() { return std::move(weather); }

  private:
	int ID = 0;
	std::string name;
	std::vector<int> provinces;
	std::optional<std::string> navalTerrain;
	std::map<std::string, std::string> staticModifiers;
	std::string weather;
};

} // namespace HoI4



#endif // MAP_REGION_H