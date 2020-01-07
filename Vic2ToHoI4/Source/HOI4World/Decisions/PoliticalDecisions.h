#ifndef POLITICAL_DECISIONS_H
#define POLITICAL_DECISIONS_H



#include "IdeologicalDecisions.h"
#include "newParser.h"



namespace HoI4
{

class PoliticalDecisions: commonItems::parser
{
	public:
		void importDecisions(const std::string& filename);

		[[nodiscard]] const std::vector<decisionsCategory>& getDecisions() const { return decisions; }

		void updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

	private:
		std::vector<IdeologicalDecisions> allIdeologicalDecisions;
		std::vector<decisionsCategory> decisions;
};

}



#endif POLITICAL_DECISIONS_H