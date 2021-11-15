#ifndef HOI4_IDEA_H
#define HOI4_IDEA_H



#include "Parser.h"



namespace HoI4
{

class Idea: commonItems::parser
{
  public:
	Idea(std::string ideaName, std::istream& theStream);

	friend std::ostream& operator<<(std::ostream& outStream, const Idea& outIdea);

	[[nodiscard]] std::string getName() const { return name; }

	void setAvailable(const std::string& newAvailable) { available = newAvailable; }
	void setAllowedCivilWar(const std::string& newAllowedCivilWar) { allowedCivilWar = newAllowedCivilWar; }
	void updateCancel(const std::string& newCancel) { cancel = newCancel; }

  private:
	std::string name;
	std::string altName;

	std::string ledger;

	std::optional<int> cost;
	std::optional<int> removalCost;
	std::optional<int> level;

	std::string allowed;
	std::string allowedCivilWar;
	std::optional<std::string> visible;
	std::string cancel;
	std::string available;
	std::string aiWillDo;
	std::string picture;
	std::string rule;
	std::string modifier;
	std::string researchBonus;
	std::string equipmentBonus;
	std::string traits;
	std::string onAdd;
	std::string allowedToRemove;

	bool isDefault = false;
	std::optional<bool> cancelIfInvalid;
};

} // namespace HoI4



#endif // HOI4_IDEA_H