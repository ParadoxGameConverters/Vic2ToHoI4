#ifndef TRAITS_FACTORY_H
#define TRAITS_FACTORY_H


#include "Parser.h"
#include "Traits.h"
#include <memory>



namespace Vic2
{

class Traits::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Traits> loadTraits(const std::string& Vic2Location);

  private:
	std::unique_ptr<Traits> traits;
};

} // namespace Vic2



#endif // TRAITS_FACTORY_H