#include "GovernmentMapper.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "V2World/Country.h"



class aGovernmentMapping: commonItems::parser
{
  public:
	explicit aGovernmentMapping(std::istream& theStream);

	auto getMapping() const { return mapping; }

  private:
	governmentMapping mapping;
};


aGovernmentMapping::aGovernmentMapping(std::istream& theStream)
{
	registerKeyword("vic", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString vic2Government(theStream);
		mapping.vic2Government = vic2Government.getString();
	});
	registerKeyword("ruling_party", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString rulingParty(theStream);
		mapping.rulingPartyRequired = rulingParty.getString();
	});
	registerKeyword("hoi_gov", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString hoi4Government(theStream);
		mapping.HoI4GovernmentIdeology = hoi4Government.getString();
	});
	registerKeyword("hoi_leader", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString hoi4Leader(theStream);
		mapping.HoI4LeaderIdeology = hoi4Leader.getString();
	});

	parseStream(theStream);
}


class governmentMappings: commonItems::parser
{
  public:
	explicit governmentMappings(std::istream& theStream);

	auto getGovernmentMap() const { return governmentMap; }

  private:
	std::vector<governmentMapping> governmentMap;
};


governmentMappings::governmentMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](const std::string& unused, std::istream& theStream) {
		aGovernmentMapping mapping(theStream);
		governmentMap.push_back(mapping.getMapping());
	});

	parseStream(theStream);
}


class aPartyMapping: commonItems::parser
{
  public:
	explicit aPartyMapping(std::istream& theStream);

	auto getMapping() const { return mapping; }

  private:
	partyMapping mapping;
};


aPartyMapping::aPartyMapping(std::istream& theStream)
{
	registerKeyword("ruling_ideology", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		mapping.rulingIdeology = ideologyString.getString();
	});
	registerKeyword("vic2_ideology", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		mapping.vic2Ideology = ideologyString.getString();
	});
	registerKeyword("supported_ideology", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		mapping.supportedIdeology = ideologyString.getString();
	});

	parseStream(theStream);
}


class partyMappings: commonItems::parser
{
  public:
	explicit partyMappings(std::istream& theStream);

	auto getPartyMap() const { return partyMap; }

  private:
	std::vector<partyMapping> partyMap;
};


partyMappings::partyMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](const std::string& unused, std::istream& theStream) {
		aPartyMapping mapping(theStream);
		partyMap.push_back(mapping.getMapping());
	});

	parseStream(theStream);
}


void governmentMapper::init()
{
	Log(LogLevel::Info) << "\tParsing governments mappings";

	registerKeyword("government_mappings", [this](const std::string& unused, std::istream& theStream) {
		governmentMappings mappings(theStream);
		governmentMap = mappings.getGovernmentMap();
	});
	registerKeyword("party_mappings", [this](const std::string& unused, std::istream& theStream) {
		partyMappings mappings(theStream);
		partyMap = mappings.getPartyMap();
	});

	parseFile("governmentMapping.txt");
}


std::string governmentMapper::getIdeologyForCountry(const std::string& sourceTag,
	 const std::string& sourceGovernment,
	 const std::string& Vic2RulingIdeology,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
	{
		if (governmentMatches(mapping, sourceGovernment) && rulingIdeologyMatches(mapping, Vic2RulingIdeology))
		{
			ideology = mapping.HoI4GovernmentIdeology;
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
		if (governmentMatches(mapping, sourceGovernment) && rulingIdeologyMatches(mapping, Vic2RulingIdeology))
		{
			ideology = mapping.HoI4LeaderIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << sourceTag << " leader " << sourceGovernment << " to " << ideology;
	}
	return ideology;
}


std::string governmentMapper::getExistingIdeologyForCountry(const Vic2::Country& country,
	 const std::string& Vic2RulingIdeology,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
	{
		if (governmentMatches(mapping, country.getGovernment()) && rulingIdeologyMatches(mapping, Vic2RulingIdeology) &&
			 ideologyIsValid(mapping, majorIdeologies, ideologies))
		{
			ideology = mapping.HoI4GovernmentIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << country.getTag() << " government " << country.getGovernment() << " to "
									<< ideology;
	}
	return ideology;
}


std::string governmentMapper::getExistingLeaderIdeologyForCountry(const Vic2::Country& country,
	 const std::string& Vic2RulingIdeology,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies,
	 bool debug) const
{
	std::string ideology = "neutrality";
	for (auto mapping: governmentMap)
	{
		if (governmentMatches(mapping, country.getGovernment()) && rulingIdeologyMatches(mapping, Vic2RulingIdeology) &&
			 ideologyIsValid(mapping, majorIdeologies, ideologies))
		{
			ideology = mapping.HoI4LeaderIdeology;
			break;
		}
	}

	if (debug)
	{
		Log(LogLevel::Debug) << "\t\tMapped " << country.getTag() << " leader " << country.getGovernment() << " to "
									<< ideology;
	}
	return ideology;
}


bool governmentMapper::governmentMatches(const governmentMapping& mapping, const std::string& government) const
{
	return ((mapping.vic2Government.empty()) || (mapping.vic2Government == government));
}


bool governmentMapper::rulingIdeologyMatches(const governmentMapping& mapping, const std::string& rulingIdeology) const
{
	return ((mapping.rulingPartyRequired.empty()) || (mapping.rulingPartyRequired == rulingIdeology));
}


bool governmentMapper::ideologyIsValid(const governmentMapping& mapping,
	 const std::set<std::string>& majorIdeologies,
	 const HoI4::Ideologies& ideologies)
{
	return majorIdeologies.contains(mapping.HoI4GovernmentIdeology) &&
			 ideologies.subIdeologyIsValid(mapping.HoI4GovernmentIdeology, mapping.HoI4LeaderIdeology);
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