#ifndef COASTAL_PROVINCES_MOCK_H
#define COASTAL_PROVINCES_MOCK_H



#include "HOI4World/Map/CoastalProvinces.h"
#include "gmock/gmock.h"



class mockCoastalProvinces final: public HoI4::CoastalProvinces
{
  public:
	MOCK_METHOD(bool, isProvinceCoastal, (int), (const, override));
};



#endif // COASTAL_PROVINCES_MOCK_H