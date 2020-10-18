#ifndef STATE_CATEGORIES_MOCK
#define STATE_CATEGORIES_MOCK



#include "HOI4World/States/StateCategories.h"
#include "gmock/gmock.h"



class mockStateCategories final: public HoI4::StateCategories
{
  public:
	MOCK_METHOD(std::string, getBestCategory, (int numBuildingSlots), (const, override));
};



#endif // STATE_CATEGORIES_MOCK