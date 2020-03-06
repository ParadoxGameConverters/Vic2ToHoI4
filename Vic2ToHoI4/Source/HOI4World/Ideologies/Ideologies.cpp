#include "Ideologies.h"
#include "IdeologyFile.h"
#include "Log.h"
#include "ParserHelpers.h"



HoI4::Ideologies::Ideologies(const Configuration& theConfiguration)
{
	registerKeyword("ideologies", [this](const std::string& unused, std::istream& theStream) {
		const IdeologyFile theFile(theStream);
		for (const auto& ideology: theFile.getIdeologies())
		{
			ideologies.insert(ideology);
		}
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	if (theConfiguration.getIdeologiesOptions() != ideologyOptions::keep_default)
	{
		parseFile("converterIdeologies.txt");
	}
	parseFile(theConfiguration.getHoI4Path() + "/common/ideologies/00_ideologies.txt");
	clearRegisteredKeywords();
}


void HoI4::Ideologies::identifyMajorIdeologies(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	if (theConfiguration.getIdeologiesOptions() == ideologyOptions::keep_major)
	{
		for (const auto& greatPower: greatPowers)
		{
			majorIdeologies.insert(greatPower->getGovernmentIdeology());
		}
		for (const auto& country: countries)
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
		for (const auto& ideology: theConfiguration.getSpecifiedIdeologies())
		{
			majorIdeologies.insert(ideology);
		}
	}
	// keep default is accomplished by only importing the default ideologies, so we can include
	//		all ideologies the converter knows for both keep_default and keep_all
	else
	{
		for (const auto& ideology: ideologies)
		{
			majorIdeologies.insert(ideology.first);
		}
	}
}


bool HoI4::Ideologies::subIdeologyIsValid(const std::string& ideologyName, const std::string_view subIdeology) const
{
	if (const auto ideology = ideologies.find(ideologyName); ideology != ideologies.end())
	{
		for (const auto& type: ideology->second.getTypes())
		{
			if (subIdeology == type)
			{
				return true;
			}
		}
	}

	return true;
}


std::optional<HoI4::Ideology> HoI4::Ideologies::getIdeology(const std::string& ideologyName) const
{
	if (const auto ideology = ideologies.find(ideologyName); ideology != ideologies.end())
	{
		return ideology->second;
	}
	else
	{
		return std::nullopt;
	}
}