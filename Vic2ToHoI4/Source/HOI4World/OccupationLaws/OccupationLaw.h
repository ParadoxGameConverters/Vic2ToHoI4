#ifndef OCCUPATION_LAW_H
#define OCCUPATION_LAW_H


#include <string>



namespace HoI4
{

class OccupationLaw
{
  public:
	class Factory;
	[[nodiscard]] const auto& getName() const { return name; }
	
	void setName(std::string _name) { name = std::move(_name); }

  private:
	std::string name;
};

} // namespace HoI4



#endif // OCCUPATION_LAW_H