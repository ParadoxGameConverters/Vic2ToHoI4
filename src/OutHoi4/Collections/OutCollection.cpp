#include "src/OutHoi4/Collections/OutCollection.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Collection& theCollection)
{
	out << theCollection.id << " = {\n";
	out << "\tinput = " << theCollection.input << "\n";
	out << "\tname = " << theCollection.name << "\n";
	out << "\toperators " << theCollection.operators << "\n";
	out << "}\n";

	return out;
}