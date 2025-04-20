#ifndef SCRIPTED_EFFECTS_H
#define SCRIPTED_EFFECTS_H



#include "src/HOI4World/ScriptedEffects/ScriptedEffect.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class ScriptedEffects
{
  public:
	explicit ScriptedEffects(const std::filesystem::path& HoI4Location);

	[[nodiscard]] const auto& getOperationStratEffects() const { return operationStratEffects; }

	void updateOperationStratEffects(const std::set<std::string>& majorIdeologies);

  private:
	void updateUpdateOperationAi(ScriptedEffect* updateOperationAi, const std::set<std::string>& majorIdeologies) const;

	std::vector<ScriptedEffect> operationStratEffects;
};

} // namespace HoI4



#endif // SCRIPTED_EFFECTS_H