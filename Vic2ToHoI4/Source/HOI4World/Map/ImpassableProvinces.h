#ifndef IMPASSABLE_PROVINCES_H
#define IMPASSABLE_PROVINCES_H



#include <map>
#include <unordered_set>



namespace HoI4
{

class DefaultState;



class impassableProvinces
{
	public:
		explicit impassableProvinces(const std::map<int, HoI4::DefaultState>& states);

		bool isProvinceImpassable(int provinceNumber) const;

	public:
		std::unordered_set<int> impassibleProvinces;
};

}



#endif // IMPASSABLE_PROVINCES_H

