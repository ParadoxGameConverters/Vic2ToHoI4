#ifndef SCRIPTED_LOCALISATIONS_H
#define SCRIPTED_LOCALISATIONS_H



#include "ScriptedLocalisation.h"
#include <vector>



namespace HoI4
{

class ScriptedLocalisations
{
	public:
		ScriptedLocalisations();
		std::vector<ScriptedLocalisation> getLocalisations() const { return scriptedLocalistions; }

	private:
		std::vector<ScriptedLocalisation> scriptedLocalistions;
};

}



#endif // SCRIPTED_LOCALISATIONS_H