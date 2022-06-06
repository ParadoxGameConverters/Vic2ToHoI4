#include "HoI4UnitType.h"
#include "external/common_items/ParserHelpers.h"



HoI4::HoI4UnitType::HoI4UnitType(std::istream& theStream)
{
	registerKeyword("category", [this](std::istream& theStream) {
		const commonItems::singleString categoryString(theStream);
		category = categoryString.getString();
	});
	registerKeyword("type", [this](std::istream& theStream) {
		const commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword("equipment", [this](std::istream& theStream) {
		const commonItems::singleString equipmentString(theStream);
		equipment = equipmentString.getString();
	});
	registerKeyword("version", [this](std::istream& theStream) {
		const commonItems::singleString versionString(theStream);
		version = versionString.getString();
	});
	registerKeyword("size", [this](std::istream& theStream) {
		const commonItems::singleInt sizeInt(theStream);
		size = sizeInt.getInt();
	});

	parseStream(theStream);
}


bool HoI4::HoI4UnitType::operator==(const HoI4UnitType& rhs) const
{
	return category == rhs.category && type == rhs.type && equipment == rhs.equipment && version == rhs.version &&
			 size == rhs.size;
}