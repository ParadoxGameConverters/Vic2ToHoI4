#ifndef GAME_RULE_H
#define GAME_RULE_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/GameRules/GameRuleOption.h"
#include <optional>
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{

class GameRule
{
  public:
	class Parser;
	GameRule(std::string _key,
		 std::string _name,
		 std::optional<std::string> _requiredDlc,
		 std::string _group,
		 std::optional<std::string> _icon,
		 std::vector<GameRuleOption> _options):
		 key(std::move(_key)),
		 name(std::move(_name)), requiredDlc(std::move(_requiredDlc)), group(std::move(_group)), icon(std::move(_icon)),
		 options(std::move(_options))
	{
	}

	friend std::ostream& operator<<(std::ostream& output, const GameRule& rule);

	[[nodiscard]] const auto& getKey() const { return key; }

  private:
	std::string key;
	std::string name;
	std::optional<std::string> requiredDlc;
	std::string group;
	std::optional<std::string> icon;
	std::vector<GameRuleOption> options;
};


class GameRule::Parser: commonItems::parser
{
  public:
	GameRule parseRule(const std::string& key, std::istream& theStream);
};

} // namespace HoI4



#endif // GAME_RULE_H