#include "HoI4War.h"
#include "HOI4World/HoI4Country.h"
#include "Log.h"



HoI4::War::War(const Vic2::War& sourceWar,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const Mappers::CountryMapper& countryMapper,
	 const Mappers::CasusBellis& casusBellis,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const std::map<int, int>& provinceToStateIDMap)
{
	auto possibleOriginalDefender = countryMapper.getHoI4Tag(sourceWar.getOriginalDefender());
	if (possibleOriginalDefender)
	{
		originalDefender = *possibleOriginalDefender;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not map " << sourceWar.getOriginalDefender() << ", original defender in a war";
	}

	for (const auto& defender: sourceWar.getDefenders())
	{
		if (defender == sourceWar.getOriginalDefender())
		{
			continue;
		}
		const auto& possibleDefender = countryMapper.getHoI4Tag(defender);
		if (!possibleDefender)
		{
			Log(LogLevel::Warning) << "Could not map " << defender << ", defending in a war";
			continue;
		}
		if (const auto& defCountry = countries.find(*possibleDefender);
			 defCountry != countries.end() && !defCountry->second->getPuppetMaster())
		{
			extraDefenders.insert(*possibleDefender);
		}
	}

	auto possibleOriginalAttacker = countryMapper.getHoI4Tag(sourceWar.getOriginalAttacker());
	if (possibleOriginalAttacker)
	{
		originalAttacker = *possibleOriginalAttacker;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not map " << sourceWar.getOriginalAttacker() << ", original attacker in a war";
	}

	for (const auto& attacker: sourceWar.getAttackers())
	{
		if (attacker == sourceWar.getOriginalAttacker())
		{
			continue;
		}
		auto possibleAttacker = countryMapper.getHoI4Tag(attacker);
		if (!possibleAttacker)
		{
			Log(LogLevel::Warning) << "Could not map " << attacker << ", attacking in a war";
			continue;
		}
		if (const auto& attCountry = countries.find(*possibleAttacker);
			 attCountry != countries.end() && !attCountry->second->getPuppetMaster())
		{
			extraAttackers.insert(*possibleAttacker);
		}
	}

	CB = casusBellis.getWarGoalFromCasusBelli(sourceWar.getCasusBelli());

	if (const auto possibleVic2Province = sourceWar.getProvince(); possibleVic2Province)
	{
		if (const auto HoI4Provinces = provinceMapper.getVic2ToHoI4ProvinceMapping(*possibleVic2Province);
			 !HoI4Provinces.empty())
		{
			if (const auto provinceToStateIDMapping = provinceToStateIDMap.find(HoI4Provinces[0]);
				 provinceToStateIDMapping != provinceToStateIDMap.end())
			{
				state = provinceToStateIDMapping->second;
			}
		}
	}
}