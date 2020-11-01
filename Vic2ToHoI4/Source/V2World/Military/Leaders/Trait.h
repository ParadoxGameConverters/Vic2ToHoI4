#ifndef TRAIT_H
#define TRAIT_H



#include <istream>
#include <string>
#include <unordered_map>



namespace Vic2
{

using TraitEffects = std::unordered_map<std::string, float>;

TraitEffects getTraitEffects(std::istream& theStream);

} // namespace Vic2



#endif // TRAIT_H