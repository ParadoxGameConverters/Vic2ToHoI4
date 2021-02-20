#include "PartyMapper.h"



std::string Mappers::PartyMapper::getSupportedIdeology(const std::string& rulingIdeology,
                                                       const std::string& Vic2Ideology,
                                                       const std::set<std::string>& majorIdeologies) const
{
	std::string ideology = "neutrality";
	for (auto mapping: partyMap)
	{
		if ((rulingIdeology == mapping.rulingIdeology) && (Vic2Ideology == mapping.vic2Ideology) &&
			 majorIdeologies.contains(mapping.supportedIdeology))
		{
			ideology = mapping.supportedIdeology;
			break;
		}
	}

	return ideology;
}