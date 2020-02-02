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
		[[nodiscard]] const auto& getElectionsScriptedTriggers() const { return electionsScriptedTriggers; }
	
	private:
		void createIdeologyScriptedTriggers(const std::set<std::string>& majorIdeologies);
		void createElectionsScriptedTriggers(const std::set<std::string>& majorIdeologies);
	
		std::vector<ScriptedTrigger> ideologyScriptedTriggers;
		std::vector<ScriptedTrigger> electionsScriptedTriggers;
};

}



#endif // SCRIPTED_TRIGGERS