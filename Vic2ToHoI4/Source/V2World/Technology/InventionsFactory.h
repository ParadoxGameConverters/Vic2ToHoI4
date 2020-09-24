#ifndef INVENTIONS_FACTORY_H
#define INVENTIONS_FACTORY_H



#include "../../Configuration.h"
#include "Inventions.h"
#include "Parser.h"
#include <list>
#include <memory>
#include <string>



namespace Vic2
{

class Inventions::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Inventions> getInventions(const Configuration& theConfiguration);

  private:
	std::list<std::string> getInventionFiles(const Configuration& theConfiguration) const;
	void generateNums(const std::list<std::string>& inventionFiles);
	void processTechFile(const std::string& filename);

	std::unique_ptr<Inventions> inventions;
};

} // namespace Vic2



#endif // INVENTIONS_FACTORY_H