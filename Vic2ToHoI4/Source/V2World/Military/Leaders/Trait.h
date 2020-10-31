#ifndef TRAIT_H
#define TRAIT_H



#include <istream>
#include <string>
#include <unordered_map>



namespace Vic2
{

std::unordered_map<std::string, float> getTraitEffects(std::istream& theStream);

}



#endif // TRAIT_H