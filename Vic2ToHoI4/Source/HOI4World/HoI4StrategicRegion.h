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

		int getID() const { return ID; }
		std::vector<int>	getOldProvinces() const	{ return oldProvinces; }

		void addNewProvince(int province) { newProvinces.push_back(province); }

	private:
		HoI4StrategicRegion(const HoI4StrategicRegion&) = delete;
		HoI4StrategicRegion& operator=(const HoI4StrategicRegion&) = delete;

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
