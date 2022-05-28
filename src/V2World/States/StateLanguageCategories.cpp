#include "StateLanguageCategories.h"



std::optional<std::string> Vic2::StateLanguageCategories::getStateCategory(const std::string& stateName) const
{
	if (!categories.contains(stateName))
	{
		return std::nullopt;
	}

	return categories.at(stateName);
}