#include "src/HOI4World/Diplomacy/HoI4Relations.h"


HoI4::Relations::Relations(std::string newTag, const Vic2::Relations& oldRelations, const date& startDate):
	 tag(std::move(newTag)), value(oldRelations.getRelations()),
	 guarantee(oldRelations.getLevel() >= Vic2::opinionLevel::friendly),
	 sphereLeader(oldRelations.getLevel() == Vic2::opinionLevel::in_sphere),
	 influenceValue(oldRelations.getInfluenceValue()), militaryAccess(oldRelations.hasMilitaryAccess()),
	 truceUntil(oldRelations.getTruceUntil())
{
	if (truceUntil)
	{
		if (const auto& diffInYears = truceUntil->diffInYears(startDate); diffInYears > 0)
		{
			truceDuration = static_cast<int>(365 * diffInYears);
		}
	}
}