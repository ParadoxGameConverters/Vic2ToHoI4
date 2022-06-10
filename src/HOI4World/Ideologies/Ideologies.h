#ifndef IDEOLOGIES_H
#define IDEOLOGIES_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/Ideologies/Ideology.h"
#include <map>
#include <optional>
#include <set>
#include <string>



namespace HoI4
{

class Country; // forward declaration to break circular dependency

class Ideologies: commonItems::parser
{
  public:
	class Builder;

	Ideologies() = default;
	explicit Ideologies(const Configuration& theConfiguration);

	void identifyMajorIdeologies(const std::vector<std::shared_ptr<Country>>& greatPowers,
		 const std::map<std::string, std::shared_ptr<Country>>& countries,
		 const Configuration& theConfiguration);

	[[nodiscard]] bool subIdeologyIsValid(const std::string& ideologyName, std::string_view subIdeology) const;
	[[nodiscard]] std::optional<Ideology> getIdeology(const std::string& ideologyName) const;

	[[nodiscard]] const auto& getMajorIdeologies() const { return majorIdeologies; }

  private:
	std::map<std::string, Ideology> ideologies;
	std::set<std::string> majorIdeologies;
};

} // namespace HoI4



#endif // IDEOLOGIES_H