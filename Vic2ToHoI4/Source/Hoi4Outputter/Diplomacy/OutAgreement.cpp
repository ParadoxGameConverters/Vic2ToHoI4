#include "OutAgreement.h"



std::ostream& HoI4::operator<<(std::ostream& output, const Agreement& agreement)
{
	output << agreement.type << "=\n";
	output << "{\n";
	output << "\tfirst=\"" << agreement.country1 << "\"\n";
	output << "\tsecond=\"" << agreement.country2 << "\"\n";
	if (agreement.type == "relation")
	{
		output << "\tvalue=\"%i\"\n" << agreement.relationshipValue;
	}
	output << "\tstart_date=\"%s\"\n" << agreement.startDate;
	output << "\tend_date=\"1949.1.1\"\n";
	output << "}\n";
	output << "\n";

	return output;
}