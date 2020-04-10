#ifndef VIC2_STATE_DEFINITIONS_H
#define VIC2_STATE_DEFINITIONS_H



#include "newParser.h"
#include <map>
#include <memory>
#include <optional>
#include <set>



namespace Vic2
{

class StateDefinitions: commonItems::parser
{
	public:
		StateDefinitions() = default;

		void initialize();

		std::set<int> getAllProvinces(int provinceNumber) const;
		std::optional<std::string> getStateID(int provinceNumber) const;
		std::optional<int> getCapitalProvince(const std::string& stateID) const;

	private:
		StateDefinitions(const StateDefinitions&) = delete;
		StateDefinitions& operator=(const StateDefinitions&) = delete;

		std::map<int, std::set<int>> stateMap; // < province, all other provinces in state >
		std::map<int, std::string> provinceToIDMap;
		std::map<std::string, int> stateToCapitalMap;
};


}



#endif // VIC2_STATE_DEFINITIONS_H

