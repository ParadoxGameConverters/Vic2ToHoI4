#ifndef SCRIPTED_LOCALISATIONS_FACTORY_H
#define SCRIPTED_LOCALISATIONS_FACTORY_H



#include "Parser.h"
#include "ScriptedLocalisationFactory.h"
#include "ScriptedLocalisations.h"
#include <memory>



namespace HoI4
{

class ScriptedLocalisations::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<ScriptedLocalisations> getScriptedLocalisations();

  private:
	std::unique_ptr<ScriptedLocalisations> scriptedLocalisations;
	ScriptedLocalisation::Factory factory;
};

} // namespace HoI4



#endif // SCRIPTED_LOCALISATIONS_FACTORY_H