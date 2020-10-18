#ifndef TECHNOLOGIES_MOCK_H
#define TECHNOLOGIES_MOCK_H



#include "HOI4World/Technologies.h"
#include "gmock/gmock.h"



class mockTechnologies final: public HoI4::technologies
{
  public:
	MOCK_METHOD(bool, hasTechnology, (const std::string&), (const, override));
};



#endif // TECHNOLOGIES_MOCK_H