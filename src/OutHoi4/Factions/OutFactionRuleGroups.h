#ifndef OUT_FACTION_RULE_GROUPS_H
#define OUT_FACTION_RULE_GROUPS_H



#include <map>
#include <vector>



namespace HoI4
{

void outputFactionRuleGroups(const std::filesystem::path& outputName,
	 const std::map<std::string, std::vector<std::string>>& ruleGroups);

} // namespace HoI4



#endif // OUT_FACTION_RULE_GROUPS_H