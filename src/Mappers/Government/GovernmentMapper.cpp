#include "GovernmentMapper.h"
#include "GovernmentMappingFactory.h"
#include "external/common_items/Log.h"
#include "V2World/Countries/Country.h"



namespace
{

bool governmentMatches(const Mappers::GovernmentMapping& mapping, const std::string& government)
{
	return mapping.vic2Government.empty() || (mapping.vic2Government == government);
}


bool rulingIdeologyMatches(const Mappers::GovernmentMapping& mapping, const std::string& rulingIdeology)
{
	return mapping.rulingPartyRequired.empty() || (mapping.rulingPartyRequired == rulingIdeology);
}


bool tagMatches(const Mappers::GovernmentMapping& mapping, const std::string& tag)
{
	return mapping.tagRequired.empty() || (mapping.tagRequired == tag);
}


bool ideologyIsValid(const Mappers::GovernmentMapping& mapping,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies)
{
	return majorIdeologies.contains(mapping.hoI4GovernmentIdeology) &&
			 ideologies.subIdeologyIsValid(mapping.hoI4GovernmentIdeology, mapping.hoI4LeaderIdeology);
}

} // namespace



std::string Mappers::GovernmentMapper::getIdeologyForCountry(const std::string& sourceTag,
	 const std::string& sourceGovernment,
	 const std::string& Vic2RulingIdeology,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (const auto& mapping: governmentMap)
	{
		if (governmentMatches(mapping, sourceGovernment) && rulingIdeologyMatches(mapping, Vic2RulingIdeology) &&
			 tagMatches(mapping, sourceTag))
		{
			ideology = mapping.hoI4GovernmentIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << sourceTag << " government " << sourceGovernment << " to " << ideology;
	}
	return ideology;
}


std::string Mappers::GovernmentMapper::getLeaderIdeologyForCountry(const std::string& sourceTag,
	 const std::string& sourceGovernment,
	 const std::string& Vic2RulingIdeology,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (const auto& mapping: governmentMap)
	{
		if (governmentMatches(mapping, sourceGovernment) && rulingIdeologyMatches(mapping, Vic2RulingIdeology) &&
			 tagMatches(mapping, sourceTag))
		{
			ideology = mapping.hoI4LeaderIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << sourceTag << " leader " << sourceGovernment << " to " << ideology;
	}
	return ideology;
}


std::string Mappers::GovernmentMapper::getExistingIdeologyForCountry(const std::string& tag,
	 const std::string& government,
	 const std::string& Vic2RulingIdeology,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (const auto& mapping: governmentMap)
	{
		if (governmentMatches(mapping, government) && rulingIdeologyMatches(mapping, Vic2RulingIdeology) &&
			 tagMatches(mapping, tag) && ideologyIsValid(mapping, majorIdeologies, ideologies))
		{
			ideology = mapping.hoI4GovernmentIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << tag << " government " << government << " to " << ideology;
	}
	return ideology;
}


std::string Mappers::GovernmentMapper::getExistingLeaderIdeologyForCountry(const std::string& tag,
	 const std::string& government,
	 const std::string& Vic2RulingIdeology,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies,
	 bool debug) const
{
	std::string ideology = "dictatorship_neutral";
	for (const auto& mapping: governmentMap)
	{
		if (governmentMatches(mapping, government) && rulingIdeologyMatches(mapping, Vic2RulingIdeology) &&
			 tagMatches(mapping, tag) && ideologyIsValid(mapping, majorIdeologies, ideologies))
		{
			ideology = mapping.hoI4LeaderIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << tag << " leader " << government << " to " << ideology;
	}
	return ideology;
}