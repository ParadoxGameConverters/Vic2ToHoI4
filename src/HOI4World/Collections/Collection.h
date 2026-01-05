#ifndef COLLECTION_H
#define COLLECTION_H



#include "external/common_items/ConvenientParser.h"
#include <string>



namespace HoI4
{

class Collection: commonItems::parser
{
  public:
	Collection(const std::string& id, std::istream& theStream);

	[[nodiscard]] const auto& getId() const { return id; }
	[[nodiscard]] const auto& getInput() const { return input; }
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getOperators() const { return operators; }

	void setInput(const std::string& newValue) { input = newValue; }
	void setName(const std::string& newValue) { name = newValue; }
	void setOperators(const std::string& newValue) { operators = newValue; }

	bool operator==(const Collection& other) const;
	friend std::ostream& operator<<(std::ostream& out, const Collection& theGoal);

  private:
	std::string id;
	std::string input = "game:scope";
	std::string name = "COLLECTION_DEFAULT";
	std::string operators = "= {}";
};

} // namespace HoI4



#endif // COLLECTION_H