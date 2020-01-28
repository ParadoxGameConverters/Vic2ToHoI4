#ifndef _HOI4_STRATEGIC_REGION
#define _HOI4_STRATEGIC_REGION



#include "newParser.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



class HoI4StrategicRegion: commonItems::parser
{
	public:
		explicit HoI4StrategicRegion(const std::string& _filename);
		void output(const std::string& path) const;

		[[nodiscard]] int getID() const { return ID; }
		[[nodiscard]] std::vector<int>	getOldProvinces() const	{ return oldProvinces; }

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



#endif // _HOI4_STRATEGIC_REGION
