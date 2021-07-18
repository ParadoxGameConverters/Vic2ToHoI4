#ifndef STATE_CATEGORY_H
#define STATE_CATEGORY_H



#include "Parser.h"



namespace HoI4
{

class StateCategory: commonItems::parser
{
  public:
	explicit StateCategory(std::istream& theStream);

	auto getNumberOfSlots() const { return numberOfSlots; }

  private:
	int numberOfSlots = 0;
};

} // namespace HoI4



#endif // STATE_CATEGORY_H
