#ifndef SRC_V2WORLD_CULTURE_CULTURE_GROUPS_H
#define SRC_V2WORLD_CULTURE_CULTURE_GROUPS_H



#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{

class CultureGroups
{
  public:
	class Factory;

	[[nodiscard]] std::optional<std::string> GetGroup(const std::string& culture) const;
	[[nodiscard]] bool IsUnionCountry(const std::string& tag) const;

  private:
	std::map<std::string, std::string> mappings_;
	std::set<std::string> union_tags_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_CULTURE_CULTURE_GROUPS_H