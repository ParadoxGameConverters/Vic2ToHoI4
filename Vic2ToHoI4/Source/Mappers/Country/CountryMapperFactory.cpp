#include "CountryMapperFactory.h"
#include "Log.h"
#include <iomanip>



namespace
{

void logMapping(const std::string& sourceTag, const std::string& targetTag, const std::string& reason)
{
	Log(LogLevel::Debug) << "Mapping " << sourceTag << " -> " << targetTag << " (" << reason << ')';
}

} // namespace



Mappers::CountryMapper::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		countryMapper->Vic2TagToHoI4TagsRules.insert(countryMappingRuleFactory.importMapping(theStream));
	});
}


std::unique_ptr<Mappers::CountryMapper> Mappers::CountryMapper::Factory::importCountryMapper(
	 const Vic2::World& srcWorld,
	 bool debug)
{
	Log(LogLevel::Info) << "Getting country mappings";

	countryMapper = std::make_unique<CountryMapper>();
	readRules();
	createMappings(srcWorld, debug);

	return std::move(countryMapper);
}


void Mappers::CountryMapper::Factory::readRules()
{
	Log(LogLevel::Info) << "\tReading country mapping rules";
	parseFile("Configurables/country_mappings.txt");
}


void Mappers::CountryMapper::Factory::createMappings(const Vic2::World& srcWorld, bool debug)
{
	Log(LogLevel::Info) << "\tCreating country mappings";
	resetMappingData();

	for (const auto& [tag, unused]: srcWorld.getCountries())
	{
		makeOneMapping(tag, debug);
	}
}


void Mappers::CountryMapper::Factory::resetMappingData()
{
	generatedHoI4TagPrefix = 'X';
	generatedHoI4TagSuffix = 0;
}


void Mappers::CountryMapper::Factory::makeOneMapping(const std::string& Vic2Tag, bool debug)
{
	if (const auto mappingRule = countryMapper->Vic2TagToHoI4TagsRules.find(Vic2Tag);
		 mappingRule != countryMapper->Vic2TagToHoI4TagsRules.end())
	{
		const auto& possibleHoI4Tag = mappingRule->second;
		if (!tagIsAlreadyAssigned(possibleHoI4Tag))
		{
			countryMapper->V2TagToHoI4TagMap.insert(make_pair(Vic2Tag, possibleHoI4Tag));
			countryMapper->HoI4TagToV2TagMap.insert(make_pair(possibleHoI4Tag, Vic2Tag));
			if (debug)
			{
				logMapping(Vic2Tag, possibleHoI4Tag, "mapping rule");
			}
			return;
		}
	}

	mapToNewTag(Vic2Tag, generateNewHoI4Tag(), debug);
}


bool Mappers::CountryMapper::Factory::tagIsAlreadyAssigned(const std::string& HoI4Tag) const
{
	return countryMapper->HoI4TagToV2TagMap.contains(HoI4Tag);
}


std::string Mappers::CountryMapper::Factory::generateNewHoI4Tag()
{
	std::ostringstream generatedHoI4TagStream;
	generatedHoI4TagStream << generatedHoI4TagPrefix << std::setfill('0') << std::setw(2) << generatedHoI4TagSuffix;
	auto newTag = generatedHoI4TagStream.str();

	++generatedHoI4TagSuffix;
	if (generatedHoI4TagSuffix > 99)
	{
		generatedHoI4TagSuffix = 0;
		--generatedHoI4TagPrefix;
	}

	return newTag;
}


void Mappers::CountryMapper::Factory::mapToNewTag(const std::string& Vic2Tag, const std::string& HoI4Tag, bool debug)
{
	countryMapper->V2TagToHoI4TagMap.insert(make_pair(Vic2Tag, HoI4Tag));
	countryMapper->HoI4TagToV2TagMap.insert(make_pair(HoI4Tag, Vic2Tag));
	if (debug)
	{
		logMapping(Vic2Tag, HoI4Tag, "generated tag");
	}
}