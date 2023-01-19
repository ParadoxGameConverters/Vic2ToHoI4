#ifndef TECH_MAPPING_H
#define TECH_MAPPING_H



#include "external/common_items/ConvenientParser.h"
#include <set>
#include <string>



namespace Mappers
{

class TechMapping
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] const auto& getVic2Requirements() const { return vic2Requirements; }
	[[nodiscard]] const auto& getLimit() const { return limit; }
	[[nodiscard]] const auto& getTechs() const { return techs; }

  private:
	std::set<std::string> vic2Requirements;
	std::string limit;
	std::set<std::string> techs;
};

} // namespace Mappers



#endif // TECH_MAPPING_H