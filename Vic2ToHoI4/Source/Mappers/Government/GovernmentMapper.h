#ifndef GOVERNMENT_MAPPER_H
#define GOVERNMENT_MAPPER_H



#include "HOI4World/Ideologies/Ideologies.h"
#include "Parser.h"
#include <set>
#include <string>
#include <vector>



typedef struct governmentMapping
{
	std::string vic2Government;
	std::string tagRequired;
	std::string HoI4GovernmentIdeology;
	std::string HoI4LeaderIdeology;
	std::string rulingPartyRequired;
} governmentMapping;



typedef struct partyMapping
{
	std::string rulingIdeology;
	std::string vic2Ideology;
	std::string supportedIdeology;
} partyMapping;


class governmentMapper: commonItems::parser
{
  public:
	governmentMapper() = default;
	void init();
	~governmentMapper() = default;

	class Builder;

	std::string getIdeologyForCountry(const std::string& sourceTag,
		 const std::string& sourceGovernment,
		 const std::string& Vic2RulingIdeology,
		 bool debug) const;
	std::string getLeaderIdeologyForCountry(const std::string& sourceTag,
		 const std::string& sourceGovernment,
		 const std::string& Vic2RulingIdeology,
		 bool debug) const;
	std::string getExistingIdeologyForCountry(const std::string& tag,
		 const std::string& government,
		 const std::string& Vic2RulingIdeology,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::Ideologies& ideologies,
		 bool debug) const;
	std::string getExistingLeaderIdeologyForCountry(const std::string& tag,
		 const std::string& government,
		 const std::string& Vic2RulingIdeology,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::Ideologies& ideologies,
		 bool debug) const;
	std::string getSupportedIdeology(const std::string& rulingIdeology,
		 const std::string& Vic2Ideology,
		 const std::set<std::string>& majorIdeologies) const;

	auto getGovernmentMappings() const { return governmentMap; }

  private:
	governmentMapper(const governmentMapper&) = delete;
	governmentMapper& operator=(const governmentMapper&) = delete;

	bool governmentMatches(const governmentMapping& mapping, const std::string& government) const;
	bool rulingIdeologyMatches(const governmentMapping& mapping, const std::string& rulingIdeology) const;
	bool tagMatches(const governmentMapping& mapping, const std::string& tag) const;
	static bool ideologyIsValid(const governmentMapping& mapping,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::Ideologies& ideologies);

	std::vector<governmentMapping> governmentMap;
	std::vector<partyMapping> partyMap;
};



#endif // GOVERNMENT_MAPPER_H