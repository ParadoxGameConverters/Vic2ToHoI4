#ifndef HOI4_IDEOLOGY_FILE
#define HOI4_IDEOLOGY_FILE


#include "newParser.h"
#include <map>
#include <string>



class HoI4Ideology;



namespace HoI4
{

class IdeologyFile: commonItems::parser
{
	public:
		explicit IdeologyFile(std::istream& theStream);

		auto getIdeologies() const { return ideologies; }

	private:
		std::map<std::string, HoI4Ideology*> ideologies;
};

}



#endif // HOI4_IDEOLOGY_FILE