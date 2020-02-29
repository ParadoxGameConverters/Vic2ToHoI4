#ifndef HOI4_IDEA_H
#define HOI4_IDEA_H


#include "newParser.h"



namespace HoI4
{

class Idea: commonItems::parser
{
	public:
		Idea(const std::string& ideaName, std::istream& theStream);

		friend std::ostream& operator<<(std::ostream& outStream, const HoI4::Idea& outIdea);

		std::string getName() const { return name; }

		void setAvailable(const std::string& newAvailable) { available = newAvailable; }
		void setAllowedCivilWar(const std::string& newAllowedCivilWar) { allowedCivilWar = newAllowedCivilWar; }

	private:
		std::string name;
		std::string altName;

		std::optional<int> cost;
		std::optional<int> removalCost;
		std::optional<int> level;

		std::string allowed;
		std::string allowedCivilWar;
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

std::ostream& operator<<(std::ostream& outStream, const HoI4::Idea& outIdea);

}



#endif // HOI4_IDEA_H