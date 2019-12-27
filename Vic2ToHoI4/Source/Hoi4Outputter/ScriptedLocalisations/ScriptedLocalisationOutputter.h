#ifndef SCRIPTED_LOCALISATION_OUTPUTTER_H
#define SCRIPTED_LOCALISATION_OUTPUTTER_H



#include "../../HOI4World/ScriptedLocalisations/ScriptedLocalisation.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const ScriptedLocalisation& localisation);
	
}



#endif // SCRIPTED_LOCALISATION_OUTPUTTER_H