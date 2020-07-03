#ifndef OPERATIONS_H
#define OPERATIONS_H



#include "Operation.h"
#include <set>
#include <vector>



namespace HoI4
{

class Operations
{
  public:
	class Factory;
	[[nodiscard]] const auto& getOperations() const { return operations; }

	void updateOperations(const std::set<std::string>& majorIdeologies);

  private:
	static void updateOperationCoupGovernment(Operation& operation, const std::set<std::string>& majorIdeologies);

	std::vector<Operation> operations;
};

} // namespace HoI4



#endif // OPERATIONS_H