#ifndef RESOURCES_LINK_H
#define RESOURCES_LINK_H



#include "Parser.h"



namespace HoI4
{

class ResourcesLink: commonItems::parser
{
  public:
	explicit ResourcesLink(std::istream& theStream);

	[[nodiscard]] int getProvinceNum() const { return provinceNum; }
	[[nodiscard]] auto takeResources() { return std::move(theResources); }

  private:
	int provinceNum = 0;
	std::map<std::string, double> theResources;
};

} // namespace HoI4



#endif // RESOURCES_LINK_H