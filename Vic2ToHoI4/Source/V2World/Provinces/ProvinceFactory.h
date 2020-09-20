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
	explicit Factory(std::unique_ptr<Pop::Factory>&& _popFactory);
	std::unique_ptr<Province> getProvince(int number, std::istream& theStream);

  private:
	std::unique_ptr<Province> province;
	std::unique_ptr<Pop::Factory> popFactory;
};

} // namespace Vic2



#endif // PROVINCE_FACTORY_H