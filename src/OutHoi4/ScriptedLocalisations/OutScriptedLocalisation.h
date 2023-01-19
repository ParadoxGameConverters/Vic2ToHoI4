#ifndef OUT_SCRIPTED_LOCALISATION_H
#define OUT_SCRIPTED_LOCALISATION_H



#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisation.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const ScriptedLocalisation& localisation);

}



#endif // OUT_SCRIPTED_LOCALISATION_H