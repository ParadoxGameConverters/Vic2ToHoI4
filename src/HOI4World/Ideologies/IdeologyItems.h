#ifndef IDEOLOGY_ITEMS_H
#define IDEOLOGY_ITEMS_H



#include "Parser.h"



namespace HoI4
{

class IdeologyItems: commonItems::parser
{
  public:
	explicit IdeologyItems(std::istream& theStream);

	auto&& takeItems() { return items; }

  private:
	std::map<std::string, std::string> items;
};

} // namespace HoI4



#endif // IDEOLOGY_ITEMS_H