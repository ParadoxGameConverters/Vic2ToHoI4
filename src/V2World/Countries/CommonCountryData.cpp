#include "src/V2World/Countries/CommonCountryData.h"



bool Vic2::CommonCountryData::operator==(const CommonCountryData& rhs) const
{
	return (color_ == rhs.color_) && (unit_names_ == rhs.unit_names_) && (parties_ == rhs.parties_);
}