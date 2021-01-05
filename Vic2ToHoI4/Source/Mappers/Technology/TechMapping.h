#ifndef TECH_MAPPING_H
#define TECH_MAPPING_H



#include "Parser.h"
#include <set>
#include <string>



namespace Mappers
{

class TechMapping
{
  public:
	class Factory;

	[[nodiscard]] const auto& getVic2Item() const { return vic2Item; }
	[[nodiscard]] const auto& getLimit() const { return limit; }
	[[nodiscard]] const auto& getTechs() const { return techs; }

  private:
	std::string vic2Item;
	std::string limit;
	std::set<std::string> techs;
};

} // namespace mappers



#endif // TECH_MAPPING_H