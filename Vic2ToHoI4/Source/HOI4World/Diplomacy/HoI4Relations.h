#ifndef HoI4RELATIONS_H_
#define HoI4RELATIONS_H_



#include "Date.h"
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
	Relations(std::string newTag, const Vic2::Relations& oldRelations, const date& startDate);

	[[nodiscard]] const auto& getTag() const { return tag; }
	[[nodiscard]] int getRelations() const { return value; }
	[[nodiscard]] bool getGuarantee() const { return guarantee; }
	[[nodiscard]] bool getSphereLeader() const { return sphereLeader; }
	[[nodiscard]] int getInfluenceValue() const { return influenceValue; }
	[[nodiscard]] bool hasMilitaryAccess() const { return militaryAccess; }
	[[nodiscard]] const auto& getTruceUntil() const { return truceUntil; }
	[[nodiscard]] std::optional<int> getTruceDuration() const { return truceDuration; }

  private:
	std::string tag;
	int value;
	bool guarantee;
	bool sphereLeader;
	int influenceValue;
	bool militaryAccess = false;
	std::optional<date> truceUntil;
	std::optional<int> truceDuration;
};

} // namespace HoI4



#endif // HoI4RELATIONS_H_