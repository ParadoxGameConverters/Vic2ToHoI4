#ifndef HOI4_IDEAS_H
#define HOI4_IDEAS_H



#include "IdeaGroup.h"
#include "newParser.h"
#include <map>
#include <memory>
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

		const auto& getIdeologicalIdeas() const { return ideologicalIdeas; }
		const auto& getGeneralIdeas() const { return generalIdeas; }

	private:
		void importIdeologicalIdeas();
		void importGeneralIdeas();

		std::map<std::string, IdeaGroup> ideologicalIdeas;
		std::vector<std::unique_ptr<IdeaGroup>> generalIdeas;
};

}



#endif // HOI4_IDEAS_H