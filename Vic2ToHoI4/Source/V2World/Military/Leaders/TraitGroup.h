#ifndef TRAIT_GROUP_H
#define TRAIT_GROUP_H



#include "Parser.h"
#include "Trait.h"



namespace Vic2
{

class TraitGroup: commonItems::parser
{
  public:
	explicit TraitGroup(std::istream& theStream);

	auto&& takeTraits() { return std::move(traits); }

  private:
	std::unordered_map<std::string, TraitEffects> traits;
};

} // namespace Vic2



#endif // TRAIT_GROUP_H