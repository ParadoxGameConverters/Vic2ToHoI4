#ifndef HOI4_DIVISION_TYPE_H
#define HOI4_DIVISION_TYPE_H



#include <ostream>
#include <string>



namespace HoI4
{

class DivisionType
{
  public:
	DivisionType(std::string _name,
		 std::string _type,
		 const int _location,
		 const double _experience,
		 double _startEquipment):
		 name(std::move(_name)),
		 type(std::move(_type)), location(_location), experience(_experience), startEquipment(_startEquipment)
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const DivisionType&);

  private:
	std::string name;
	std::string type;
	int location = 0;
	double experience = 0.0;
	double startEquipment = 0.7;
};

} // namespace HoI4



#endif // HOI4_DIVISION_TYPE_H