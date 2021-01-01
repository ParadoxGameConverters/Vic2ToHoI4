#include "CountryMapping.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "V2World/World/World.h"
#include <iomanip>



class countryMappingRule: commonItems::parser
{
  public:
	explicit countryMappingRule(std::istream& theStream);

	std::string getVic2Tag() const { return Vic2Tag; }
	std::vector<std::string> getHoI4Tags() const { return HoI4Tags; }

  private:
	std::string Vic2Tag;
	std::vector<std::string> HoI4Tags;
};


countryMappingRule::countryMappingRule(std::istream& theStream)
{
	registerKeyword("vic", [this](std::istream& theStream) {
		commonItems::singleString mapping(theStream);
		Vic2Tag = mapping.getString();
	});
	registerKeyword("hoi", [this](std::istream& theStream) {
		commonItems::singleString mapping(theStream);
		HoI4Tags.push_back(mapping.getString());
	});

	parseStream(theStream);
}


CountryMapper::CountryMapper(const Vic2::World& srcWorld, bool debug)
{
	Log(LogLevel::Info) << "Getting country mappings";
	readRules();
	createMappings(srcWorld, debug);
}


void CountryMapper::readRules()
{
	registerKeyword("link", [this](std::istream& theStream) {
		countryMappingRule rule(theStream);
		Vic2TagToHoI4TagsRules.insert(make_pair(rule.getVic2Tag(), rule.getHoI4Tags()));
	});

	Log(LogLevel::Info) << "\tReading country mapping rules";
	parseFile("Configurables/country_mappings.txt");
}


void CountryMapper::createMappings(const Vic2::World& srcWorld, bool debug)
{
	Log(LogLevel::Info) << "\tCreating country mappings";
	resetMappingData();

	for (const auto& [tag, unused]: srcWorld.getCountries())
	{
		makeOneMapping(tag, debug);
	}
}


void CountryMapper::resetMappingData()
{
	generatedHoI4TagPrefix = 'X';
	generatedHoI4TagSuffix = 0;
}


void CountryMapper::makeOneMapping(const std::string& Vic2Tag, bool debug)
{
	auto mappingRule = Vic2TagToHoI4TagsRules.find(Vic2Tag);

	bool mapped = false;
	if (mappingRule != Vic2TagToHoI4TagsRules.end())
	{
		auto possibleHoI4Tags = mappingRule->second;
		mapped = mapToFirstUnusedVic2Tag(possibleHoI4Tags, Vic2Tag, debug);
	}

	if (!mapped)
	{
		std::string HoI4Tag = generateNewHoI4Tag(Vic2Tag);
		mapToNewTag(Vic2Tag, HoI4Tag, debug);
	}
}


bool CountryMapper::mapToFirstUnusedVic2Tag(const std::vector<std::string>& possibleHoI4Tags,
	 const std::string& Vic2Tag,
	 bool debug)
{
	for (auto possibleHoI4Tag: possibleHoI4Tags)
	{
		if (!tagIsAlreadyAssigned(possibleHoI4Tag))
		{
			V2TagToHoI4TagMap.insert(make_pair(Vic2Tag, possibleHoI4Tag));
			HoI4TagToV2TagMap.insert(make_pair(possibleHoI4Tag, Vic2Tag));
			if (debug)
			{
				logMapping(Vic2Tag, possibleHoI4Tag, "mapping rule");
			}

			return true;
		}
	}

	return false;
}


std::string CountryMapper::generateNewHoI4Tag(const std::string& Vic2Tag)
{
	std::ostringstream generatedHoI4TagStream;
	generatedHoI4TagStream << generatedHoI4TagPrefix << std::setfill('0') << std::setw(2) << generatedHoI4TagSuffix;
	std::string newTag = generatedHoI4TagStream.str();

	++generatedHoI4TagSuffix;
	if (generatedHoI4TagSuffix > 99)
	{
		generatedHoI4TagSuffix = 0;
		--generatedHoI4TagPrefix;
	}

	return newTag;
}


void CountryMapper::mapToNewTag(const std::string& Vic2Tag, const std::string& HoI4Tag, bool debug)
{
	V2TagToHoI4TagMap.insert(make_pair(Vic2Tag, HoI4Tag));
	HoI4TagToV2TagMap.insert(make_pair(HoI4Tag, Vic2Tag));
	if (debug)
	{
		logMapping(Vic2Tag, HoI4Tag, "generated tag");
	}
}


void CountryMapper::logMapping(const std::string& sourceTag,
	 const std::string& targetTag,
	 const std::string& reason) const
{
	Log(LogLevel::Debug) << "Mapping " << sourceTag << " -> " << targetTag << " (" << reason << ')';
}


bool CountryMapper::tagIsAlreadyAssigned(const std::string& HoI4Tag) const
{
	return (HoI4TagToV2TagMap.contains(HoI4Tag));
}


std::optional<std::string> CountryMapper::getHoI4Tag(const std::string& V2Tag) const
{
	auto findIter = V2TagToHoI4TagMap.find(V2Tag);
	if (findIter != V2TagToHoI4TagMap.end())
	{
		return findIter->second;
	}
	else
	{
		return {};
	}
}


std::optional<std::string> CountryMapper::getVic2Tag(const std::string& HoI4Tag) const
{
	auto findIter = HoI4TagToV2TagMap.find(HoI4Tag);
	if (findIter != HoI4TagToV2TagMap.end())
	{
		return findIter->second;
	}
	else
	{
		return {};
	}
}