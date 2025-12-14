#ifndef FACTION_TEMPLATE_H
#define FACTION_TEMPLATE_H



#include "external/common_items/ConvenientParser.h"
#include <string>



namespace HoI4
{

class FactionTemplate: commonItems::parser
{
  public:
	FactionTemplate(const std::string& id, std::istream& theStream);

	[[nodiscard]] const auto& getId() const { return id; }
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getIcon() const { return icon; }
	[[nodiscard]] const auto& getManifest() const { return manifest; }
	[[nodiscard]] const auto& getGoals() const { return goals; }
	[[nodiscard]] const auto& getRules() const { return rules; }

	void removeGoal(const std::string& goal) { std::erase(goals, goal); }
	void addRule(const std::string& rule) { rules.push_back(rule); }
	void removeRule(const std::string& rule) { std::erase(rules, rule); }

	bool operator==(const FactionTemplate& other) const;
	friend std::ostream& operator<<(std::ostream& out, const FactionTemplate& theTemplate);

  private:
	std::string id;
	std::string name = "default_template_name";
	std::string icon = "GFX_faction_logo_generic";
	std::string manifest = "faction_manifest_regional_expansionism";
	std::vector<std::string> goals;
	std::vector<std::string> rules;
};

} // namespace HoI4



#endif // FACTION_TEMPLATE_H