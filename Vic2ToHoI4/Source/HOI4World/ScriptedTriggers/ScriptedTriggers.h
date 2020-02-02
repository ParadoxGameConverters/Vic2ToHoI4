#ifndef SCRIPTED_TRIGGERS
#define SCRIPTED_TRIGGERS



#include "ScriptedTrigger.h"
#include "../../Configuration.h"
#include "newParser.h"
#include <set>
#include <vector>


namespace HoI4
{

class ScriptedTriggers: commonItems::parser
{
	public:
		void importScriptedTriggers(const Configuration& theConfiguration);
		void updateScriptedTriggers(const std::set<std::string>& majorIdeologies);

		[[nodiscard]] const auto& getIdeologyScriptedTriggers() const { return ideologyScriptedTriggers; }
		[[nodiscard]] const auto& getElectionsScriptedTriggers() const { return electionsScriptedTriggers; }
	
	private:
		void updateIdeologyScriptedTriggers(const std::set<std::string>& majorIdeologies);
		void updateElectionsScriptedTriggers(const std::set<std::string>& majorIdeologies);
	
		std::vector<ScriptedTrigger> ideologyScriptedTriggers;
		std::vector<ScriptedTrigger> electionsScriptedTriggers;
};

}



#endif // SCRIPTED_TRIGGERS