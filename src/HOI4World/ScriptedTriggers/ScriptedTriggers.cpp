#include "ScriptedTriggers.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"



void HoI4::ScriptedTriggers::importScriptedTriggers(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tImporting scripted triggers";

	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		ScriptedTrigger scriptedTrigger(name);
		const commonItems::stringOfItem bodyString(theStream);
		scriptedTrigger.setBody(bodyString.getString());
		ideologyScriptedTriggers.push_back(scriptedTrigger);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/scripted_triggers/ideology_scripted_triggers.txt");
	clearRegisteredKeywords();

	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		ScriptedTrigger scriptedTrigger(name);
		const commonItems::stringOfItem bodyString(theStream);
		scriptedTrigger.setBody(bodyString.getString());
		electionsScriptedTriggers.push_back(scriptedTrigger);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/scripted_triggers/Elections_scripted_triggers.txt");
	clearRegisteredKeywords();

	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		ScriptedTrigger scriptedTrigger(name);
		const commonItems::stringOfItem bodyString(theStream);
		scriptedTrigger.setBody(bodyString.getString());
		lawsWarSupportTriggers.push_back(scriptedTrigger);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/scripted_triggers/laws_war_support.txt");
	clearRegisteredKeywords();
}


void replaceScriptedTriggers(std::vector<HoI4::ScriptedTrigger>& triggers,
	 const std::map<std::string_view, std::string>& replacements)
{
	for (auto& scriptedTrigger: triggers)
	{
		if (auto replacement = replacements.find(scriptedTrigger.getName()); replacement != replacements.end())
		{
			scriptedTrigger.setBody(replacement->second);
		}
	}
}


void HoI4::ScriptedTriggers::replaceIdeologyScriptedTrigger(const std::string_view name,
	 const std::string& replacementBody)
{
	replaceScriptedTriggers(ideologyScriptedTriggers, std::map<std::string_view, std::string>{{name, replacementBody}});
}


void HoI4::ScriptedTriggers::replaceElectionsScriptedTrigger(const std::string_view name,
	 const std::string& replacementBody)
{
	replaceScriptedTriggers(electionsScriptedTriggers, std::map<std::string_view, std::string>{{name, replacementBody}});
}


void HoI4::ScriptedTriggers::replaceLawsWarSupportTriggers(const std::map<std::string_view, std::string>& replacements)
{
	replaceScriptedTriggers(lawsWarSupportTriggers, replacements);
}