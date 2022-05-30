#ifndef DECISIONS_FILE_H
#define DECISIONS_FILE_H



#include "DecisionsInCategory.h"
#include "Parser.h"
#include <string>
#include <vector>



namespace HoI4
{

class DecisionsFile: commonItems::parser
{
  public:
	void importDecisions(const std::string& filename);

	[[nodiscard]] const std::vector<DecisionsInCategory>& getDecisions() const { return decisions; }

  protected:
	std::vector<DecisionsInCategory> decisions;
};

} // namespace HoI4
#endif // DECISIONS_FILE_H