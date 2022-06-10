#ifndef STOCKPILES_FACTORY_H
#define STOCKPILES_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>



namespace Vic2
{

class StockpileFactory: commonItems::parser
{
  public:
	StockpileFactory();
	std::map<std::string, float> importStockpile(std::istream& theStream);

  private:
	std::map<std::string, float> stockpile;
};

} // namespace Vic2



#endif // STOCKPILES_FACTORY_H