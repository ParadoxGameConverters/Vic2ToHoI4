#ifndef MOD_H
#define MOD_H


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

  private:
	std::string name;
	std::string directory;
};

} // namespace Vic2



#endif // MOD_H