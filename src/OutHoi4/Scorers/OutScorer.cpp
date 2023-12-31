#include "src/OutHoi4/Scorers/OutScorer.h"



std::ostream& HoI4::operator<<(std::ostream& output, const Scorer& scorer)
{
	output << scorer.getName() << " = {\n";
	output << "\ttargets " << scorer.getTargets() << "\n";
	output << "\t\n";
	output << "}\n";

	return output;
}