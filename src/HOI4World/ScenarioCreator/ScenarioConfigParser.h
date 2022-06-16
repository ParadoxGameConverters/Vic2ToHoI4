#ifndef SCENARIO_CONFIG_PARSER_H
#define SCENARIO_CONFIG_PARSER_H

#include "external/common_items/Parser.h"
#include <set>

namespace HoI4
{

class ConfigParser: commonItems::parser
{
  public:
	ConfigParser(std::string file_name, bool pre_genned = false);
	[[nodiscard]] std::set<std::string> GetPossibleRoles() const { return possible_roles_; };
	[[nodiscard]] std::map<std::string, std::string> GetRoleAssignments() const { return role_assignments_; };

  private:
	void registerKeys();
	void registerKeysPreGenned();
	std::set<std::string> possible_roles_;						// Roles marked as valid in config file
	std::map<std::string, std::string> role_assignments_; // Map of tag to pre-assigned role
};
} // namespace HoI4

#endif // SCENARIO_CONFIG_PARSER_H