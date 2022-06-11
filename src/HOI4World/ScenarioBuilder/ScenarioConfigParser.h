#ifndef SCENARIO_CONFIG_PARSER_H
#define SCENARIO_CONFIG_PARSER_H

#include "external/common_items/Parser.h"
#include <set>

namespace HoI4
{

class ConfigParser: commonItems::parser
{
  public:
	ConfigParser(std::string fileName, bool preGenned = false);
	[[nodiscard]] std::set<std::string> getPossibleRoles() const { return possibleRoles; };

  private:
	void registerKeys();
	void registerKeysPreGenned();
	std::set<std::string> possibleRoles; // Roles marked as valid in config file
	std::map<std::string, std::string> roleAssignments; // Map of tag to pre-assigned role
};
} // namespace HoI4

#endif // SCENARIO_CONFIG_PARSER_H