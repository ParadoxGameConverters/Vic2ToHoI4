#ifndef OCCUPATION_LAW_H
#define OCCUPATION_LAW_H



#include <optional>
#include <string>



namespace HoI4
{

class OccupationLaw
{
  public:
	class Factory;
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getIcon() const { return icon; }
	[[nodiscard]] const auto& getDefaultLaw() const { return defaultLaw; }
	[[nodiscard]] const auto& getSoundEffect() const { return soundEffect; }
	[[nodiscard]] const auto& getVisible() const { return visible; }
	[[nodiscard]] const auto& getStateModifier() const { return stateModifier; }
	[[nodiscard]] const auto& getSuppressedStateModifier() const { return suppressedStateModifier; }
	[[nodiscard]] const auto& getStartingLaw() const { return startingLaw; }
	[[nodiscard]] const auto& getAiWillDo() const { return aiWillDo; }

	void setName(std::string _name) { name = std::move(_name); }
	void setIcon(int _icon) { icon = _icon; }
	void setDefaultLaw(bool _defaultLaw) { defaultLaw = _defaultLaw; }
	void setSoundEffect(std::string _soundEffect) { soundEffect = std::move(_soundEffect); }
	void setVisible(std::string _visible) { visible = std::move(_visible); }
	void setStateModifier(std::string _stateModifier) { stateModifier = std::move(_stateModifier); }
	void setSuppressedStateModifier(std::string _suppressedStateModifier)
	{
		suppressedStateModifier = std::move(_suppressedStateModifier);
	}
	void setStartingLaw(bool _startingLaw) { startingLaw = _startingLaw; }
	void setAiWillDo(std::string _aiWillDo) { aiWillDo = std::move(_aiWillDo); }

  private:
	std::string name;
	int icon = 0;
	bool defaultLaw = false;
	std::string soundEffect;
	std::optional<std::string> visible;
	std::string stateModifier;
	std::optional<std::string> suppressedStateModifier;
	bool startingLaw = false;
	std::optional<std::string> aiWillDo;
};

} // namespace HoI4



#endif // OCCUPATION_LAW_H