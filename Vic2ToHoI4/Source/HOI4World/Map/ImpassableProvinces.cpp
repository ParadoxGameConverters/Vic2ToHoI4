#include "ImpassableProvinces.h"
#include "../States/DefaultState.h"
#include "../../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"



HoI4::impassableProvinces::impassableProvinces(const std::map<int, HoI4::DefaultState>& states)
{
	LOG(LogLevel::Info) << "Finding impassable provinces";
	for (auto state: states)
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


bool HoI4::impassableProvinces::isProvinceImpassable(int provinceNumber) const
{
	return (impassibleProvinces.count(provinceNumber) > 0);
}