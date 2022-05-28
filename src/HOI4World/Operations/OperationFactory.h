#ifndef OPERATION_FACTOR_H
#define OPERATION_FACTOR_H



#include "Operation.h"
#include "Parser.h"
#include <memory>



namespace HoI4
{

class Operation::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Operation> getOperation(std::string name, std::istream& theStream);

  private:
	std::unique_ptr<Operation> operation;
};

} // namespace HoI4



#endif // OPERATION_FACTOR_H