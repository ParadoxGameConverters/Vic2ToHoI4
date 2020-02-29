#ifndef HOI4_IDEAGROUP_H
#define HOI4_IDEAGROUP_H


#include "newParser.h"
#include "Idea.h"
#include <optional>
#include <vector>



namespace HoI4
{

class IdeaGroup: commonItems::parser
{
	public:
		IdeaGroup(const std::string& ideaGroupName, std::istream& theStream);

		std::string getName() const { return name; }
		std::optional<Idea> getIdea(const std::string& ideaName);
		void replaceIdea(const Idea& newIdea);

		auto getIdeas() const { return ideas; }

		friend std::ostream& operator<<(std::ostream& outStream, const HoI4::IdeaGroup& outIdeaGroup);

	private:
		std::string name;

		bool law = false;
		bool designer = false;

		std::vector<Idea> ideas;
};

std::ostream& operator<<(std::ostream& outStream, const HoI4::IdeaGroup& outIdeaGroup);

}



#endif // HOI4_IDEAGROUP_H