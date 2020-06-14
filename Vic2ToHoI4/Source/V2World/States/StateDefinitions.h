#ifndef VIC2_STATE_DEFINITIONS_H
#define VIC2_STATE_DEFINITIONS_H



#include "Parser.h"
#include <map>
#include <optional>
#include <set>



class Configuration;



namespace Vic2
{

class StateDefinitions
{
  public:
	class Factory;

	StateDefinitions(std::map<int, std::set<int>> stateMap,
		 std::map<int, std::string> provinceToIDMap,
		 std::map<std::string, int> stateToCapitalMap):
		 stateMap(std::move(stateMap)),
		 provinceToIDMap(std::move(provinceToIDMap)), stateToCapitalMap(std::move(stateToCapitalMap))
	{
	}

	[[nodiscard]] std::set<int> getAllProvinces(int provinceNumber) const;
	[[nodiscard]] std::optional<std::string> getStateID(int provinceNumber) const;
	[[nodiscard]] std::optional<int> getCapitalProvince(const std::string& stateID) const;

  private:
	std::map<int, std::set<int>> stateMap; // < province, all other provinces in state >
	std::map<int, std::string> provinceToIDMap;
	std::map<std::string, int> stateToCapitalMap;
};

} // namespace Vic2



#endif // VIC2_STATE_DEFINITIONS_H