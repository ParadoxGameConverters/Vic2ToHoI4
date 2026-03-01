#ifndef STATE_CATEGORY_H
#define STATE_CATEGORY_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class StateCategory: commonItems::parser
{
  public:
	explicit StateCategory(std::string name, std::istream& theStream);
	StateCategory() = default;

	const auto& getName() const { return name_; }
	auto getNumberOfSlots() const { return numberOfSlots; }
	int getBuildingMaxLevel(const std::string& building) const;

	void setName(const std::string& name) { name_ = name; }
	void setNumberOfSlots(int level) { numberOfSlots = level; }
	void setBuildingsMaxLevel(const std::string& building, int level) { buildingsMaxLevels.emplace(building, level); }

  private:
	std::string name_ = "wasteland";
	int numberOfSlots = 0;
	std::map<std::string, int> buildingsMaxLevels;
};

} // namespace HoI4



#endif // STATE_CATEGORY_H
