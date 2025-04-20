#ifndef HOI4_IDEAS_FACTORY_H
#define HOI4_IDEAS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Ideas/IdeaGroup.h"
#include "src/HOI4World/Ideas/Ideas.h"



namespace HoI4
{

class Ideas::Factory: commonItems::parser
{
  public:
	Factory();

	[[nodiscard]] Ideas importIdeas(const std::filesystem::path& filePath);

  private:
	std::unique_ptr<Ideas> importedIdeas;
};

} // namespace HoI4



#endif // HOI4_IDEAS_FACTORY_H