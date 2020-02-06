#ifndef DECISIONS_FILE_H
#define DECISIONS_FILE_H



#include"DecisionsCategory.h"
#include "newParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class DecisionsFile: commonItems::parser
{
	public:
		void importDecisions(const std::string& filename);

		[[nodiscard]] std::vector<decisionsCategory>& getDecisions() { return decisions; }

	protected:
		std::vector<decisionsCategory> decisions;
};

}
#endif // DECISIONS_FILE_H