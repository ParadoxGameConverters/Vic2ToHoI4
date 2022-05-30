#ifndef STATE_HISTORY_H
#define STATE_HISTORY_H



#include "Parser.h"
#include <string>



namespace HoI4
{

class StateHistory: commonItems::parser
{
  public:
	explicit StateHistory(std::istream& theStream);

	int getCivFactories() const { return civFactories; }
	int getMilFactories() const { return milFactories; }
	int getDockyards() const { return dockyards; }
	std::string getOwner() const { return owner; }

  private:
	int civFactories = 0;
	int milFactories = 0;
	int dockyards = 0;
	std::string owner;
};

} // namespace HoI4



#endif // STATE_HISTORY_H