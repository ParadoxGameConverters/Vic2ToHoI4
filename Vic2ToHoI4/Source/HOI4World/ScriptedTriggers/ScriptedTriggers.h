#ifndef SCRIPTED_TRIGGERS
#define SCRIPTED_TRIGGERS



#include "ScriptedTrigger.h"
#include "../../Configuration.h"
#include "newParser.h"
#include <map>
#include <set>
#include <vector>


namespace HoI4
{

class ScriptedTriggers: commonItems::parser
{
	public:
		void importScriptedTriggers(const Configuration& theConfiguration);

		void replaceIdeologyScriptedTrigger(std::string_view name, const std::string& replacementBody);
		void replaceElectionsScriptedTrigger(std::string_view name, const std::string& replacementBody);
		void replaceLawsWarSupportTriggers(const std::map<std::string_view, std::string>& replacements);

		void updateScriptedTriggers(const std::set<std::string>& majorIdeologies);

		[[nodiscard]] const auto& getIdeologyScriptedTriggers() const { return ideologyScriptedTriggers; }
		[[nodiscard]] const auto& getElectionsScriptedTriggers() const { return electionsScriptedTriggers; }
		[[nodiscard]] const auto& getLawsWarSupportTriggers() const { return lawsWarSupportTriggers; }
	
	private:
		void updateIdeologyScriptedTriggers(const std::set<std::string>& majorIdeologies);
		void updateElectionsScriptedTriggers(const std::set<std::string>& majorIdeologies);
		void updateLawsWarSupportTriggers(const std::set<std::string>& majorIdeologies);
	
		std::vector<ScriptedTrigger> ideologyScriptedTriggers;
		std::vector<ScriptedTrigger> electionsScriptedTriggers;
		std::vector<ScriptedTrigger> lawsWarSupportTriggers;
};

}



#endif // SCRIPTED_TRIGGERS