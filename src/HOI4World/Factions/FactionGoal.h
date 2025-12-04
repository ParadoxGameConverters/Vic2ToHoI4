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
	[[nodiscard]] const auto& getAllowed() const { return allowed; }
	[[nodiscard]] const auto& getVisible() const { return visible; }
	[[nodiscard]] const auto& getLockedGoal() const { return lockedGoal; }
	[[nodiscard]] const auto& getAvailable() const { return available; }
	[[nodiscard]] const auto& getSelectEffect() const { return selectEffect; }
	[[nodiscard]] const auto& getCompleted() const { return completed; }
	[[nodiscard]] const auto& getCancel() const { return cancel; }
	[[nodiscard]] const auto& getAutoComplete() const { return autoComplete; }
	[[nodiscard]] const auto& getCompleteEffect() const { return completeEffect; }
	[[nodiscard]] const auto& getAiWillDo() const { return aiWillDo; }
	[[nodiscard]] const auto& getIsManifest() const { return isManifest; }
	[[nodiscard]] const auto& getRatioProgress() const { return ratioProgress; }

	bool operator==(const FactionGoal& other) const;
	friend std::ostream& operator<<(std::ostream& out, const FactionGoal& theGoal);

  private:
	std::string id;
	std::string name = "default_goal_name";
	std::string description = "default_goal_desc";
	std::optional<std::string> group;
	std::optional<std::string> category;
	std::optional<std::string> allowed;
	std::optional<std::string> visible;
	bool lockedGoal = false;
	std::optional<std::string> available;
	std::optional<std::string> selectEffect;
	std::optional<std::string> completed;
	std::optional<std::string> cancel;
	bool autoComplete = false;
	std::optional<std::string> completeEffect;
	std::optional<std::string> aiWillDo;
	bool isManifest = false;
	std::optional<std::string> ratioProgress;
};

} // namespace HoI4



#endif // FACTION_GOAL_H