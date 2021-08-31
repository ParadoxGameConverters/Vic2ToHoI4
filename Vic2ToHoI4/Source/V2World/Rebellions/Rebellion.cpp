#include "Rebellion.h"



#include <map>



std::optional<std::string> Vic2::Rebellion::getIdeology() const
{
	const std::map<std::string, std::string>& theMap = {{"reactionary_rebels", "absolutist"},
		 {"fascist_rebels", "fascism"},
		 {"communist_rebels", "communism"},
		 {"anarcho_liberal_rebels", "radical"},
		 {"carlist_rebels", "absolutist"},
		 {"boxer_rebels", "absolutist"},
		 {"liberal_rebels", "democratic"},
		 {"unciv_reactionary_rebels", "absolutist"},
		 // HPM
		 {"christino_rebels", "democratic"},
		 {"socialist_rebels", "communism"},
		 {"turkish_nationalist_rebels", "democratic"},
		 {"native_rebels", "democratic"}};

	if (theMap.contains(type))
	{
		return theMap.at(type);
	}
	else
	{
		return std::nullopt;
	}
}