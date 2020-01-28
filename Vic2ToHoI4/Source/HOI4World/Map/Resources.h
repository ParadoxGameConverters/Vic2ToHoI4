#ifndef RESOURCES_H
#define RESOURCES_H



#include "newParser.h"
#include <map>
#include <string>


class resources: commonItems::parser
{
	public:
		resources() noexcept;

		std::map<std::string, double> getResourcesInProvince(int provinceNum);

	private:
		std::map<int, std::map<std::string, double>> resourceMap;
};




#endif // RESOURCES_H