#ifndef HOI4_IDEOLOGY_FILE
#define HOI4_IDEOLOGY_FILE


#include "Ideology.h"
#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class IdeologyFile: commonItems::parser
{
  public:
	explicit IdeologyFile(std::istream& theStream);

	[[nodiscard]] auto getIdeologies() const { return ideologies; }

  private:
	std::map<std::string, Ideology> ideologies;
};

} // namespace HoI4



#endif // HOI4_IDEOLOGY_FILE