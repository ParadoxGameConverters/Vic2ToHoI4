#ifndef OPERATIONS_H
#define OPERATIONS_H



#include "Operation.h"
#include <vector>



namespace HoI4
{

class Operations
{
  public:
	class Factory;
	[[nodiscard]] const auto& getOperations() const { return operations; }

  private:
	std::vector<Operation> operations;
};

} // namespace HoI4



#endif // OPERATIONS_H