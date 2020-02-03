#include "HoI4War.h"
#include "Log.h"



HoI4::War::War(const Vic2::War& sourceWar, const CountryMapper& countryMapper)
{
	auto posssibleOriginalDefender = countryMapper.getHoI4Tag(sourceWar.getOriginalDefender());
	if (posssibleOriginalDefender)
	{
		originalDefender = *posssibleOriginalDefender;
	}
	else
	{
		LOG(LogLevel::Warning) << "Could not map " << sourceWar.getOriginalDefender() << ", original defender in a war";
	}

	CB = "annex_everything";

	for (auto defender: sourceWar.getDefenders())
	{
		if (defender != sourceWar.getOriginalDefender())
		{
			auto posssibleDefender = countryMapper.getHoI4Tag(defender);
			if (posssibleDefender)
			{
				extraDefenders.insert(*posssibleDefender);
			}
			else
			{
				LOG(LogLevel::Warning) << "Could not map " << defender << ", defending in a war";
			}
		}
	}

	auto posssibleOriginalAttacker = countryMapper.getHoI4Tag(sourceWar.getOriginalAttacker());
	if (posssibleOriginalAttacker)
	{
		originalAttacker = *posssibleOriginalAttacker;
	}
	else
	{
		LOG(LogLevel::Warning) << "Could not map " << sourceWar.getOriginalAttacker() << ", original attacker in a war";
	}

	for (auto attacker: sourceWar.getAttackers())
	{
		if (attacker != sourceWar.getOriginalAttacker())
		{
			auto posssibleAttacker = countryMapper.getHoI4Tag(attacker);
			if (posssibleAttacker)
			{
				extraAttackers.insert(*posssibleAttacker);
			}
			else
			{
				LOG(LogLevel::Warning) << "Could not map " << attacker << ", attacking in a war";
			}
		}
	}
}



std::ostream& HoI4::operator<<(std::ostream& outstream, const War& theWar)
{
	outstream << "declare_war_on = {\n";
	outstream << "\ttarget = " << theWar.originalDefender << "\n";
	outstream << "\ttype = " << theWar.CB << "\n";
	outstream << "}\n";

	for (auto extraAttacker: theWar.extraAttackers)
	{
		outstream << extraAttacker << " = {\n";
		outstream << "\tadd_to_war = {\n";
		outstream << "\t\ttargeted_alliance = " << theWar.originalAttacker << "\n";
		outstream << "\t\tenemy = " << theWar.originalDefender << "\n";
		outstream << "\t}\n";
		outstream << "}\n";
	}

	for (auto extraDefender : theWar.extraDefenders)
	{
		outstream << extraDefender << " = {\n";
		outstream << "\tadd_to_war = {\n";
		outstream << "\t\ttargeted_alliance = " << theWar.originalDefender << "\n";
		outstream << "\t\tenemy = " << theWar.originalAttacker << "\n";
		outstream << "\t}\n";
		outstream << "}\n";
	}

	outstream << "\n";

	return outstream;
}