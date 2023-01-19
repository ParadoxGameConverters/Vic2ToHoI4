#ifndef HOI4_IDEOLOGY_FILE
#define HOI4_IDEOLOGY_FILE


#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Ideologies/Ideology.h"
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