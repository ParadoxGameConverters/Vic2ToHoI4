#ifndef GOVERNMENT_MAPPER_H
#define GOVERNMENT_MAPPER_H



#include "GovernmentMapping.h"
#include "HOI4World/Ideologies/Ideologies.h"
#include <set>
#include <string>
#include <vector>



namespace Mappers
{

class GovernmentMapper
{
  public:
	class Factory;
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

	auto getGovernmentMappings() const { return governmentMap; }

  private:
	bool governmentMatches(const Mappers::GovernmentMapping& mapping, const std::string& government) const;
	bool rulingIdeologyMatches(const Mappers::GovernmentMapping& mapping, const std::string& rulingIdeology) const;
	bool tagMatches(const Mappers::GovernmentMapping& mapping, const std::string& tag) const;
	static bool ideologyIsValid(const Mappers::GovernmentMapping& mapping,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::Ideologies& ideologies);

	std::vector<Mappers::GovernmentMapping> governmentMap;
};

} // namespace Mappers



#endif // GOVERNMENT_MAPPER_H