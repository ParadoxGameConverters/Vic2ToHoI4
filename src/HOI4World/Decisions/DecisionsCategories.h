#ifndef DECISIONS_CATEGORIES_H
#define DECISIONS_CATEGORIES_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Decisions/DecisionsCategory.h"
#include <string>



namespace HoI4
{

class DecisionsCategories
{
  public:
	class Factory;
	DecisionsCategories(std::vector<DecisionsCategory> _theCategories): theCategories(std::move(_theCategories)) {}

	[[nodiscard]] const auto& getTheCategories() const { return theCategories; }

	void addCategory(const DecisionsCategory& newCategory) { theCategories.emplace_back(newCategory); }
	void replaceCategory(const DecisionsCategory& newCategory)
	{
		std::replace(theCategories.begin(), theCategories.end(), newCategory, newCategory);
	}

  private:
	std::vector<DecisionsCategory> theCategories;
};


class DecisionsCategories::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<DecisionsCategories> getDecisionsCategories();
	std::unique_ptr<DecisionsCategories> getDecisionsCategories(std::istream& theStream);
	std::unique_ptr<DecisionsCategories> getDecisionsCategories(const std::filesystem::path& filename);

  private:
	std::vector<DecisionsCategory> theCategories;
	DecisionsCategory::Factory DecisionsCategoryFactory;
};

} // namespace HoI4



#endif // DECISIONS_CATEGORIES_H