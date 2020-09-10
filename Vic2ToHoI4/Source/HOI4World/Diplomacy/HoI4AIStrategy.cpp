#include "HoI4AIStrategy.h"

void HoI4::AIStrategy::updateStrategy()
{
	if (type == "befriend")
	{
		type = "alliance";
		value = value / 2;
	}
	if (type == "threat")
	{
		type = "contain";
	}
	if (type == "rival")
	{
		type = "declare_war";
	}
}