#ifndef OPERATION_H
#define OPERATION_H



#include <string>



namespace HoI4
{

class Operation
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }

  private:
	std::string name;
};

} // namespace HoI4



#endif // OPERATION_H