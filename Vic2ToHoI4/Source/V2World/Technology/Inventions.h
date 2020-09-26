#ifndef INVENTIONS_H
#define INVENTIONS_H



#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class Inventions
{
  public:
	class Factory;

	[[nodiscard]] std::optional<std::string> getInventionName(unsigned int inventionNumber) const;

  private:
	std::vector<std::string> inventionNames;
};

} // namespace Vic2



#endif // INVENTIONS_H