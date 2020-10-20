#ifndef VIC2_WORLD_MOCK
#define VIC2_WORLD_MOCK



#include "V2World/Politics/Party.h"
#include "V2World/World.h"
#include "gmock/gmock.h"



class mockVic2World final: public Vic2::World
{
  public:
	MOCK_METHOD(std::vector<Vic2::Party>, getParties, (), (const, override));
};



#endif // VIC2_WORLD_MOCK