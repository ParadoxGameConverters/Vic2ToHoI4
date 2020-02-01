#ifndef REGION_H
#define REGION_H



#include "newParser.h"



namespace HoI4
{
	
class Region: commonItems::parser
{
	public:
		explicit Region(std::istream& theStream);

		[[nodiscard]] auto getID() const { return ID; }
		[[nodiscard]] auto getName() const { return name; }
		[[nodiscard]] auto getProvinces() const { return provinces; }
		[[nodiscard]] auto getNavalTerrain() const { return navalTerrain; }
		[[nodiscard]] auto getStaticModifiers() const { return staticModifiers; }
		[[nodiscard]] auto getWeather() const { return weather; }

	private:
		int ID = 0;
		std::string name;
		std::vector<int> provinces;
		std::optional<std::string> navalTerrain;
		std::map<std::string, std::string> staticModifiers;
		std::string weather;
};
	
}




#endif // REGION_H