#ifndef STATE_LANGUAGE_CATEGORIES_BUILDER_H
#define STATE_LANGUAGE_CATEGORIES_BUILDER_H



#include "src/V2World/States/StateLanguageCategories.h"
#include <memory>



namespace Vic2
{

class StateLanguageCategories::Builder
{
  public:
	Builder() { theCategories = std::make_unique<StateLanguageCategories>(); }
	std::unique_ptr<StateLanguageCategories> build() { return std::move(theCategories); }

	Builder& setCategories(std::map<std::string, std::string> categories)
	{
		theCategories->categories = std::move(categories);
		return *this;
	}

  private:
	std::unique_ptr<StateLanguageCategories> theCategories;
};

} // namespace Vic2



#endif // STATE_LANGUAGE_CATEGORIES_BUILDER_H