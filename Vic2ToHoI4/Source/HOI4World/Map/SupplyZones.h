#ifndef HOI4_SUPPLY_ZONES_H
#define HOI4_SUPPLY_ZONES_H



#include "newParser.h"
#include <map>
#include <set>
#include <string>



class HoI4SupplyZone;



namespace HoI4
{

class DefaultState;
class States;



class SupplyZones: commonItems::parser
{
	public:
		explicit SupplyZones(const std::map<int, HoI4::DefaultState>& defaultStates);
		void output();
		void convertSupplyZones(const States& states);

	private:
		SupplyZones(const SupplyZones&) = delete;
		SupplyZones& operator=(const SupplyZones&) = delete;

		void importStates(const std::map<int, HoI4::DefaultState>& defaultStates);

		std::map<int, std::set<int>> defaultStateToProvinceMap;
		std::map<int, std::string> supplyZonesFilenames;
		std::map<int, HoI4SupplyZone*> supplyZones;
		std::map<int, int> provinceToSupplyZoneMap;
};

}



#endif // HOI4_SUPPLY_ZONES_H