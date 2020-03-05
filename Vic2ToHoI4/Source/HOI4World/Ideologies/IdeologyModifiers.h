#ifndef IDEOLOGY_MODIFIERS_H
#define IDEOLOGY_MODIFIERS_H



#include "newParser.h"



namespace HoI4
{

class IdeologyModifiers: commonItems::parser
{
  public:
	explicit IdeologyModifiers(std::istream& theStream);

	auto&& takeModifiers() { return modifiers; }

  private:
	std::map<std::string, std::string> modifiers;
};

} // namespace HoI4



#endif // IDEOLOGY_MODIFIERS_H