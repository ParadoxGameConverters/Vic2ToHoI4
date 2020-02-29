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

		void output(const std::set<std::string>& majorIdeologies) const;

	private:
		void importIdeologicalIdeas();
		void importGeneralIdeas();

		void outputIdeologicalIdeas(const std::set<std::string>& majorIdeologies) const;
		void outputGeneralIdeas() const;

		std::ofstream openIdeaFile(const std::string& fileName) const;
		void closeIdeaFile(std::ofstream& fileStream) const;

		std::map<std::string, IdeaGroup> ideologicalIdeas;
		std::vector<std::unique_ptr<IdeaGroup>> generalIdeas;
};

}



#endif // HOI4_IDEAS_H