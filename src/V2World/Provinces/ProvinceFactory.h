#ifndef PROVINCE_FACTORY_H
#define PROVINCE_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "Province.h"
#include <memory>



namespace Vic2
{

class Province::Factory: commonItems::parser
{
  public:
	explicit Factory(std::unique_ptr<PopFactory>&& _popFactory);
	std::unique_ptr<Province> getProvince(int number, std::istream& theStream);

  private:
	std::unique_ptr<Province> province;
	std::unique_ptr<PopFactory> popFactory;
};

} // namespace Vic2



#endif // PROVINCE_FACTORY_H