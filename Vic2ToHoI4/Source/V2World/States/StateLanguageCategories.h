#ifndef STATE_LANGUAGE_CATEGORIES_H
#define STATE_LANGUAGE_CATEGORIES_H



#include <map>
#include <optional>
#include <string>



namespace Vic2
{

class StateLanguageCategories
{
  public:
	class Builder;
	class Factory;

	[[nodiscard]] std::optional<std::string> getStateCategory(const std::string& stateName) const;

  private:
	std::map<std::string, std::string> categories;
};

} // namespace Vic2



#endif // STATE_LANGUAGE_CATEGORIES_H