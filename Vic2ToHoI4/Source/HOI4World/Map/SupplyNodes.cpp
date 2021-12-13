#include "SupplyNodes.h"



std::set<int> HoI4::determineSupplyNodes(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	std::set<int> supplyNodes;
	for (const auto& [Vic2ProvinceNumber, Vic2Province]: Vic2Provinces)
	{
		if (!Vic2Province->isLandProvince())
		{
			continue;
		}

		const auto HoI4ProvinceNumbers = provinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNumber);
		if (HoI4ProvinceNumbers.empty())
		{
			continue;
		}

		supplyNodes.insert(HoI4ProvinceNumbers[0]);
	}

	return supplyNodes;
}