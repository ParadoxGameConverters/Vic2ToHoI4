#ifndef STATE_BUILDINGS_H
#define STATE_BUILDINGS_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class StateBuildings: commonItems::parser
{
  public:
	explicit StateBuildings(std::istream& theStream);

	int getCivFactories() const { return civFactories; }
	int getMilFactories() const { return milFactories; }
	int getDockyards() const { return dockyards; }

  private:
	int civFactories = 0;
	int milFactories = 0;
	int dockyards = 0;
};

} // namespace HoI4



#endif // STATE_BUILDINGS_H