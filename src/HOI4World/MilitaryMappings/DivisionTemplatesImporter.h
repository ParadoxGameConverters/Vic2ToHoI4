#ifndef DIVISION_TEMPLATE_IMPORTER
#define DIVISION_TEMPLATE_IMPORTER



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Military/DivisionTemplate.h"



namespace HoI4
{

class DivisionTemplatesImporter: commonItems::parser
{
  public:
	explicit DivisionTemplatesImporter(std::istream& theStream);

	[[nodiscard]] auto&& takeDivisionTemplates() const { return std::move(divisionTemplates); }

  private:
	std::vector<DivisionTemplateType> divisionTemplates;
};

} // namespace HoI4



#endif // DIVISION_TEMPLATE_IMPORTER