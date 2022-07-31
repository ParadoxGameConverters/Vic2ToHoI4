#ifndef SRC_V2WORLD_CULTURE_CULTURE_H_
#define SRC_V2WORLD_CULTURE_CULTURE_H_



#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

struct CultureGroup
{
	std::vector<std::string> cultures;
	std::optional<std::string> union_tag;
};

} // namespace Vic2



#endif // SRC_V2WORLD_CULTURE_CULTURE_H_