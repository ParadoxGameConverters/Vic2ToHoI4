#ifndef MOD_FACTORY_H
#define MOD_FACTORY_H



#include "Mod.h"
#include "Parser.h"
#include <memory>



namespace Vic2
{

class Mod::Factory: commonItems::parser
{
  public:
	Factory();
	[[nodiscard]] std::unique_ptr<Mod> getMod(const std::string& modFile, const std::string& Vic2ModDir);

  private:
	std::unique_ptr<Mod> mod;
};

} // namespace Vic2



#endif // MOD_FACTORY_H