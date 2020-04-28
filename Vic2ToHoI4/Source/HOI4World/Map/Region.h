#ifndef REGION_H
#define REGION_H



#include "Parser.h"



namespace HoI4
{
	
class Region: commonItems::parser
{
	public:
		explicit Region(std::istream& theStream);

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
	
}




#endif // REGION_H