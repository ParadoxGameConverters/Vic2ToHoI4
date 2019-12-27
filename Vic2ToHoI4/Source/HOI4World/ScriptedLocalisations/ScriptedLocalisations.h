#ifndef SCRIPTED_LOCALISATIONS_H
#define SCRIPTED_LOCALISATIONS_H



#include "ScriptedLocalisation.h"
#include <vector>



namespace HoI4
{

class ScriptedLocalisations
{
	public:
		void initialize(const std::string& strongestNavyTag, const std::string& secondStrongestNavyTag);

		std::vector<ScriptedLocalisation> getLocalisations() const { return scriptedLocalistions; }

	private:
		std::vector<ScriptedLocalisation> scriptedLocalistions;
};

}



#endif // SCRIPTED_LOCALISATIONS_H