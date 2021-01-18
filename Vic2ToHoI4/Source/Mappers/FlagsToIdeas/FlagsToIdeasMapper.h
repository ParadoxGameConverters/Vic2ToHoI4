#ifndef FLAGS_TO_IDEAS_MAPPER
#define FLAGS_TO_IDEAS_MAPPER



#include <map>
#include <optional>
#include <string>



namespace Mappers
{

class FlagsToIdeasMapper
{
  public:
	class Factory;

	[[nodiscard]] std::optional<std::string> getIdea(const std::string& flag) const;

  private:
	std::map<std::string, std::string> mappings;
};

} // namespace mappers



#endif // FLAGS_TO_IDEAS_MAPPER