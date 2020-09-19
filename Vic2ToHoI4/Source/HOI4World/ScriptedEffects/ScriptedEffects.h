#ifndef SCRIPTED_EFFECTS_H
#define SCRIPTED_EFFECTS_H



#include "ScriptedEffect.h"
#include <string>
#include <vector>



namespace HoI4
{

class ScriptedEffects
{
  public:
	ScriptedEffects(const std::string& HoI4Location);

	[[nodiscard]] const auto& getOperationStratEffects() const { return operationStratEffects; }

  private:
	std::vector<ScriptedEffect> operationStratEffects;
};

} // namespace HoI4



#endif // SCRIPTED_EFFECTS_H