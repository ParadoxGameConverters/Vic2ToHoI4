#ifndef GAME_RULE_OPTION_H
#define GAME_RULE_OPTION_H



#include "external/common_items/ConvenientParser.h"
#include <optional>
#include <string>



namespace HoI4
{

class GameRuleOption
{
  public:
	class Parser;
	GameRuleOption(const bool _isDefault,
		 std::string _name,
		 std::string _text,
		 std::string _description,
		 const std::optional<bool>& _allowAchievements):
		 isDefault(_isDefault),
		 name(std::move(_name)), text(std::move(_text)), description(std::move(_description)),
		 allowAchievements(_allowAchievements)
	{
	}

	friend std::ostream& operator<<(std::ostream& output, const GameRuleOption& option);

  private:
	bool isDefault = false;
	std::string name;
	std::string text;
	std::string description;
	std::optional<bool> allowAchievements;
};


class GameRuleOption::Parser: commonItems::parser
{
  public:
	GameRuleOption parseOption(const std::string& key, std::istream& theStream);
};

} // namespace HoI4



#endif // GAME_RULE_OPTION_H