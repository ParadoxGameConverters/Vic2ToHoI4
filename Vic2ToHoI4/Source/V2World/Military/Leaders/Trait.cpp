#include "Trait.h"
#include "ParserHelpers.h"
#include "Log.h"



std::unordered_map<std::string, float> Vic2::getTraitEffects(std::istream& theStream)
{
	const commonItems::assignments rawEffects(theStream);

	std::unordered_map<std::string, float> effects;
	for (const auto& [name, amountString]: rawEffects.getAssignments())
	{
		try
		{
			effects.insert(std::make_pair(name, stof(amountString)));
		}
		catch (std::exception& e)
		{
			Log(LogLevel::Warning) << "Trait effect amount couldn't be parsed";
		}
	}
	
	return effects;
}