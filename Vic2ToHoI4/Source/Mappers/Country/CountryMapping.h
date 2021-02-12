#ifndef COUNTRY_MAPPING_H
#define COUNTRY_MAPPING_H



#include "Parser.h"
#include "V2World/World/World.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



class CountryMapper: commonItems::parser
{
  public:
	CountryMapper() = default;
	~CountryMapper() = default;

	class Builder;

	explicit CountryMapper(const Vic2::World& srcWorld, bool debug);

	std::optional<std::string> getHoI4Tag(const std::string& V2Tag) const;
	std::optional<std::string> getVic2Tag(const std::string& HoI4Tag) const;

  private:
	CountryMapper(const CountryMapper&) = delete;
	CountryMapper& operator=(const CountryMapper&) = delete;

	void readRules();

	void createMappings(const Vic2::World& srcWorld, bool debug);
	void resetMappingData();
	void makeOneMapping(const std::string& Vic2Tag, bool debug);
	std::string generateNewHoI4Tag(const std::string& Vic2Tag);
	void mapToNewTag(const std::string& Vic2Tag, const std::string& HoI4Tag, bool debug);
	void logMapping(const std::string& sourceTag, const std::string& targetTag, const std::string& reason) const;
	bool tagIsAlreadyAssigned(const std::string& HoI4Tag) const;

	std::map<std::string, std::string> Vic2TagToHoI4TagsRules;
	std::map<std::string, std::string> V2TagToHoI4TagMap;
	std::map<std::string, std::string> HoI4TagToV2TagMap;

	char generatedHoI4TagPrefix = 'X';
	int generatedHoI4TagSuffix = 0;
};



#endif // COUNTRY_MAPPING_H