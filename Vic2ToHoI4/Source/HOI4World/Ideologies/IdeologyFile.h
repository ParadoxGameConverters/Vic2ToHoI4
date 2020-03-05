#ifndef HOI4_IDEOLOGY_FILE
#define HOI4_IDEOLOGY_FILE


#include "newParser.h"
#include <map>
#include <string>



namespace HoI4
{

class Ideology;

class IdeologyFile: commonItems::parser
{
  public:
	explicit IdeologyFile(std::istream& theStream);

	auto getIdeologies() const { return ideologies; }

  private:
	std::map<std::string, Ideology*> ideologies;
};

} // namespace HoI4



#endif // HOI4_IDEOLOGY_FILE