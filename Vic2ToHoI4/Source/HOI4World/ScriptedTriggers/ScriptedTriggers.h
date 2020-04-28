#ifndef SCRIPTED_TRIGGERS
#define SCRIPTED_TRIGGERS



#include "ScriptedTrigger.h"
#include "../../Configuration.h"
#include "Parser.h"
#include <map>
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

		[[nodiscard]] const auto& getIdeologyScriptedTriggers() const { return ideologyScriptedTriggers; }
		[[nodiscard]] const auto& getElectionsScriptedTriggers() const { return electionsScriptedTriggers; }
		[[nodiscard]] const auto& getLawsWarSupportTriggers() const { return lawsWarSupportTriggers; }
	
	private:
		std::vector<ScriptedTrigger> ideologyScriptedTriggers;
		std::vector<ScriptedTrigger> electionsScriptedTriggers;
		std::vector<ScriptedTrigger> lawsWarSupportTriggers;
};

}



#endif // SCRIPTED_TRIGGERS