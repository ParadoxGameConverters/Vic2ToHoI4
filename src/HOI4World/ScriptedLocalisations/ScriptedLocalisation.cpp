#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisation.h"



void HoI4::ScriptedLocalisation::filterTexts(const std::function<bool(const std::string&)>& removeCondition)
{
	texts.erase(std::remove_if(texts.begin(), texts.end(), removeCondition), texts.end());
}


void HoI4::ScriptedLocalisation::updateTexts(const std::regex& old, const std::string& replacement)
{
	for (auto& text: texts)
	{
		text = std::regex_replace(text, old, replacement);
	}
}