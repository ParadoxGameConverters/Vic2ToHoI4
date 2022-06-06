#ifndef SCRIPTED_EFFECT_FILE_H
#define SCRIPTED_EFFECT_FILE_H



#include "external/common_items/ConvenientParser.h"
#include "ScriptedEffect.h"
#include "ScriptedEffectFactory.h"
#include <vector>



namespace HoI4
{

class ScriptedEffectFile: commonItems::parser
{
  public:
	ScriptedEffectFile();
	std::vector<ScriptedEffect> getScriptedEffects(const std::string& filename);

  private:
	ScriptedEffect::Factory factory;
	std::vector<ScriptedEffect> scriptedEffects;
};

} // namespace HoI4



#endif // SCRIPTED_EFFECT_FILE_H