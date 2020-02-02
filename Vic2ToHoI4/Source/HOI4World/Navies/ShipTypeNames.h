#ifndef SHIP_TYPE_NAMES
#define SHIP_TYPE_NAMES



#include <string>
#include <vector>



namespace HoI4
{

class ShipTypeNames
{
	public:
		explicit ShipTypeNames(std::string _type, std::string _genericName, std::vector<std::string> _names):
			type(std::move(_type)), genericName(std::move(_genericName)), names(std::move(_names)) 
		{}
	
		[[nodiscard]] std::string_view getType() const { return type; }
		[[nodiscard]] std::string_view getPrefix() const { return ""; }
		[[nodiscard]] std::string_view getGenericName() const { return genericName; }
		[[nodiscard]] std::vector<std::string> getNames() const { return names; }

	private:
		std::string type;
		std::string genericName;
		std::vector<std::string> names;
};

}



#endif // SHIP_TYPE_NAMES