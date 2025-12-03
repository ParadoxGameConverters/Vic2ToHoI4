#ifndef FACTION_GOAL_H
#define FACTION_GOAL_H



#include "external/common_items/ConvenientParser.h"
#include <string>



namespace HoI4
{

class FactionGoal: commonItems::parser
{
  public:
	FactionGoal(const std::string& id, std::istream& theStream);

	[[nodiscard]] const auto& getId() const { return id; }
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getDescription() const { return description; }
	[[nodiscard]] const auto& getGroup() const { return group; }
	[[nodiscard]] const auto& getCategory() const { return category; }
	[[nodiscard]] const auto& getVisible() const { return visible; }
	[[nodiscard]] const auto& getLockedGoal() const { return lockedGoal; }
	[[nodiscard]] const auto& getAvailable() const { return available; }
	[[nodiscard]] const auto& getCompleted() const { return completed; }
	[[nodiscard]] const auto& getCompleteEffect() const { return completeEffect; }

	friend std::ostream& operator<<(std::ostream& out, const FactionGoal& theGoal);

  private:
	std::string id;
	std::string name;
	std::string description;
	std::string group;
	std::string category;
	std::string visible;
	bool lockedGoal = false;
	std::string available;
	std::string completed;
	std::string completeEffect;
};

} // namespace HoI4



#endif // FACTION_GOAL_H