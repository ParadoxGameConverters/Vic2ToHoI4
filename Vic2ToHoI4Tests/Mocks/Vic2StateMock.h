#ifndef VIC2_STATE_MOCK
#define VIC2_STATE_MOCK



#include "../../Vic2ToHoI4/Source/V2World/State.h"
#include "gmock/gmock.h"



class mockVic2State final: public Vic2::State
{
  public:
	MOCK_METHOD(int, getEmployedWorkers, (), (const, override));
	MOCK_METHOD(int, getPopulation, (), (const, override));
	MOCK_METHOD(float, getAverageRailLevel, (), (const, override));
	MOCK_METHOD(std::set<int>, getProvinceNumbers, (), (const, override));
	MOCK_METHOD(std::optional<int>, getCapitalProvince, (), (const, override));
	MOCK_METHOD(std::set<const Vic2::Province*>, getProvinces, (), (const, override));
};



#endif // VIC2_STATE_MOCK