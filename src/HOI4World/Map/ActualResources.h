#ifndef ACTUAL_RESOURCES_H
#define ACTUAL_RESOURCES_H



#include "Parser.h"



namespace HoI4
{

class ActualResources: commonItems::parser
{
  public:
	explicit ActualResources(std::istream& theStream);

	[[nodiscard]] auto takeResources() { return std::move(theResources); }

  private:
	std::map<std::string, double> theResources;
};

} // namespace HoI4



#endif // ACTUAL_RESOURCES_H