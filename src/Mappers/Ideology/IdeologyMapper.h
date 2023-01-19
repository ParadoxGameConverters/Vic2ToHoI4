#ifndef IDEOLOGY_MAPPER_H
#define IDEOLOGY_MAPPER_H



#include "src/Mappers/Ideology/IdeologyMapping.h"
#include <set>
#include <string>
#include <vector>



namespace Mappers
{

class IdeologyMapper
{
  public:
	class Factory;

	[[nodiscard]] std::string getSupportedIdeology(const std::string& rulingIdeology,
		 const std::string& Vic2Ideology,
		 const std::set<std::string>& majorIdeologies) const;

  private:
	std::vector<IdeologyMapping> ideologyMap;
};

} // namespace Mappers


#endif // IDEOLOGY_MAPPER_H