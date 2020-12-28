#ifndef HoI4RELATIONS_H_
#define HoI4RELATIONS_H_



#include "V2World/Diplomacy/Relations.h"



namespace HoI4
{

class Relations
{
  public:
	explicit Relations(std::string newTag):
		 tag(std::move(newTag)), value(0), guarantee(false), sphereLeader(false), influenceValue(0)
	{
	}

	Relations(std::string newTag, const Vic2::Relations& oldRelations):
		 tag(std::move(newTag)), value(oldRelations.getRelations()),
		 guarantee(oldRelations.getLevel() >= Vic2::opinionLevel::friendly),
		 sphereLeader(oldRelations.getLevel() == Vic2::opinionLevel::in_sphere),
		 influenceValue(oldRelations.getInfluenceValue()), militaryAccess(oldRelations.hasMilitaryAccess())
	{
	}

	[[nodiscard]] const auto& getTag() const { return tag; }
	[[nodiscard]] int getRelations() const { return value; }
	[[nodiscard]] bool getGuarantee() const { return guarantee; }
	[[nodiscard]] bool getSphereLeader() const { return sphereLeader; }
	[[nodiscard]] int getInfluenceValue() const { return influenceValue; }
	[[nodiscard]] bool hasMilitaryAccess() const { return militaryAccess; }

  private:
	std::string tag;
	int value;
	bool guarantee;
	bool sphereLeader;
	int influenceValue;
	bool militaryAccess = false;
};

} // namespace HoI4



#endif // HoI4RELATIONS_H_