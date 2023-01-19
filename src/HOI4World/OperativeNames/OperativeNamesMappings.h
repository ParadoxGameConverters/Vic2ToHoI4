#ifndef OPERATIVE_NAMES_MAPPINGS_H
#define OPERATIVE_NAMES_MAPPINGS_H



#include <map>
#include <string>



namespace HoI4
{

class OperativeNamesMappings
{
  public:
	class Factory;
	[[nodiscard]] std::string getMatchingNamesSet(const std::string& primaryCulture) const;

  private:
	std::map<std::string, std::string> cultureToNamesSetMap;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_MAPPINGS_H