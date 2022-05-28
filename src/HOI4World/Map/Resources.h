#ifndef RESOURCES_H
#define RESOURCES_H



#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class Resources: commonItems::parser
{
  public:
	Resources() noexcept;

	[[nodiscard]] std::map<std::string, double> getResourcesInProvince(int provinceNum) const;

  private:
	std::map<int, std::map<std::string, double>> resourceMap;
};

} // namespace HoI4



#endif // RESOURCES_H