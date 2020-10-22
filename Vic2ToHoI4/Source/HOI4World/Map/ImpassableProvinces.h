#ifndef IMPASSABLE_PROVINCES_H
#define IMPASSABLE_PROVINCES_H



#include "HOI4World/States/DefaultState.h"
#include <map>
#include <unordered_set>



namespace HoI4
{

class ImpassableProvinces
{
  public:
	explicit ImpassableProvinces(const std::map<int, DefaultState>& states);

	[[nodiscard]] bool isProvinceImpassable(int provinceNumber) const;

  private:
	std::unordered_set<int> impassibleProvinces;
};

} // namespace HoI4



#endif // IMPASSABLE_PROVINCES_H