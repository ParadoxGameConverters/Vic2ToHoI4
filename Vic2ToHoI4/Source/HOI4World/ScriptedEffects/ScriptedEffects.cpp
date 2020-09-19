#include "ScriptedEffects.h"
#include "ScriptedEffectFile.h"



HoI4::ScriptedEffects::ScriptedEffects(const std::string& HoI4Location)
{
	operationStratEffects =
		 ScriptedEffectFile{}.getScriptedEffects(HoI4Location + "/common/scripted_effects/operation_strat_effects.txt");
}