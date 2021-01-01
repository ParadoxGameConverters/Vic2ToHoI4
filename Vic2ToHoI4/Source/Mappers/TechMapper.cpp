#include "TechMapper.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



class techMapping: commonItems::parser
{
  public:
	explicit techMapping(std::istream& theStream);

	auto getKey() const { return key; }
	auto getValues() const { return values; }

  private:
	std::string key;
	std::set<std::string> values;
};


techMapping::techMapping(std::istream& theStream)
{
	registerKeyword("vic2", [this](std::istream& theStream) {
		commonItems::singleString theKey(theStream);
		key = theKey.getString();
	});
	registerKeyword("hoi4", [this](std::istream& theStream) {
		commonItems::singleString aValue(theStream);
		values.insert(aValue.getString());
	});

	parseStream(theStream);
}


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
	std::map<std::string, std::set<std::string>> mappings;
};


techMap::techMap(std::istream& theStream)
{
	registerKeyword("link", [this](std::istream& theStream) {
		techMapping theMapping(theStream);
		mappings.insert(make_pair(theMapping.getKey(), theMapping.getValues()));
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
	std::map<std::string, std::set<std::string>> techMappings;
	std::map<std::string, std::set<std::string>> nonMtgNavalTechMappings;
	std::map<std::string, std::set<std::string>> mtgNavalTechMappings;
	std::map<std::string, std::map<std::string, float>> researchBonusMappings;

	registerKeyword("tech_map", [this, &techMappings](std::istream& theStream) {
		techMap theTechMap(theStream);
		techMappings = theTechMap.getMappings();
	});
	registerKeyword("non_mtg_naval_tech_map", [this, &nonMtgNavalTechMappings](std::istream& theStream) {
		techMap theTechMap(theStream);
		nonMtgNavalTechMappings = theTechMap.getMappings();
	});
	registerKeyword("mtg_naval_tech_map", [this, &mtgNavalTechMappings](std::istream& theStream) {
		techMap theTechMap(theStream);
		mtgNavalTechMappings = theTechMap.getMappings();
	});
	registerKeyword("bonus_map", [this, &researchBonusMappings](std::istream& theStream) {
		researchBonusMap theBonusMap(theStream);
		researchBonusMappings = theBonusMap.getMappings();
	});

	parseFile("Configurables/tech_mapping.txt");
	theTechMapper =
		 std::make_unique<techMapper>(techMappings, nonMtgNavalTechMappings, mtgNavalTechMappings, researchBonusMappings);
}