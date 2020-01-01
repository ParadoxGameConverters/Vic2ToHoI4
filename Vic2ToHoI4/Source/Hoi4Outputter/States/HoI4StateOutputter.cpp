#include "HoI4StateOutputter.h"
#include <iomanip>



void HoI4::outputHoI4State(std::ostream& output, const HoI4::State& theState, const Configuration& theConfiguration)
{
	output << "\n";
	output << "state={" << "\n";
	output << "\tid=" << theState.getID() << "\n";
	output << "\tname=\"STATE_" << theState.getID() << "\"\n";
	if (theState.hasResources())
	{
		output << "\tresources={\n";
		output << std::fixed;
		output << std::setprecision(3);
		for (auto resource: theState.getResources())
		{
			output << "\t\t" << resource.first << "=" << resource.second << "\n";
		}
		output << "\t}\n";
	}
	if (theState.isImpassable())
	{
		output << "\timpassable = yes\n";
	}
	output << "\n";
	output << "\thistory={\n";
	if (!theState.getOwner().empty())
	{
		output << "\t\towner = " << theState.getOwner() << "\n";
	}
	if (!theState.isImpassable())
	{
		if ((theState.getVpValue() > 0) && (theState.getVPLocation()))
		{
			if (theConfiguration.getDebug())
			{
				output << "\t\tvictory_points = {\n";
				output << "\t\t\t" << *theState.getVPLocation() << " " << (theState.getVpValue() + 10) << "\n";
				output << "\t\t}\n";
				for (auto VP: theState.getDebugVPs())
				{
					if (VP == theState.getVPLocation())
					{
						continue;
					}
					output << "\t\tvictory_points = { " << VP << " 5\n";
					output << "\t}\n";
				}
				for (auto VP: theState.getSecondaryDebugVPs())
				{
					if (VP == theState.getVPLocation())
					{
						continue;
					}
					output << "\t\tvictory_points = { " << VP << " 1 }\n";
				}
			}
			else
			{
				output << "\t\tvictory_points = {\n";
				output << "\t\t\t" << *theState.getVPLocation() << " " << theState.getVpValue() << " \n";
				output << "\t\t}\n";
			}
		}
	}
	if (!theState.isImpassable())
	{
		output << "\t\tbuildings = {\n";
		output << "\t\t\tinfrastructure = " << theState.getInfrastructure() << "\n";
		output << "\t\t\tindustrial_complex = " << theState.getCivFactories() << "\n";
		output << "\t\t\tarms_factory = " << theState.getMilFactories() << "\n";
		if (theState.getDockyards() > 0)
		{
			output << "\t\t\tdockyard = " << theState.getDockyards() << "\n";
		}

		for (auto navalBase: theState.getNavalBases())
		{
			output << "\t\t\t" << navalBase.first << " = {\n";
			output << "\t\t\t\tnaval_base = " << navalBase.second << "\n";
			output << "\t\t\t}\n";
		}

		output << "\t\t\tair_base = " << theState.getAirbaseLevel() << "\n";
		output << "\n";
		output << "\t\t}\n";
	}
	for (auto core: theState.getCores())
	{
		output << "\t\tadd_core_of = " << core << "\n";
	}
	for (auto countryControlledProvinces: theState.getControlledProvinces())
	{
		output << "\t\t" << countryControlledProvinces.first << " = {\n";
		for (auto province : countryControlledProvinces.second)
		{
			output << "\t\t\tset_province_controller = " << province << "\n";
		}
		output << "\t\t}\n";
	}
	output << "\t}\n";
	output << "\n";
	output << "\tprovinces={\n";
	output << "\t\t";
	for (auto provnum: theState.getProvinces())
	{
		output << provnum << " ";
	}
	output << "\n";
	output << "\t}\n";
	output << "\tmanpower=" << theState.getManpower() << "\n";
	output << "\tbuildings_max_level_factor=1.000\n";
	output << "\tstate_category=" << theState.getCategory() << "\n";
	output << "}\n";
}