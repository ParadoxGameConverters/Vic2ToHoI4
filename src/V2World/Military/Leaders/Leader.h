#ifndef VIC2_LEADER_H_
#define VIC2_LEADER_H_



#include "Trait.h"
#include <string>



namespace Vic2
{

class Leader
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getPrestige() const { return prestige; }

	[[nodiscard]] float getTraitEffectValue(const std::string& trait) const;

  private:
	std::string name;
	std::string type;
	TraitEffects traitEffects;
	double prestige = 0.0;
};

} // namespace Vic2



#endif // VIC2_LEADER_H_