#ifndef VIC2_LEADER_H_
#define VIC2_LEADER_H_



#include <string>



namespace Vic2
{

class Leader
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getPersonality() const { return personality; }
	[[nodiscard]] const auto& getBackground() const { return background; }
	[[nodiscard]] const auto& getPrestige() const { return prestige; }

  private:
	std::string name;
	std::string type;
	std::string personality;
	std::string background;
	double prestige = 0.0;
};

} // namespace Vic2



#endif // VIC2_LEADER_H_