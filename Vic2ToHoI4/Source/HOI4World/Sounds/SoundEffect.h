#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H



#include <set>
#include <string>



namespace HoI4
{

class SoundEffect
{
  public:
	SoundEffect(std::string _name, std::set<std::string> _sounds): name(std::move(_name)), sounds(std::move(_sounds)) {}

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getSounds() const { return sounds; }

  private:
	std::string name;
	std::set<std::string> sounds;
};

} // namespace HoI4



#endif // SOUND_EFFECT_H