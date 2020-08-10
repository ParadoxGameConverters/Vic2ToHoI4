#ifndef PROVINCE_FACTORY_H
#define PROVINCE_FACTORY_H



#include "Parser.h"
#include "Province.h"
#include <memory>



namespace Vic2
{

class Province::Factory: commonItems::parser
{
  public:
	explicit Factory(Pop::Factory& _popFactory);
	std::unique_ptr<Province> getProvince(const std::string& numberString, std::istream& theStream);

  private:
	std::unique_ptr<Province> province;
	Pop::Factory& popFactory;
};

} // namespace Vic2



#endif // PROVINCE_FACTORY_H