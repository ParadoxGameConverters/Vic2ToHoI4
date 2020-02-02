#ifndef SCRIPTED_TRIGGERS
#define SCRIPTED_TRIGGERS



#include "ScriptedTrigger.h"
#include <set>
#include <vector>


namespace HoI4
{

class ScriptedTriggers
{
	public:
		void createScriptedTriggers(const std::set<std::string>& majorIdeologies);

		[[nodiscard]] const auto& getIdeologyScriptedTriggers() const { return ideologyScriptedTriggers; }
	
	private:
		std::vector<ScriptedTrigger> ideologyScriptedTriggers;
};

}



#endif // SCRIPTED_TRIGGERS