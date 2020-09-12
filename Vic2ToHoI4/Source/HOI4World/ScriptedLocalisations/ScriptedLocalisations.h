#ifndef SCRIPTED_LOCALISATIONS_H
#define SCRIPTED_LOCALISATIONS_H



#include "ScriptedLocalisation.h"
#include <map>
#include <set>
#include <vector>



namespace HoI4
{

class ScriptedLocalisations
{
  public:
	class Factory;
	void addNavyScriptedLocalisations(const std::string& strongestNavyTag, const std::string& secondStrongestNavyTag);
	void giveAdjectiveLocalisation(const std::string& language, ScriptedLocalisation&& localisation);
	void filterIdeologyLocalisations(const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getLocalisations() const { return scriptedLocalisations; }
	[[nodiscard]] const auto& getIdeologyLocalisations() const { return ideologyLocalisations; }
	[[nodiscard]] const auto& getAdjectiveLocalisations() const { return adjectiveLocalisations; }

  private:
	std::vector<ScriptedLocalisation> scriptedLocalisations;
	std::vector<ScriptedLocalisation> ideologyLocalisations;
	std::map<std::string, std::vector<ScriptedLocalisation>> adjectiveLocalisations;
};

} // namespace HoI4



#endif // SCRIPTED_LOCALISATIONS_H