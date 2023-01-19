#ifndef OUT_SCRIPTED_EFFECTS_H
#define OUT_SCRIPTED_EFFECTS_H



#include "src/HOI4World/ScriptedEffects/ScriptedEffect.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const ScriptedEffect& scriptedEffect);

} // namespace HoI4



#endif // OUT_SCRIPTED_EFFECTS_H