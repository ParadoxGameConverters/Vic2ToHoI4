#ifndef SCRIPTED_EFFECT_FACTORY_H
#define SCRIPTED_EFFECT_FACTORY_H



#include "Parser.h"
#include "ScriptedEffect.h"
#include <memory>



namespace HoI4
{

class ScriptedEffect::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<ScriptedEffect> getScriptedEffect(const std::string& effectName, std::istream& theStream);

  private:
	std::unique_ptr<ScriptedEffect> scriptedEffect;
};

} // namespace HoI4



#endif // SCRIPTED_EFFECT_FACTORY_H