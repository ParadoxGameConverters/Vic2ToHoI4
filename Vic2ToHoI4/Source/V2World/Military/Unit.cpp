#include "Unit.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



Vic2::Unit::Unit(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = commonItems::convertWin1252ToUTF8(nameString.getString());
	});
	registerKeyword("type", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword("strength", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble strengthDouble(theStream);
		strength = strengthDouble.getDouble();
	});
	registerKeyword("organisation", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble organizationDouble(theStream);
		organization = organizationDouble.getDouble();
	});
	registerKeyword("experience", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble experienceDouble(theStream);
		experience = experienceDouble.getDouble();
	});
	registerKeyword("pop", [this](const std::string& unused, std::istream& theStream) {
		commonItems::simpleObject pop_def(theStream);
		pop_id = pop_def.getValueAsInt("id");
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);

	if (type.empty())
	{
		Log(LogLevel::Warning) << "Regiment or Ship " << name << " has no type";
	}
}