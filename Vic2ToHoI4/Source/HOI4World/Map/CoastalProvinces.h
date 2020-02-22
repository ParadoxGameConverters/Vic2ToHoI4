#ifndef COASTAL_PROVINCES_H
#define COASTAL_PROVINCES_H



#include <map>
#include <vector>



namespace HoI4
{

class MapData;
class Province;


class CoastalProvinces
{
  public:
	CoastalProvinces() = default;
	virtual ~CoastalProvinces() = default;

	void init(const MapData& theMapData);

	[[nodiscard]] auto getCoastalProvinces() const { return theCoastalProvinces; }
	[[nodiscard]] virtual bool isProvinceCoastal(int provinceNum) const;

  private:
	[[nodiscard]] std::map<int, Province> importProvinces() const;

	std::map<int, std::vector<int>> theCoastalProvinces; // province, connecting sea provinces
};

} // namespace HoI4



#endif // COASTAL_PROVINCES_H
