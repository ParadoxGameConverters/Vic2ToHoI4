#ifndef HOI4_STATE_MOCK
#define HOI4_STATE_MOCK



#include "HOI4World/States/HoI4State.h"
#include "gmock/gmock.h"



class mockHoi4State final: public HoI4::State
{
  public:
	mockHoi4State(const Vic2::State& oldState, const std::string& owner): State(oldState, 0, owner) {}

	MOCK_METHOD(int, getID, (), (const, override));
	MOCK_METHOD(const std::set<int>&, getProvinces, (), (const, override));
};



#endif // HOI4_STATE_MOCK