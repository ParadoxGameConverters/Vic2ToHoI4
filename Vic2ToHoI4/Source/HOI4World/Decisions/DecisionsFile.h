#ifndef DECISIONS_FILE_H
#define DECISIONS_FILE_H



#include"DecisionsCategory.h"
#include "newParser.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class DecisionsFile: commonItems::parser
{
	public:
		void importDecisions(const std::string& filename);

		[[nodiscard]] const std::vector<decisionsCategory>& getDecisions() const { return decisions; }

	protected:
		std::vector<decisionsCategory> decisions;
};

}
#endif // DECISIONS_FILE_H