#ifndef CASUS_BELLI_H
#define CASUS_BELLI_H



#include <string>
#include <unordered_set>



namespace Mappers
{

struct CasusBelliMapping
{
	std::unordered_set<std::string> cbs_;
	std::string warGoal_;
};

} // namespace Mappers



#endif // CASUS_BELLI_H