#include <string>

#ifndef SCENARIO_UTILITIES_H
#define SCENARIO_UTILITIES_H

class ScenarioUtilities
{
  public:
	ScenarioUtilities() = delete;

	// Strips long//path//to/save.v2 down to save
	static const std::string getSaveName(const std::string& inputFile);

  private:
	  // Static const member variables for string in file to variable conversion
	static const std::string garrison;
};

#endif // SCENARIO_UTILITIES_H