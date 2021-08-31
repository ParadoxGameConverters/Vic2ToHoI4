#ifndef REBELLION_FACTORY_H
#define REBELLION_FACTORY_H



#include "Parser.h"
#include "Rebellion.h"
#include <memory>



namespace Vic2
{

class Rebellion::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Rebellion> importRebellion(std::istream& theStream);

  private:
	std::unique_ptr<Rebellion> rebellion;
};

} // namespace Vic2



#endif // REBELLION_FACTORY_H