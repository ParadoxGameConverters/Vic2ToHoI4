#ifndef VIC2_STATE_DEFINITIONS_H
#define VIC2_STATE_DEFINITIONS_H



#include "newParser.h"
#include <map>
#include <memory>
#include <optional>
#include <set>



namespace Vic2
{

class StateDefinitions
{
  public:
	class Parser;
	StateDefinitions(std::map<int, std::set<int>> stateMap,
		 std::map<int, std::string> provinceToIDMap,
		 std::map<std::string, int> stateToCapitalMap):
		 stateMap(std::move(stateMap)),
		 provinceToIDMap(std::move(provinceToIDMap)), stateToCapitalMap(std::move(stateToCapitalMap))
	{
	}

	std::set<int> getAllProvinces(int provinceNumber) const;
	std::optional<std::string> getStateID(int provinceNumber) const;
	std::optional<int> getCapitalProvince(const std::string& stateID) const;

  private:
	std::map<int, std::set<int>> stateMap; // < province, all other provinces in state >
	std::map<int, std::string> provinceToIDMap;
	std::map<std::string, int> stateToCapitalMap;
};


class StateDefinitions::Parser: commonItems::parser
{
  public:
	std::unique_ptr<StateDefinitions> parseStateDefinitions();
};

} // namespace Vic2



#endif // VIC2_STATE_DEFINITIONS_H
