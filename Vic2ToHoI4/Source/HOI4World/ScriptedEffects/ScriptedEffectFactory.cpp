#include "ScriptedEffectFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::ScriptedEffect::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& itemName, std::istream& theStream) {
		scriptedEffect->items.emplace_back(std::make_pair(itemName, commonItems::stringOfItem{theStream}.getString()));
	});
}


std::unique_ptr<HoI4::ScriptedEffect> HoI4::ScriptedEffect::Factory::getScriptedEffect(const std::string& effectName,
	 std::istream& theStream)
{
	scriptedEffect = std::make_unique<ScriptedEffect>();
	scriptedEffect->name = effectName;
	parseStream(theStream);
	return std::move(scriptedEffect);
}