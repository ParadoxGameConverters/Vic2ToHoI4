#ifndef RESOURCES_LINK_H
#define RESOURCES_LINK_H



#include "newParser.h"



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



#endif // RESOURCES_LINK_H