#ifndef COASTAL_PROVINCES_H
#define COASTAL_PROVINCES_H



#include "Configuration.h"
#include "HOI4World/Map/Hoi4Province.h"
#include "MapData.h"
#include <map>
#include <vector>



class Configuration;



namespace HoI4
{

class CoastalProvinces
{
  public:
	CoastalProvinces() = default;
	CoastalProvinces(const CoastalProvinces&) = default;
	CoastalProvinces(CoastalProvinces&&) = default;
	CoastalProvinces& operator=(const CoastalProvinces&) = default;
	CoastalProvinces& operator=(CoastalProvinces&&) = default;
	virtual ~CoastalProvinces() = default;

	void init(const MapData& theMapData, const std::map<int, Province>& theProvinces);

	[[nodiscard]] auto getCoastalProvinces() const { return theCoastalProvinces; }
	[[nodiscard]] virtual bool isProvinceCoastal(int provinceNum) const;

  private:
	std::map<int, std::vector<int>> theCoastalProvinces; // province, connecting sea provinces
};

} // namespace HoI4



#endif // COASTAL_PROVINCES_H