#include "src/Mappers/Ideology/IdeologyMapper.h"



std::string Mappers::IdeologyMapper::getSupportedIdeology(const std::string& rulingIdeology,
	 const std::string& Vic2Ideology,
	 const std::set<std::string>& majorIdeologies) const
{
	for (const auto& mapping: ideologyMap)
	{
		if ((rulingIdeology == mapping.rulingIdeology) && (Vic2Ideology == mapping.vic2Ideology) &&
			 majorIdeologies.contains(mapping.supportedIdeology))
		{
			return mapping.supportedIdeology;
		}
	}

	return "neutrality";
}