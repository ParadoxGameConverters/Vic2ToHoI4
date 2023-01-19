#include "src/Mappers/CasusBelli/CasusBellis.h"



std::string Mappers::CasusBellis::getWarGoalFromCasusBelli(const std::string& casusBelli) const
{
	if (const auto& mapping = casusBelliToWarGoalMap_.find(casusBelli); mapping != casusBelliToWarGoalMap_.end())
	{
		return mapping->second;
	}

	return "topple_government";
}