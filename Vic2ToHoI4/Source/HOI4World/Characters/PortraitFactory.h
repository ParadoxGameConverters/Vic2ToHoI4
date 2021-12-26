#ifndef HOI4_CHARACTERS_PORTRAIT_FACTORY_H
#define HOI4_CHARACTERS_PORTRAIT_FACTORY_H



#include "HOI4World/Characters/Portrait.h"
#include "Parser.h"



namespace HoI4
{

class PortraitFactory: commonItems::parser
{
  public:
	PortraitFactory();
	Portrait importPortrait(std::string_view type, std::istream& input);

  private:
	std::string type_;
	std::string size_;
	std::string definition_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_PORTRAIT_FACTORY_H