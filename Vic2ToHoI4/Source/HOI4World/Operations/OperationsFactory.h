#ifndef OPERATIONS_FACTORY_H
#define OPERATIONS_FACTORY_H



#include "Operations.h"
#include "Parser.h"
#include <memory>
#include <string>



namespace HoI4
{

class Operations::Factory: commonItems::parser
{
  public:
	std::unique_ptr<Operations> getOperations(const std::string& HoI4Path);
};

} // namespace HoI4



#endif // OPERATIONS_FACTORY_H