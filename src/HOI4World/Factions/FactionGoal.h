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

	void setId(const std::string& newValue) { id = newValue; }
	void setName(const std::string& newValue) { name = newValue; }
	void setDescription(const std::string& newValue) { description = newValue; }
	void setGroup(const std::string& newValue) { group = newValue; }
	void setCategory(const std::string& newValue) { category = newValue; }
	void setAllowed(const std::string& newValue) { allowed = newValue; }
	void setVisible(const std::string& newValue) { visible = newValue; }
	void setLockedGoal(bool newValue) { lockedGoal = newValue; }
	void setAvailable(const std::string& newValue) { available = newValue; }
	void setSelectEffect(const std::string& newValue) { selectEffect = newValue; }
	void setCompleted(const std::string& newValue) { completed = newValue; }
	void setCancel(const std::string& newValue) { cancel = newValue; }
	void setAutoComplete(bool newValue) { autoComplete = newValue; }
	void setCompleteEffect(const std::string& newValue) { completeEffect = newValue; }
	void setAiWillDo(const std::string& newValue) { aiWillDo = newValue; }
	void setIsManifest(bool newValue) { isManifest = newValue; }
	void setRatioProgress(const std::string& newValue) { ratioProgress = newValue; }

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