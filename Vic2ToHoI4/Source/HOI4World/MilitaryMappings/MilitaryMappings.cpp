#include "MilitaryMappings.h"
#include "DivisionTemplatesImporter.h"
#include "UnitMappings.h"
#include "SubstitutesImporter.h"



HoI4::militaryMappings::militaryMappings(std::string name, std::istream& theStream):
	mappingsName(std::move(name))
{
	registerKeyword(std::regex("unit_map"), [this](const std::string& unused, std::istream& theStream){
		unitMappings = std::make_unique<UnitMappings>(theStream);
	});
	registerKeyword(std::regex("mtg_unit_map"), [this](const std::string & unused, std::istream & theStream) {
		mtgUnitMappings = std::make_unique<MtgUnitMappings>(theStream);
	});
	registerKeyword(std::regex("division_templates"), [this](const std::string& unused, std::istream& theStream){
		const DivisionTemplatesImporter importer(theStream);
		divisionTemplates = importer.takeDivisionTemplates();
	});
	registerKeyword(std::regex("substitutes"), [this](const std::string& unused, std::istream& theStream){
		const substitutesImporter importer(theStream);
		substitutes = importer.getSubstitutes();
	});

	parseStream(theStream);

	if (!unitMappings)
	{
		throw std::invalid_argument("No unit mappings were included! Check unit_mappings.txt for correctness.");
	}
	if (!mtgUnitMappings)
	{
		throw std::invalid_argument("No mtg unit mappings were included! Check unit_mappings.txt for correctness.");
	}
}