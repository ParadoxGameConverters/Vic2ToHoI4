#ifndef HOI4_STATES_DEFAULT_STATES_IMPORTER_H
#define HOI4_STATES_DEFAULT_STATES_IMPORTER_H



#include "DefaultState.h"
#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class DefaultStatesImporter: commonItems::parser
{
  public:
	DefaultStatesImporter();

	std::map<int, DefaultState> ImportDefaultStates(const std::string& hoi4Path);

  private:
	int num_ = 0;
	std::map<int, DefaultState> defaultStates_;
};

} // namespace HoI4



#endif // HOI4_STATES_DEFAULT_STATES_IMPORTER_H