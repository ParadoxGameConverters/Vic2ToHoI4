#ifndef OUT_SCRIPTED_EFFECTS
#define OUT_SCRIPTED_EFFECTS



#include "src/HOI4World/ScriptedEffects/ScriptedEffects.h"
#include <set>
#include <string>



namespace HoI4
{

void outputScriptedEffects(const ScriptedEffects& scriptedEffects,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName);

} // namespace HoI4



#endif // OUT_SCRIPTED_EFFECTS