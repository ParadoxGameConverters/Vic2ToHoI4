#include "ImpassableProvinces.h"
#include "HOI4World/States/DefaultState.h"
#include "Log.h"



HoI4::ImpassableProvinces::ImpassableProvinces(const std::map<int, DefaultState>& states)
{
	Log(LogLevel::Info) << "\t\tFinding impassable provinces";
	for (const auto& state: states)
	{
		if (state.second.isImpassable())
		{
			for (auto province: state.second.getProvinces())
			{
				impassibleProvinces.insert(province);
			}
		}
	}
}


bool HoI4::ImpassableProvinces::isProvinceImpassable(const int provinceNumber) const
{
	return impassibleProvinces.contains(provinceNumber);
}