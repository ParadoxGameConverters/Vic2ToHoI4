#ifndef DIVISION_TEMPLATE_IMPORTER
#define DIVISION_TEMPLATE_IMPORTER



#include "../DivisionTemplate.h"
#include "newParser.h"



namespace HoI4
{

class DivisionTemplatesImporter: commonItems::parser
{
	public:
		explicit DivisionTemplatesImporter(std::istream& theStream);

		[[nodiscard]] auto getDivisionTemplates() const { return divisionTemplates; }

	private:
		std::vector<DivisionTemplateType> divisionTemplates;
};

}



#endif // DIVISION_TEMPLATE_IMPORTER