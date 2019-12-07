#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/V2World/World.h"



namespace Vic2
{
class Party;
}



class mockVic2World: public Vic2::World
{
	public:
		MOCK_METHOD(std::vector<Vic2::Party>, getParties, (), (const, override));
};