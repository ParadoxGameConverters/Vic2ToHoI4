#include "DivisionTemplatesImporter.h"



HoI4::DivisionTemplatesImporter::DivisionTemplatesImporter(std::istream& theStream)
{
	registerKeyword("division_template", [this](std::istream& theStream) {
		const DivisionTemplateType newTemplate(theStream);
		divisionTemplates.push_back(newTemplate);
	});

	parseStream(theStream);
}