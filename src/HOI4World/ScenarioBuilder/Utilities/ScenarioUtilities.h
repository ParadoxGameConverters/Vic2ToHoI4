#include <string>

#ifndef SCENARIO_UTILITIES_H
#define SCENARIO_UTILITIES_H

class ScenarioUtilities
{
  public:
	ScenarioUtilities() = delete;

	// Strips long//path//to/save.v2 down to save
	static const std::string getSaveName(const std::string& inputFile);
};

#endif // SCENARIO_UTILITIES_H