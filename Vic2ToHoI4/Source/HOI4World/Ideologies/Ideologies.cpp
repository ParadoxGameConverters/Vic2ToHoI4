#include "Ideologies.h"
#include "IdeologyFile.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"



HoI4::Ideologies::Ideologies(const Configuration& theConfiguration)
{
	registerKeyword("ideologies", [this](const std::string& unused, std::istream& theStream)
	{
		IdeologyFile theFile(theStream);
		for (auto ideology : theFile.getIdeologies())
		{
			ideologies.insert(ideology);
		}
	});

	if (theConfiguration.getIdeologiesOptions() != ideologyOptions::keep_default)
	{
		parseFile("converterIdeologies.txt");
	}
	parseFile(theConfiguration.getHoI4Path() + "/common/ideologies/00_ideologies.txt");
	clearRegisteredKeywords();
}


void HoI4::Ideologies::identifyMajorIdeologies(std::vector<std::shared_ptr<HoI4::Country>> greatPowers, std::map<std::string, std::shared_ptr<HoI4::Country>> countries)
{
	if (theConfiguration.getIdeologiesOptions() == ideologyOptions::keep_major)
	{
		for (auto greatPower : greatPowers)
		{
			majorIdeologies.insert(greatPower->getGovernmentIdeology());
		}

		for (auto country : countries)
		{
			if (country.second->isHuman())
			{
				majorIdeologies.insert(country.second->getGovernmentIdeology());
			}
		}
		majorIdeologies.insert("neutrality");
	}
	else if (theConfiguration.getIdeologiesOptions() == ideologyOptions::specified)
	{
		for (auto ideology : theConfiguration.getSpecifiedIdeologies())
		{
			majorIdeologies.insert(ideology);
		}
	}
	// keep default is accomplished by only importing the default ideologies, so we can include
	//		all ideologies the converter knows for both keep_default and keep_all
	else
	{
		for (auto ideology : ideologies)
		{
			majorIdeologies.insert(ideology.first);
		}
	}
}


bool HoI4::Ideologies::subIdeologyIsValid(const std::string& ideologyName, std::string_view subIdeology) const
{
	auto ideology = ideologies.find(ideologyName);
	if (ideology != ideologies.end())
	{
		for (auto type : ideology->second->getTypes())
		{
			if (subIdeology == type)
			{
				return true;
			}
		}
	}

	return true;
}


void HoI4::Ideologies::output()
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/ideologies/"))
	{
		Log(LogLevel::Error) << "Could not create output/" + theConfiguration.getOutputName() + "/common/ideologies/";
	}
	std::ofstream ideologyFile("output/" + theConfiguration.getOutputName() + "/common/ideologies/00_ideologies.txt");
	ideologyFile << "ideologies = {\n";
	ideologyFile << "\t\n";
	for (auto ideologyName : majorIdeologies)
	{
		auto ideology = ideologies.find(ideologyName);
		if (ideology != ideologies.end())
		{
			ideology->second->output(ideologyFile);
		}
	}
	ideologyFile << "}";
	ideologyFile.close();
}

