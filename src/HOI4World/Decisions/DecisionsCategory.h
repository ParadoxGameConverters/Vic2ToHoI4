#ifndef DECISIONS_CATEGORY_H
#define DECISIONS_CATEGORY_H


#include "Parser.h"
#include <string>



namespace HoI4
{

class DecisionsCategory
{
  public:
	class Factory;
	DecisionsCategory(std::string name,
		 std::string icon,
		 std::string picture,
		 std::optional<int> priority,
		 std::string allowed,
		 std::string visible,
		 std::string visibilityType,
		 std::vector<std::pair<std::string, std::string>> extraItems):
		 name(std::move(name)),
		 icon(std::move(icon)), picture(std::move(picture)), priority(priority), allowed(std::move(allowed)),
		 visible(std::move(visible)), visibilityType(std::move(visibilityType)), extraItems(std::move(extraItems))
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const DecisionsCategory& decisionsCategory);
	bool operator==(const DecisionsCategory& rhs) const { return name == rhs.name; }

  private:
	std::string name;
	std::string icon;
	std::string picture;
	std::optional<int> priority;
	std::string allowed;
	std::string visible;
	std::string visibilityType;
	std::vector<std::pair<std::string, std::string>> extraItems;
};


class DecisionsCategory::Factory: commonItems::parser
{
  public:
	DecisionsCategory getDecisionsCategory(const std::string& name, std::istream& theStream);
};

} // namespace HoI4



#endif // DECISIONS_CATEGORY_H