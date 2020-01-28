#include "HoI4SupplyZone.h"
#include "Log.h"
#include "../../Configuration.h"
#include <fstream>



HoI4SupplyZone::HoI4SupplyZone(int _ID, int _value):
	ID(_ID),
	states(),
	value(_value)
{
}


void HoI4SupplyZone::output(const string& _filename) const
{
	string filename("output/" + theConfiguration.getOutputName() + "/map/supplyareas/" + _filename);
	ofstream out(filename);
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not open \"output/input/map/supplyareas/" + _filename;
		exit(-1);
	}
	out << "\n";
	out << "supply_area={" << endl;
	out << "\tid=" << ID << endl;
	out << "\tname=\"SUPPLYAREA_" << ID << "\"" << endl;
	out << "\tvalue=" << value << endl;
	out << "\tstates={" << endl;
	out << "\t\t";
	for (auto stateNum: states)
	{
		out << stateNum << " ";
	}
	out << endl;
	out << "\t}" << endl;
	out << "}" << endl;

	out.close();
}