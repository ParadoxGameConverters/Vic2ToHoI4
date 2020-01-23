#ifndef SCRIPTED_LOCALISATIONS_H
#define SCRIPTED_LOCALISATIONS_H



#include "ScriptedLocalisation.h"
#include <map>
#include <vector>



namespace HoI4
{

class ScriptedLocalisations
{
	public:
		void initialize(const std::string& strongestNavyTag, const std::string& secondStrongestNavyTag);

		void giveAdjectiveLocalisation(const std::string& language, ScriptedLocalisation&& localisation);

		[[nodiscard]] std::vector<ScriptedLocalisation> getLocalisations() const { return scriptedLocalisations; }
		[[nodiscard]] std::map<std::string, std::vector<ScriptedLocalisation>> getAdjectiveLocalisations() const
		{
			return adjectiveLocalisations;
		}

	private:
		std::vector<ScriptedLocalisation> scriptedLocalisations;
		std::map<std::string, std::vector<ScriptedLocalisation>> adjectiveLocalisations;
};

}



#endif // SCRIPTED_LOCALISATIONS_H