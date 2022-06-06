#ifndef SCRIPTED_TRIGGERS
#define SCRIPTED_TRIGGERS



#include "Configuration.h"
#include "external/common_items/ConvenientParser.h"
#include "ScriptedTrigger.h"
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

	void addNationalFocusTrigger(HoI4::ScriptedTrigger& NFTrigger) { nationalFocusTriggers.push_back(NFTrigger); }

	[[nodiscard]] const auto& getIdeologyScriptedTriggers() const { return ideologyScriptedTriggers; }
	[[nodiscard]] const auto& getElectionsScriptedTriggers() const { return electionsScriptedTriggers; }
	[[nodiscard]] const auto& getLawsWarSupportTriggers() const { return lawsWarSupportTriggers; }
	[[nodiscard]] const auto& getNationalFocusTriggers() const { return nationalFocusTriggers; }

  private:
	std::vector<ScriptedTrigger> ideologyScriptedTriggers;
	std::vector<ScriptedTrigger> electionsScriptedTriggers;
	std::vector<ScriptedTrigger> lawsWarSupportTriggers;
	std::vector<ScriptedTrigger> nationalFocusTriggers;
};

} // namespace HoI4



#endif // SCRIPTED_TRIGGERS