#ifndef SCRIPTED_EFFECT_H
#define SCRIPTED_EFFECT_H



#include <string>
#include <vector>



namespace HoI4
{

class ScriptedEffect
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getItems() const { return items; }
	[[nodiscard]] auto& getMutableItems() { return items; }


  private:
	std::string name;
	std::vector<std::pair<std::string, std::string>> items;
};

} // namespace HoI4



#endif // SCRIPTED_EFFECT_H