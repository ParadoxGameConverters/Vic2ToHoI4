#ifndef HOI4_IDEAS_H
#define HOI4_IDEAS_H



#include "src/HOI4World/Ideas/IdeaGroup.h"
#include "external/common_items/ConvenientParser.h"
#include <map>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Ideas: commonItems::parser
{
  public:
	Ideas() noexcept;

	void updateIdeas(const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getIdeologicalIdeas() const { return ideologicalIdeas; }
	[[nodiscard]] const auto& getGeneralIdeas() const { return generalIdeas; }

  private:
	void importIdeologicalIdeas();
	void importGeneralIdeas();

	std::map<std::string, IdeaGroup> ideologicalIdeas;
	std::vector<IdeaGroup> generalIdeas;
};

} // namespace HoI4



#endif // HOI4_IDEAS_H