#ifndef STATE_LANGUAGE_CATEGORIES_FACTORY_H
#define STATE_LANGUAGE_CATEGORIES_FACTORY_H



#include "Parser.h"
#include "StateLanguageCategories.h"
#include <memory>



namespace Vic2
{

class StateLanguageCategories::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<StateLanguageCategories> getCategories();

  private:
	std::unique_ptr<StateLanguageCategories> theCategories;
};

} // namespace Vic2



#endif // STATE_LANGUAGE_CATEGORIES_FACTORY_H