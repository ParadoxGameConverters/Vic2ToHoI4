#ifndef EVENT_OPTION_H
#define EVENT_OPTION_H


#include "external/common_items/ConvenientParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class EventOption: commonItems::parser
{
  public:
	EventOption() = default;
	explicit EventOption(std::istream& theStream);

	void giveName(std::string&& newName) { name = newName; }
	void giveTrigger(std::string&& newTrigger) { trigger = newTrigger; }
	void giveAiChance(std::string&& newChance) { aiChance = newChance; }
	void giveScriptBlock(std::string&& scriptBlock) { scriptBlocks.push_back(scriptBlock); }
	void giveHiddenEffect(std::string&& effect) { hiddenEffect = effect; }

	friend std::ostream& operator<<(std::ostream& out, const EventOption& theOption);

  private:
	std::string name;
	std::string trigger;
	std::string aiChance;
	std::vector<std::string> scriptBlocks;
	std::string hiddenEffect;
};

} // namespace HoI4



#endif // EVENT_OPTION_H