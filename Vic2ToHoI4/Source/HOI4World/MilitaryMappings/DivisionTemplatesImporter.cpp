#include "DivisionTemplatesImporter.h"



HoI4::DivisionTemplatesImporter::DivisionTemplatesImporter(std::istream& theStream)
{
	registerKeyword(std::regex("division_template"), [this](const std::string& unused, std::istream& theStream)
	{
		const DivisionTemplateType newTemplate(theStream);
		divisionTemplates.push_back(newTemplate);
	});

	parseStream(theStream);
}