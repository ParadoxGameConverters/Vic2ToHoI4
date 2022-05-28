#ifndef VIC2_RELATIONS_H
#define VIC2_RELATIONS_H



#include "Date.h"
#include <optional>



namespace Vic2
{

enum class opinionLevel
{
	hostile = 0,
	opposed = 1,
	neutral = 2,
	cordial = 3,
	friendly = 4,
	in_sphere = 5,
};


class Relations
{
  public:
	class Factory;
	class Builder;
	bool operator==(const Relations&) const;

	[[nodiscard]] int getRelations() const { return value; }
	[[nodiscard]] opinionLevel getLevel() const { return level; }

	[[nodiscard]] bool hasMilitaryAccess() const { return militaryAccess; }
	[[nodiscard]] const auto& getDiplomatLastSent() const { return lastSentDiplomat; }
	[[nodiscard]] const auto& getLastWar() const { return lastWar; }
	[[nodiscard]] const auto& getTruceUntil() const { return truceUntil; }
	[[nodiscard]] int getInfluenceValue() const { return influenceValue; }

  private:
	int value = 0;
	opinionLevel level = opinionLevel::neutral;

	bool militaryAccess = false;
	std::optional<date> lastSentDiplomat;
	std::optional<date> lastWar;
	std::optional<date> truceUntil;
	int influenceValue = 0;
};

} // namespace Vic2



#endif // VIC2_RELATIONS_H