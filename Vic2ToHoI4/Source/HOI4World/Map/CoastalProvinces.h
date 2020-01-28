#ifndef COASTAL_PROVINCES_H
#define COASTAL_PROVINCES_H



#include <string>
#include <vector>
#include <map>



namespace HoI4
{

class MapData;

typedef struct province
{
	bool isLand = false;
	std::string type;
} province;


class coastalProvinces
{
	public:
		coastalProvinces() = default;
		void init(const MapData& theMapData);

		auto getCoastalProvinces() const { return theCoastalProvinces; }
		bool isProvinceCoastal(int provinceNum) const;

	private:
		coastalProvinces(const coastalProvinces&) = delete;
		coastalProvinces& operator=(const coastalProvinces&) = delete;

		std::map<int, province> getProvinces() const;

		std::map<int, std::vector<int>> theCoastalProvinces;	// province, connecting sea provinces
};

}



#endif // COASTAL_PROVINCES_H
