#ifndef SCENARIO_CONFIG_PARSER_H
#define SCENARIO_CONFIG_PARSER_H

#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/ScenarioBuilder/ScenarioBuilder.h"

namespace HoI4
{

class ScenarioBuilder::ConfigParser: commonItems::parser
{
  public:
	ConfigParser(std::string fileName);
	[[nodiscard]] std::vector<std::string> getPossibleRoles() const { return possibleRoles; };

  private:
	void registerKeys();
	std::vector<std::string> possibleRoles; // Roles marked as valid in config file
};
} // namespace HoI4

#endif // SCENARIO_CONFIG_PARSER_H