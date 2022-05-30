#ifndef HOI4_DEFAULT_STATES_H
#define HOI4_DEFAULT_STATES_H


#include "Parser.h"
#include <set>
#include <string>



namespace HoI4
{

class DefaultState: commonItems::parser
{
  public:
	explicit DefaultState(std::istream& theStream);

	bool isImpassable() const { return impassable; }
	const std::string& getOwner() const { return ownerTag; }
	const std::set<int>& getProvinces() const { return provinces; }
	int getCivFactories() const { return civFactories; }
	int getMilFactories() const { return milFactories; }
	int getDockyards() const { return dockyards; }

  private:
	bool impassable = false;
	std::string ownerTag;
	std::set<int> provinces;
	int civFactories = 0;
	int milFactories = 0;
	int dockyards = 0;
};

} // namespace HoI4



#endif // HOI4_DEFAULT_STATES_H