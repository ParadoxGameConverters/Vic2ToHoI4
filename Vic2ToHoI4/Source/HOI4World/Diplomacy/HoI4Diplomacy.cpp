#include "HoI4Diplomacy.h"
#include "HoI4Agreement.h"
#include "Log.h"
#include "../../Configuration.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



void HoI4Diplomacy::output() const
{
	/*LOG(LogLevel::Debug) << "Writing diplomacy";
	fstream alliances("output/" + theConfiguration.getOutputName() + "/history/diplomacy/Alliances.txt");
	if (alliances.is_open())
	{
		LOG(LogLevel::Error) << "Could not create alliances history file";
		exit(-1);
	}

	fstream guarantees("output/" + theConfiguration.getOutputName() + "/history/diplomacy/Guarantees.txt");
	if (guarantees.is_open())
	{
		LOG(LogLevel::Error) << "Could not create guarantees history file";
		exit(-1);
	}

	fstream puppetStates("output/" + theConfiguration.getOutputName() + "/history/diplomacy/PuppetStates.txt");
	if (puppetStates.is_open())
	{
		LOG(LogLevel::Error) << "Could not create puppet states history file";
		exit(-1);
	}

	fstream relations("output/" + theConfiguration.getOutputName() + "/history/diplomacy/relations.txt");
	if (relations.is_open())
	{
		LOG(LogLevel::Error) << "Could not create relations history file";
		exit(-1);
	}
	
	for (auto itr: agreements)
	{
		if (itr->getType() == "guarantee")
		{
			guarantees << itr;
		}
		else if (itr->getType() == "vassal")
		{
			puppetStates << itr;
		}
		else if (itr->getType() == "alliance")
		{
			alliances << itr;
		}
		else if (itr->getType() == "relation")
		{
			relations << itr;
		}
		else
		{
			LOG(LogLevel::Warning) << "Cannot ouput diplomatic agreement type " << itr->getType();
			continue;
		}
	}
	
	alliances.close();
	guarantees.close();
	puppetStates.close();
	relations.close();*/
}


void HoI4Diplomacy::addAgreement(const HoI4Agreement* agr)
{
	bool alreadyExists = false;

	if (agr->getType() == "relation")
	{
		for (auto itr: agreements)
		{
			if (agr == itr)
			{
				alreadyExists = true;
				break;
			}
		}
	}

	if (!alreadyExists)
	{
		agreements.push_back(agr);
	}
}
