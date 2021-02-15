#include "GovernmentMapper.h"
#include "GovernmentMappingFactory.h"
#include "Log.h"
#include "PartyMappingFactory.h"
#include "V2World/Countries/Country.h"



class governmentMappings: commonItems::parser
{
  public:
	explicit governmentMappings(std::istream& theStream);

	auto getGovernmentMap() const { return governmentMap; }

  private:
	Mappers::GovernmentMappingFactory governmentMappingFactory;
	std::vector<Mappers::GovernmentMapping> governmentMap;
};


governmentMappings::governmentMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		governmentMap.push_back(*governmentMappingFactory.importMapping(theStream));
	});

	parseStream(theStream);
}


class partyMappings: commonItems::parser
{
  public:
	explicit partyMappings(std::istream& theStream);

	auto getPartyMap() const { return partyMap; }

  private:
	Mappers::PartyMappingFactory partyMappingFactory;
	std::vector<Mappers::PartyMapping> partyMap;
};


partyMappings::partyMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		partyMap.push_back(*partyMappingFactory.importPartyMapping(theStream));
	});

	parseStream(theStream);
}


void governmentMapper::init()
{
	Log(LogLevel::Info) << "\tParsing governments mappings";

	registerKeyword("government_mappings", [this](std::istream& theStream) {
		governmentMappings mappings(theStream);
		governmentMap = mappings.getGovernmentMap();
	});
	registerKeyword("party_mappings", [this](std::istream& theStream) {
		partyMappings mappings(theStream);
		partyMap = mappings.getPartyMap();
	});

	parseFile("Configurables/governmentMapping.txt");
}


std::string governmentMapper::getIdeologyForCountry(const std::string& sourceTag,
	 const std::string& sourceGovernment,
	 const std::string& Vic2RulingIdeology,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
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


std::string governmentMapper::getLeaderIdeologyForCountry(const std::string& sourceTag,
	 const std::string& sourceGovernment,
	 const std::string& Vic2RulingIdeology,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
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


std::string governmentMapper::getExistingIdeologyForCountry(const std::string& tag,
	 const std::string& government,
	 const std::string& Vic2RulingIdeology,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
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


std::string governmentMapper::getExistingLeaderIdeologyForCountry(const std::string& tag,
	 const std::string& government,
	 const std::string& Vic2RulingIdeology,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
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


bool governmentMapper::governmentMatches(const Mappers::GovernmentMapping& mapping, const std::string& government) const
{
	return ((mapping.vic2Government.empty()) || (mapping.vic2Government == government));
}


bool governmentMapper::rulingIdeologyMatches(const Mappers::GovernmentMapping& mapping,
	 const std::string& rulingIdeology) const
{
	return ((mapping.rulingPartyRequired.empty()) || (mapping.rulingPartyRequired == rulingIdeology));
}


bool governmentMapper::tagMatches(const Mappers::GovernmentMapping& mapping, const std::string& tag) const
{
	return ((mapping.tagRequired.empty()) || (mapping.tagRequired == tag));
}


bool governmentMapper::ideologyIsValid(const Mappers::GovernmentMapping& mapping,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies)
{
	return majorIdeologies.contains(mapping.hoI4GovernmentIdeology) &&
			 ideologies.subIdeologyIsValid(mapping.hoI4GovernmentIdeology, mapping.hoI4LeaderIdeology);
}


std::string governmentMapper::getSupportedIdeology(const std::string& rulingIdeology,
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