#ifndef HOI4_MODIFIER_H
#define HOI4_MODIFIER_H



#include "Parser.h"
#include <string>
#include <vector>

namespace HoI4
{

class Modifier: commonItems::parser
{
  public:
	Modifier(const std::string& modifierName, std::istream& theStream);

	friend std::ostream& operator<<(std::ostream& output, const Modifier& modifier);

	std::string getName() const { return name; }
	std::string getIcon() const { return icon; }
	std::string getEnable() const { return enable; }
	std::string getRemoveTrigger() const { return removeTrigger; }
	std::map<std::string, std::string> getEffects() const { return effects; }

	void updateEnable(std::string newEnable) { enable = std::move(newEnable); }
	void updateRemoveTrigger(std::string newTrigger) { removeTrigger = std::move(newTrigger); }
	void addEffect(std::string modifier, std::string value) { effects.insert(std::move(make_pair(modifier, value))); }

  private:
	std::string name;
	std::string icon;
	std::string enable;
	std::string removeTrigger;
	std::map<std::string, std::string> effects;
};

} // namespace HoI4

#endif // HOI4_MODIFIER_H