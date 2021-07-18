#include "HoI4AIStrategy.h"



HoI4::AIStrategy::AIStrategy(const Vic2::AIStrategy& oldStrategy, const std::string& HoI4Tag):
	 type(oldStrategy.getType()), id(HoI4Tag), value(oldStrategy.getValue())
{
	if (oldStrategy.getType() == "befriend")
	{
		type = "alliance";
		value = value / 2;
	}
	if (oldStrategy.getType() == "threat")
	{
		type = "contain";
	}
	if (oldStrategy.getType() == "rival")
	{
		type = "declare_war";
	}
}