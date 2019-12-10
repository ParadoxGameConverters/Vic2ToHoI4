#ifndef IDEOLOGICAL_DECISIONS_H
#define IDEOLOGICAL_DECISIONS_H



#include "DecisionsCategory.h"
#include "newParser.h"



namespace HoI4
{

class IdeologicalDecisions: commonItems::parser
{
	public:
		explicit IdeologicalDecisions(std::istream& theStream);

		[[nodiscard]] const std::vector<decisionsCategory>& getCategories() const { return theCategories; }

		bool requiredIdeologiesExist(const std::set<std::string>& majorIdeologies);

	private:
		std::vector<decisionsCategory> theCategories;
		std::set<std::string> requiredIdeologies;
};

}



#endif // IDEOLOGICAL_DECISIONS_H