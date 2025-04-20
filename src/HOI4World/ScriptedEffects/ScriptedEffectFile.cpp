#include "src/HOI4World/ScriptedEffects/ScriptedEffectFile.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::ScriptedEffectFile::ScriptedEffectFile()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& effectName, std::istream& theStream) {
		scriptedEffects.push_back(*factory.getScriptedEffect(effectName, theStream));
	});
}



std::vector<HoI4::ScriptedEffect> HoI4::ScriptedEffectFile::getScriptedEffects(const std::filesystem::path& filename)
{
	scriptedEffects.clear();
	parseFile(filename);
	return scriptedEffects;
}