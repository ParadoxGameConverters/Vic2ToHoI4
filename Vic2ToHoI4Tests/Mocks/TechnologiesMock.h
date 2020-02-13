#ifndef TECHNOLOGIES_MOCK_H
#define TECHNOLOGIES_MOCK_H



#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/Technologies.h"



class mockTechnologies: public HoI4::technologies
{
	public:
		MOCK_METHOD(bool, hasTechnology, (const std::string&), (const, override));
};



#endif // TECHNOLOGIES_MOCK_H