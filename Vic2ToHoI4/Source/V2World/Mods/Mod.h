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


inline bool operator==(const Mod& a, const Mod& b)
{
	return a.getName() == b.getName();
}

} // namespace Vic2



#endif // MOD_H