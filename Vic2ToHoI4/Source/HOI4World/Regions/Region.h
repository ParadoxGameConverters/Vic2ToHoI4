#ifndef REGION_H
#define REGION_H



#include <string>
#include <vector>



namespace HoI4
{

class Region
{
  public:
	class Factory;
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getProvinces() const { return provinces; }

  private:
	std::string name;
	std::vector<int> provinces;
};

} // namespace HoI4



#endif // REGION_H