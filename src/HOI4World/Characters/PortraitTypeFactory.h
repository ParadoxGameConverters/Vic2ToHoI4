#ifndef HOI4_CHARACTERS_PORTRAIT_TYPE_FACTORY_H
#define HOI4_CHARACTERS_PORTRAIT_TYPE_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Characters/Portrait.h"
#include <string_view>
#include <vector>



namespace HoI4
{

class PortraitTypeFactory: commonItems::parser
{
  public:
	PortraitTypeFactory();

	std::vector<Portrait> importPortraits(std::string_view type, std::istream& input);

  private:
	std::string type_;

	std::vector<Portrait> portraits_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_PORTRAIT_TYPE_FACTORY_H