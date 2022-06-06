#ifndef HOI4_EVENT_H
#define HOI4_EVENT_H



#include "EventOption.h"
#include "external/common_items/ConvenientParser.h"
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{

class Event: commonItems::parser
{
  public:
	Event() = default;
	Event(const std::string& _type, std::istream& theStream);

	void giveType(std::string&& newType) { type = newType; }
	void giveId(std::string&& newId) { id = newId; }
	void giveTitle(std::string&& newTitle) { title = newTitle; }
	void giveDescription(std::string&& description) { descriptions.push_back(description); }
	void givePicture(std::string&& newPicture) { picture = newPicture; }
	void setMajor() { majorEvent = true; }
	void setTriggeredOnly() { triggeredOnly = true; }
	void giveTrigger(std::string&& newTrigger) { trigger = newTrigger; }
	void setFireOnlyOnce() { fireOnlyOnce = true; }
	void giveMeanTimeToHappen(std::string&& newMttH) { meanTimeToHappen = newMttH; }
	void giveImmediate(std::string&& newImmediate) { immediate = newImmediate; }
	void giveOption(EventOption&& theOption) { options.push_back(theOption); }

	void clearDescriptions() { descriptions.clear(); }
	void clearOptions() { options.clear(); }

	[[nodiscard]] const std::string& getId() const { return id; }
	[[nodiscard]] const auto& getTitle() const { return title; }

	friend std::ostream& operator<<(std::ostream& out, const Event& theEvent);

  private:
	std::string type;
	std::string id;
	std::optional<std::string> title;
	std::vector<std::string> descriptions;
	std::optional<std::string> picture;
	bool majorEvent = false;
	bool triggeredOnly = false;
	std::optional<bool> hidden;
	std::string trigger;
	std::optional<bool> fireOnlyOnce;
	std::string meanTimeToHappen;
	std::string immediate;
	std::vector<EventOption> options;
};

} // namespace HoI4



#endif // HOI4_EVENT_H