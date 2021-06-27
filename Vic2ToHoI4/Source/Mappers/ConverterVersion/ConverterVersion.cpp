#include "ConverterVersion.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include <fstream>

void mappers::ConverterVersion::loadVersion(const std::string& fileName)
{
	registerKeys();
	parseFile(fileName);
	clearRegisteredKeywords();
}

void mappers::ConverterVersion::loadVersion(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::ConverterVersion::registerKeys()
{
	registerSetter("name", name);
	registerSetter("version", version);
	registerSetter("source", source);
	registerSetter("target", target);
	registerKeyword("minSource", [this](std::istream& theStream) {
		minSource = GameVersion(commonItems::getString(theStream));
	});
	registerKeyword("maxSource", [this](std::istream& theStream) {
		maxSource = GameVersion(commonItems::getString(theStream));
	});
	registerKeyword("minTarget", [this](std::istream& theStream) {
		minTarget = GameVersion(commonItems::getString(theStream));
	});
	registerKeyword("maxTarget", [this](std::istream& theStream) {
		maxTarget = GameVersion(commonItems::getString(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

std::string mappers::ConverterVersion::getDescription() const
{
	auto toReturn = "Compatible with " + source + " [v" + minSource.toShortString();
	if (maxSource != minSource)
		toReturn += "-v" + maxSource.toShortString();
	toReturn += "] and " + target + " [v" + minTarget.toShortString();
	if (maxTarget != minTarget)
		toReturn += "-v" + maxTarget.toShortString();
	toReturn += "]";

	return toReturn;
}

std::ostream& mappers::operator<<(std::ostream& output, const ConverterVersion& version)
{
	output << "\n\n";
	output << "************ -= The Paradox Converters Team =- ********************\n";
	output << "* Converter version " << version.version << " \"" << version.name << "\"\n";
	output << "* " << version.getDescription() << "\n";
	output << "* Built on " << __TIMESTAMP__ << "\n";
	output << "********************* + Vic2 To HoI4 + ****************************\n";
	return output;
}