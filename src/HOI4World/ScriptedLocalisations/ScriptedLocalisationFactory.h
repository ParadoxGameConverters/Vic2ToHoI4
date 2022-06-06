#ifndef SCRIPTED_LOCALISATION_FACTORY_H
#define SCRIPTED_LOCALISATION_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "ScriptedLocalisation.h"
#include <memory>



namespace HoI4
{

class ScriptedLocalisation::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<ScriptedLocalisation> getScriptedLocalisation(std::istream& theStream);

  private:
	std::unique_ptr<ScriptedLocalisation> scriptedLocalisation;
};

} // namespace HoI4



#endif // SCRIPTED_LOCALISATION_FACTORY_H