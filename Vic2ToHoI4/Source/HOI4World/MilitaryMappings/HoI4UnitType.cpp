#include "HoI4UnitType.h"
#include "ParserHelpers.h"



HoI4::HoI4UnitType::HoI4UnitType(std::istream& theStream)
{
	registerKeyword(std::regex("category"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString categoryString(theStream);
		category = categoryString.getString();
	});
	registerKeyword(std::regex("type"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword(std::regex("equipment"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString equipmentString(theStream);
		equipment = equipmentString.getString();
	});
	registerKeyword(std::regex("version"), [this](const std::string & unused, std::istream & theStream) {
		const commonItems::singleString versionString(theStream);
		version = versionString.getString();
	});
	registerKeyword(std::regex("size"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleInt sizeInt(theStream);
		size = sizeInt.getInt();
	});

	parseStream(theStream);
}


bool HoI4::HoI4UnitType::operator==(const HoI4UnitType& rhs) const
{
	return
		category == rhs.category &&
		type == rhs.type &&
		equipment == rhs.equipment &&
		version == rhs.version &&
		size == rhs.size;
}