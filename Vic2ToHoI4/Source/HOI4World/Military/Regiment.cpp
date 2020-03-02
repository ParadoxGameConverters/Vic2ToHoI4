#include "Regiment.h"
#include "ParserHelpers.h"



HoI4::RegimentType::RegimentType(const std::string& _type, std::istream& theStream):
	type(_type)
{
	registerKeyword(std::regex("x"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt xInt(theStream);
		x = xInt.getInt();
	});
	registerKeyword(std::regex("y"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt yInt(theStream);
		y = yInt.getInt();
	});

	parseStream(theStream);
}