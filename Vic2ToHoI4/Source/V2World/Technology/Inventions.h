#ifndef INVENTIONS_H
#define INVENTIONS_H



#include <map>
#include <optional>
#include <string>



namespace Vic2
{

class Inventions
{
  public:
	class Factory;

	std::optional<std::string> getInventionName(int inventionNum) const;

  private:
	std::map<int, std::string> inventionNumsToNames;
};

} // namespace Vic2



#endif // INVENTIONS_H
