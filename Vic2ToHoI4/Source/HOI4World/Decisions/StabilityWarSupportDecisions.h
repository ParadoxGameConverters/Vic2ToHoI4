#ifndef STABILITY_WAR_SUPPORT_DECISIONS_H
#define STABILITY_WAR_SUPPORT_DECISIONS_H



#include"DecisionsCategory.h"
#include "newParser.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class StabilityWarSupportDecisions: commonItems::parser
{
	public:
		StabilityWarSupportDecisions(std::istream& theStream);

		void updateDecisions(const std::set<std::string>& majorIdeologies);

		[[nodiscard]] const std::vector<decisionsCategory>& getDecisions() const { return decisions; }

	private:
		std::vector<decisionsCategory> decisions;
};

}


#endif // STABILITY_WAR_SUPPORT_DECISIONS_H