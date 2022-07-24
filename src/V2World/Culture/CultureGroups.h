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
	CultureGroups() = default;
	CultureGroups(std::map<std::string, std::string> mappings, std::map<std::string, std::set<std::string>> unions):
		 mappings_(std::move(mappings)), unions_(std::move(unions))
	{
	}

	[[nodiscard]] std::optional<std::string> GetGroup(const std::string& culture) const;
	[[nodiscard]] bool IsUnionCountry(const std::string& tag) const;
	[[nodiscard]] std::set<std::string> GetUnionCultures(const std::string& tag) const;

  private:
	std::map<std::string, std::string> mappings_;
	std::map<std::string, std::set<std::string>> unions_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_CULTURE_CULTURE_GROUPS_H