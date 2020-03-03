#ifndef AIRPLANE_H
#define AIRPLANE_H



#include <fstream>
#include <string>



namespace HoI4
{

class Airplane
{
  public:
	Airplane(std::string _type, std::string _owner, const int _amount):
		 type(std::move(_type)), owner(std::move(_owner)), amount(_amount)
	{
	}

	friend std::ostream& operator<<(std::ostream& output, const Airplane& instance);

  private:
	std::string type;
	std::string owner;
	int amount;
};

} // namespace HoI4



#endif // AIRPLANE_H
