#ifndef SCORER_FACTORY_H
#define SCORER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Scorers/Scorer.h"
#include <memory>



namespace HoI4
{

class Scorer::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Scorer> getScorer(const std::string& name, std::istream& theStream);

  private:
	std::unique_ptr<Scorer> scorer;
};

} // namespace HoI4



#endif // SCORER_FACTORY_H