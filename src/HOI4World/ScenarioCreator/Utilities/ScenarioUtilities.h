#include <string>

#ifndef SCENARIO_UTILITIES_H
#define SCENARIO_UTILITIES_H

class ScenarioUtilities
{
  public:
	ScenarioUtilities() = delete;

	// Strips long//path//to/save.v2 down to save
	static const std::string GetSaveName(const std::string& input_file);

  private:
	// If nothing goese here at end, just make this part of HoI4 namespace and no class
};

#endif // SCENARIO_UTILITIES_H