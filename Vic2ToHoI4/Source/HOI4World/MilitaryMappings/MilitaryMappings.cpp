#include "MilitaryMappings.h"
#include "DivisionTemplatesImporter.h"
#include "SubstitutesImporter.h"
#include "UnitMappings.h"



HoI4::militaryMappings::militaryMappings(std::string name, std::istream& theStream): mappingsName(std::move(name))
{
	registerKeyword("unit_map", [this](std::istream& theStream) {
		unitMappings = std::make_unique<UnitMappings>(theStream);
	});
	registerKeyword("mtg_unit_map", [this](std::istream& theStream) {
		mtgUnitMappings = std::make_unique<MtgUnitMappings>(theStream);
	});
	registerKeyword("division_templates", [this](std::istream& theStream) {
		const DivisionTemplatesImporter importer(theStream);
		divisionTemplates = importer.takeDivisionTemplates();
	});
	registerKeyword("substitutes", [this](std::istream& theStream) {
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