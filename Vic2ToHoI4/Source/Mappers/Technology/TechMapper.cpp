#include "TechMapper.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "TechMappingFactory.h"



class researchBonusMapping: commonItems::parser
{
  public:
	explicit researchBonusMapping(std::istream& theStream);

	auto getKey() const { return key; }
	auto getValues() const { return values; }

  private:
	std::string key;
	std::map<std::string, float> values;
};


researchBonusMapping::researchBonusMapping(std::istream& theStream)
{
	registerKeyword("vic2", [this](std::istream& theStream) {
		commonItems::singleString theKey(theStream);
		key = theKey.getString();
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& valueName, std::istream& theStream) {
		commonItems::singleDouble aValue(theStream);
		values.insert(std::make_pair(valueName, aValue.getDouble()));
	});

	parseStream(theStream);
}


class techMap: commonItems::parser
{
  public:
	explicit techMap(std::istream& theStream);

	auto getMappings() const { return mappings; }

  private:
	std::map<std::string, std::map<std::string, std::set<std::string>>> mappings;
};


techMap::techMap(std::istream& theStream)
{
	Mappers::TechMapping::Factory techMappingFactory;

	registerKeyword("link", [this, &techMappingFactory](std::istream& theStream) {
		const auto theMapping = techMappingFactory.importTechMapping(theStream);
		const auto& techs = theMapping->getTechs();
		const auto techsByLimit = std::make_pair(theMapping->getLimit(), techs);

		auto [itr, inserted] = mappings.insert(std::make_pair(theMapping->getVic2Item(), std::map{techsByLimit}));
		if (!inserted)
		{
			auto [itr2, inserted2] = itr->second.insert(techsByLimit);
			if (!inserted2)
			{
				itr2->second.insert(techs.begin(), techs.end());
			}
		}
	});

	parseStream(theStream);
}


class researchBonusMap: commonItems::parser
{
  public:
	explicit researchBonusMap(std::istream& theStream);

	auto getMappings() const { return mappings; }

  private:
	std::map<std::string, std::map<std::string, float>> mappings;
};


researchBonusMap::researchBonusMap(std::istream& theStream)
{
	registerKeyword("link", [this](std::istream& theStream) {
		researchBonusMapping theMapping(theStream);
		mappings.insert(make_pair(theMapping.getKey(), theMapping.getValues()));
	});

	parseStream(theStream);
}


mappers::techMapperFile::techMapperFile()
{
	std::map<std::string, std::map<std::string, std::set<std::string>>> techMappings;
	std::map<std::string, std::map<std::string, float>> researchBonusMappings;

	registerKeyword("tech_map", [this, &techMappings](std::istream& theStream) {
		techMap theTechMap(theStream);
		techMappings = theTechMap.getMappings();
	});
	registerKeyword("bonus_map", [this, &researchBonusMappings](std::istream& theStream) {
		researchBonusMap theBonusMap(theStream);
		researchBonusMappings = theBonusMap.getMappings();
	});

	parseFile("Configurables/tech_mapping.txt");
	theTechMapper = std::make_unique<techMapper>(techMappings, researchBonusMappings);
}