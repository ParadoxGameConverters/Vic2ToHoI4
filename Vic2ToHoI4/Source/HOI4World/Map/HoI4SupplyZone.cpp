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