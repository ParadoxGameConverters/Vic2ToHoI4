#ifndef HOI4_FOCUS_H
#define HOI4_FOCUS_H



#include "Parser.h"
#include <string>
#include <vector>



namespace HoI4
{
class Localisation;
}



class HoI4Focus: commonItems::parser
{
  public:
	HoI4Focus() = default;
	explicit HoI4Focus(std::istream& theStream);
	HoI4Focus(const HoI4Focus&) = default;

	friend std::ostream& operator<<(std::ostream& output, const HoI4Focus& focus);

	std::shared_ptr<HoI4Focus> makeCustomizedCopy(const std::string& country) const;
	std::shared_ptr<HoI4Focus> makeTargetedCopy(const std::string& country,
		 const std::string& target,
		 HoI4::Localisation& localisation) const;

	std::string id;
	std::string icon;
	std::string text;
	std::vector<std::string> prerequisites;
	std::string mutuallyExclusive;
	std::string bypass;
	int xPos = 0;
	int yPos = 0;
	std::string relativePositionId;
	int cost = 0;
	bool availableIfCapitulated = false;
	std::string available;
	std::string cancelIfInvalid;
	std::string continueIfInvalid;
	std::string completeTooltip;
	std::string completionReward;
	std::string aiWillDo;

  private:
	HoI4Focus& operator=(const HoI4Focus&) = delete;

	void customizeMutualExclusion(std::shared_ptr<HoI4Focus> newFocus, const std::string& country) const;
	void customizePrerequisite(std::shared_ptr<HoI4Focus> newFocus,
		 std::string& prerequisite,
		 const std::string& country) const;
};



#endif // HOI4_FOCUS_H