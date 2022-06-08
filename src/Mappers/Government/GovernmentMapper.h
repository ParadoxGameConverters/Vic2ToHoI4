#ifndef GOVERNMENT_MAPPER_H
#define GOVERNMENT_MAPPER_H



#include "src/Mappers/Government/GovernmentMapping.h"
#include "src/HOI4World/Ideologies/Ideologies.h"
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

	[[nodiscard]] std::string getIdeologyForCountry(const std::string& sourceTag,
		 const std::string& sourceGovernment,
		 const std::string& Vic2RulingIdeology,
		 bool debug) const;
	[[nodiscard]] std::string getLeaderIdeologyForCountry(const std::string& sourceTag,
		 const std::string& sourceGovernment,
		 const std::string& Vic2RulingIdeology,
		 bool debug) const;
	[[nodiscard]] std::string getExistingIdeologyForCountry(const std::string& tag,
		 const std::string& government,
		 const std::string& Vic2RulingIdeology,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::Ideologies& ideologies,
		 bool debug) const;
	[[nodiscard]] std::string getExistingLeaderIdeologyForCountry(const std::string& tag,
		 const std::string& government,
		 const std::string& Vic2RulingIdeology,
		 const std::set<std::string>& majorIdeologies,
		 const HoI4::Ideologies& ideologies,
		 bool debug) const;

  private:
	std::vector<GovernmentMapping> governmentMap;
};

} // namespace Mappers



#endif // GOVERNMENT_MAPPER_H