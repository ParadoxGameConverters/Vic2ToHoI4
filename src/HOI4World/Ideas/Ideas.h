#ifndef HOI4_IDEAS_H
#define HOI4_IDEAS_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Ideas/IdeaGroup.h"
#include <map>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Ideas: commonItems::parser
{
  public:
	class Factory;

	Ideas() = default;
	Ideas(const std::set<std::string>& majorIdeologies) noexcept;

	void updateIdeas(const std::set<std::string>& majorIdeologies);
	void addGeneralIdeas(const IdeaGroup& theGroup) { generalIdeas.push_back(theGroup); }

	[[nodiscard]] const auto& getIdeologicalIdeas() const { return ideologicalIdeas; }
	[[nodiscard]] const auto& getGeneralIdeas() const { return generalIdeas; }

  private:
	void importIdeologicalIdeas(const std::set<std::string>& majorIdeologies);
	void importGeneralIdeas();

	std::map<std::string, std::vector<IdeaGroup>> ideologicalIdeas;
	std::vector<IdeaGroup> generalIdeas;
};

} // namespace HoI4



#endif // HOI4_IDEAS_H