#include "HoI4Airforce.h"



HoI4Airplane::HoI4Airplane(const string& _type, const string& _owner, int _amount):
	type(_type),
	owner(_owner),
	amount(_amount)
{
}



ofstream& operator << (ofstream& output, const HoI4Airplane& instance)
{
	output << "\t\t" << instance.type << " = {\n";
	output << "\t\t\towner = \"" << instance.owner << "\"\n";
	output << "\t\t\tamount = " << instance.amount << "\n";
	output << "\t\t}\n";

	return output;
}