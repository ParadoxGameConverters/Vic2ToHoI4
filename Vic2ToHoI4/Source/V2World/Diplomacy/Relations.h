#ifndef VIC2_RELATIONS_H
#define VIC2_RELATIONS_H



#include "Date.h"
#include <optional>



namespace Vic2
{

class Relations
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] int getRelations() const { return value; }
	[[nodiscard]] int getLevel() const { return level; }

	[[nodiscard]] bool hasMilitaryAccess() const { return militaryAccess; }
	[[nodiscard]] const auto& getDiplomatLastSent() const { return lastSentDiplomat; }
	[[nodiscard]] const auto& getLastWar() const { return lastWar; }
	[[nodiscard]] const auto& getTruceUntil() const { return truceUntil; }
	[[nodiscard]] int getInfluenceValue() const { return influenceValue; }

  private:
	int value = 0;
	int level = 2;

	bool militaryAccess = false;
	std::optional<date> lastSentDiplomat;
	std::optional<date> lastWar;
	std::optional<date> truceUntil;
	int influenceValue = 0;
};

} // namespace Vic2



#endif // VIC2_RELATIONS_H