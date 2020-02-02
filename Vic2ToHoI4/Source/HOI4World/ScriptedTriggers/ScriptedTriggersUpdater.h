#ifndef SCRIPTED_TRIGGERS_UPDATER
#define SCRIPTED_TRIGGERS_UPDATER



#include "ScriptedTriggers.h"
#include <set>



namespace HoI4
{

void updateScriptedTriggers(ScriptedTriggers& scriptedTriggers, const std::set<std::string>& majorIdeologies);

}



#endif // SCRIPTED_TRIGGERS_UPDATER