#include "CountryMapping.h"
#include "CountryMappingRuleFactory.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "V2World/World/World.h"
#include <iomanip>



CountryMapper::CountryMapper(const Vic2::World& srcWorld, bool debug)
{
	Log(LogLevel::Info) << "Getting country mappings";
	readRules();
	createMappings(srcWorld, debug);
}


void CountryMapper::readRules()
{
	Mappers::CountryMappingRuleFactory countryMappingRuleFactory;
	registerKeyword("link", [this, &countryMappingRuleFactory](std::istream& theStream) {
		Vic2TagToHoI4TagsRules.insert(countryMappingRuleFactory.importMapping(theStream));
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
		const auto& possibleHoI4Tag = mappingRule->second;
		if (!tagIsAlreadyAssigned(possibleHoI4Tag))
		{
			V2TagToHoI4TagMap.insert(make_pair(Vic2Tag, possibleHoI4Tag));
			HoI4TagToV2TagMap.insert(make_pair(possibleHoI4Tag, Vic2Tag));
			if (debug)
			{
				logMapping(Vic2Tag, possibleHoI4Tag, "mapping rule");
			}
			mapped = true;
		}
	}

	if (!mapped)
	{
		std::string HoI4Tag = generateNewHoI4Tag(Vic2Tag);
		mapToNewTag(Vic2Tag, HoI4Tag, debug);
	}
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