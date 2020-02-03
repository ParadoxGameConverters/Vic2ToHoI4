#include "HoI4Agreement.h"
#include <fstream>



HoI4Agreement::HoI4Agreement(const string& _country1, const string& _country2, const Vic2::Agreement* oldAgreement):
	type(oldAgreement->getType()),
	country1(_country1),
	country2(_country2),
	relationshipValue(0),
	startDate(oldAgreement->getDate())
{
}


HoI4Agreement::HoI4Agreement(const string& _country1, const string& _country2, const string& _type, int _relationshipValue, const date& _startDate):
	type(_type),
	country1(_country1),
	country2(_country2),
	relationshipValue(_relationshipValue),
	startDate(_startDate)
{
}


ofstream& operator << (ofstream& output, HoI4Agreement& instance)
{
	output << instance.type << "=\n";
	output << "{\n";
	output << "\tfirst=\"" << instance.country1 << "\"\n";
	output << "\tsecond=\"" << instance.country2 << "\"\n";
	if (instance.type == "relation")
	{
		output << "\tvalue=\"%i\"\n" << instance.relationshipValue;
	}
	output << "\tstart_date=\"%s\"\n" << instance.startDate;
	output << "\tend_date=\"1949.1.1\"\n";
	output << "}\n";
	output << "\n";

	return output;
}