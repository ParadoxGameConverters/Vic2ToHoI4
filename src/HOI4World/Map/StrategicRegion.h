#ifndef _HOI4_STRATEGIC_REGION
#define _HOI4_STRATEGIC_REGION



#include "Configuration.h"
#include "Parser.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



namespace HoI4
{

class StrategicRegion: commonItems::parser
{
  public:
	explicit StrategicRegion(const std::string& _filename, const Configuration& theConfiguration);

	[[nodiscard]] const auto& getFilename() const { return filename; }
	[[nodiscard]] auto getID() const { return ID; }
	[[nodiscard]] std::string_view getName() const { return name; }
	[[nodiscard]] const auto& getOldProvinces() const { return oldProvinces; }
	[[nodiscard]] const auto& getNewProvinces() const { return newProvinces; }
	[[nodiscard]] bool hasStaticModifiers() const { return !staticModifiers.empty(); }
	[[nodiscard]] const auto& getStaticModifiers() const { return staticModifiers; }
	[[nodiscard]] const auto& getNavalTerrain() const { return navalTerrain; }
	[[nodiscard]] std::string_view getWeather() const { return weather; }

	void addNewProvince(const int province) { newProvinces.push_back(province); }

  private:
	std::string filename;
	int ID = 0;
	std::string name;
	std::vector<int> oldProvinces;
	std::vector<int> newProvinces;
	std::map<std::string, std::string> staticModifiers;
	std::optional<std::string> navalTerrain;
	std::string weather;
};

} // namespace HoI4



#endif // _HOI4_STRATEGIC_REGION
