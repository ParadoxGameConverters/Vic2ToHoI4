#ifndef HOI4_PROVINCE_H
#define HOI4_PROVINCE_H



#include <string>



namespace HoI4
{
	
class Province
{
	public:
		Province(const bool _isLand, std::string _type): isLand(_isLand), type(std::move(_type)) {}

		[[nodiscard]] bool isLandProvince() const { return isLand; }
		[[nodiscard]] std::string_view getType() const { return type; }
	
	private:
		bool isLand = false;
		std::string type;
};
	
}



#endif // HOI4_PROVINCE_H