#ifndef COASTAL_PROVINCES_H
#define COASTAL_PROVINCES_H



#include <vector>
#include <map>



namespace HoI4
{

class MapData;
class Province;


class CoastalProvinces
{
	public:
		void init(const MapData& theMapData);

		[[nodiscard]] auto getCoastalProvinces() const { return theCoastalProvinces; }
		[[nodiscard]] bool isProvinceCoastal(int provinceNum) const;

	private:
		[[nodiscard]] std::map<int, Province> importProvinces() const;

		std::map<int, std::vector<int>> theCoastalProvinces;	// province, connecting sea provinces
};

}



#endif // COASTAL_PROVINCES_H
