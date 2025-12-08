#ifndef FACTION_RULE_H
#define FACTION_RULE_H



#include "external/common_items/ConvenientParser.h"
#include <string>



namespace HoI4
{

class FactionRule: commonItems::parser
{
  public:
	FactionRule(const std::string& id, std::istream& theStream);

	[[nodiscard]] const auto& getId() const { return id; }
	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getVisible() const { return visible; }
	[[nodiscard]] const auto& getAvailable() const { return available; }
	[[nodiscard]] const auto& getCanRemove() const { return canRemove; }
	[[nodiscard]] const auto& getTrigger() const { return trigger; }
	[[nodiscard]] const auto& getDismissMemberTrigger() const { return dismissMemberTrigger; }
	[[nodiscard]] const auto& getGovernmentInExileAllowedTrigger() const { return governmentInExileAllowedTrigger; }
	[[nodiscard]] const auto& getPeaceActionModifiers() const { return peaceActionModifiers; }
	[[nodiscard]] const auto& getModifier() const { return modifier; }
	[[nodiscard]] const auto& getEffect() const { return effect; }
	[[nodiscard]] const auto& getAiWillDo() const { return aiWillDo; }

	void setId(const std::string& newValue) { id = newValue; }
	void setType(const std::string& newValue) { type = newValue; }
	void setVisible(const std::string& newValue) { visible = newValue; }
	void setAvailable(const std::string& newValue) { available = newValue; }
	void setCanRemove(const std::string& newValue) { canRemove = newValue; }
	void setTrigger(const std::string& newValue) { trigger = newValue; }
	void setDismissMemberTrigger(const std::string& newValue) { dismissMemberTrigger = newValue; }
	void setGovernmentInExileAllowedTrigger(const std::string& newValue) { governmentInExileAllowedTrigger = newValue; }
	void setPeaceActionModifiers(const std::string& newValue) { peaceActionModifiers = newValue; }
	void setModifier(const std::string& newValue) { modifier = newValue; }
	void setEffect(const std::string& newValue) { effect = newValue; }
	void setAiWillDo(const std::string& newValue) { aiWillDo = newValue; }

	bool operator==(const FactionRule& other) const;
	friend std::ostream& operator<<(std::ostream& out, const FactionRule& theRule);

  private:
	std::string id;
	std::string type = "default_rule_type";
	std::optional<std::string> visible;
	std::optional<std::string> available;
	std::optional<std::string> canRemove;
	std::optional<std::string> trigger;
	std::optional<std::string> dismissMemberTrigger;
	std::optional<std::string> governmentInExileAllowedTrigger;
	std::optional<std::string> peaceActionModifiers;
	std::optional<std::string> modifier;
	std::optional<std::string> effect;
	std::optional<std::string> aiWillDo;
};

} // namespace HoI4



#endif // FACTION_RULE_H