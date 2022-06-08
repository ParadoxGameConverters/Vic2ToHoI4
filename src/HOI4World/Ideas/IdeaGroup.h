#ifndef HOI4_IDEA_GROUP_H
#define HOI4_IDEA_GROUP_H



#include "src/HOI4World/Ideas/Idea.h"
#include "external/common_items/ConvenientParser.h"
#include <optional>
#include <vector>



namespace HoI4
{

class IdeaGroup: commonItems::parser
{
  public:
	IdeaGroup(std::string ideaGroupName, std::istream& theStream);

	[[nodiscard]] std::string getName() const { return name; }
	[[nodiscard]] std::optional<Idea> getIdea(const std::string& ideaName) const;
	[[nodiscard]] auto getIdeas() const { return ideas; }

	void replaceIdea(const Idea& newIdea);

	friend std::ostream& operator<<(std::ostream& outStream, const IdeaGroup& outIdeaGroup);

  private:
	std::string name;

	bool law = false;
	bool designer = false;
	bool useListView = false;

	std::vector<Idea> ideas;
};

} // namespace HoI4



#endif // HOI4_IDEA_GROUP_H