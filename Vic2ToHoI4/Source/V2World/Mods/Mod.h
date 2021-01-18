#ifndef MOD_H
#define MOD_H



#include <set>
#include <string>



namespace Vic2
{

class Mod
{
  public:
	class Builder;
	class Factory;
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getDirectory() const { return directory; }
	[[nodiscard]] const auto& getDependencies() const { return dependencies; }

  private:
	std::string name;
	std::string directory;
	std::set<std::string> dependencies;
};

} // namespace Vic2



#endif // MOD_H