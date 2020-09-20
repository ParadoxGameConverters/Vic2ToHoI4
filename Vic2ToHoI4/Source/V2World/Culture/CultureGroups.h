#ifndef CULTURE_GROUPS_H
#define CULTURE_GROUPS_H



#include <map>
#include <optional>
#include <string>



namespace Vic2
{

class CultureGroups
{
  public:
	class Factory;

	[[nodiscard]] std::optional<std::string> getGroup(const std::string& culture) const;

  private:
	std::map<std::string, std::string> mappings;
};

} // namespace Vic2



#endif // CULTURE_GROUPS_H