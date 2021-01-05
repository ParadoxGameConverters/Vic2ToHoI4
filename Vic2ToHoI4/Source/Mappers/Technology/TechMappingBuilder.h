#ifndef TECH_MAPPING_BUILDER_H
#define TECH_MAPPING_BUILDER_H



#include "TechMapping.h"
#include <memory>



namespace Mappers
{

class TechMapping::Builder
{
  public:
	Builder() { techMapping = std::make_unique<TechMapping>(); }

	std::unique_ptr<TechMapping> Build() { return std::move(techMapping); }

	Builder& setVic2Requirements(std::set<std::string> vic2Requirements)
	{
		techMapping->vic2Requirements = std::move(vic2Requirements);
		return *this;
	}

	Builder& setLimit(std::string limit)
	{
		techMapping->limit = std::move(limit);
		return *this;
	}

	Builder& setTechs(std::set<std::string> techs)
	{
		techMapping->techs = std::move(techs);
		return *this;
	}

  private:
	std::unique_ptr<TechMapping> techMapping;
};

} // namespace Mappers



#endif // TECH_MAPPING_BUILDER_H