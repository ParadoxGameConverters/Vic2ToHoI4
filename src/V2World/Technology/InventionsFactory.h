#ifndef INVENTIONS_FACTORY_H
#define INVENTIONS_FACTORY_H



#include "Configuration.h"
#include "Inventions.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>
#include <string>
#include <vector>



namespace Vic2
{

class Inventions::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Inventions> loadInventions(const Configuration& theConfiguration);

  private:
	[[nodiscard]] std::vector<std::string> getInventionFiles(const Configuration& theConfiguration) const;
	[[nodiscard]] std::map<std::string, std::string> getTechFilesAndPaths(const Configuration& theConfiguration) const;
	void generateNumbers(const std::vector<std::string>& inventionFiles);

	std::unique_ptr<Inventions> inventions;
};

} // namespace Vic2



#endif // INVENTIONS_FACTORY_H