#ifndef SOUND_EFFECT_MAPPER_LINK
#define SOUND_EFFECT_MAPPER_LINK



#include <set>
#include <string>



namespace HoI4
{

class SoundEffectsMapperLink
{
  public:
	class Factory;

	[[nodiscard]] const auto& getCultures() const { return cultures; }
	[[nodiscard]] const auto& getSounds() const { return sounds; }

  private:
	std::set<std::string> cultures;
	std::set<std::string> sounds;
};

} // namespace HoI4



#endif // SOUND_EFFECT_MAPPER_LINK