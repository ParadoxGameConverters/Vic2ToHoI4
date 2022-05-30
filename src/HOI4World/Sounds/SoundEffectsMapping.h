#ifndef SOUND_EFFECTS_MAPPING
#define SOUND_EFFECTS_MAPPING



#include <set>
#include <string>



namespace HoI4
{

class SoundEffectsMapping
{
  public:
	SoundEffectsMapping(std::string _name, std::set<std::string> _sounds):
		 name(std::move(_name)), sounds(std::move(_sounds))
	{
	}

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getSounds() const { return sounds; }

	bool operator<(const SoundEffectsMapping& rhs) const { return name < rhs.name; }

  private:
	std::string name;
	std::set<std::string> sounds;
};

} // namespace HoI4



#endif // SOUND_EFFECTS_MAPPING