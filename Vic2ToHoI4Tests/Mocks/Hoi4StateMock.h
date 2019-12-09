#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/States/HoI4State.h"



class mockHoi4State: public HoI4::State
{
	public:
		mockHoi4State(const std::string& owner):State(nullptr, 0, owner) {}

		MOCK_METHOD(int, getID, (), (const, override));
		MOCK_METHOD(std::set<int>, getProvinces, (), (const, override));
};