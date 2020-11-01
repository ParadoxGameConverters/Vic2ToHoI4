#include "Trait.h"
#include "Log.h"
#include "ParserHelpers.h"



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
		catch (const std::exception&)
		{
			Log(LogLevel::Warning) << "Trait effect amount couldn't be parsed";
		}
	}

	return effects;
}