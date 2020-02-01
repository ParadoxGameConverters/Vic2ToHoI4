#ifndef RESOURCES_H
#define RESOURCES_H



#include "newParser.h"
#include <map>
#include <string>



class Resources: commonItems::parser
{
	public:
		Resources() noexcept;

		[[nodiscard]] std::map<std::string, double> getResourcesInProvince(int provinceNum) const;

	private:
		std::map<int, std::map<std::string, double>> resourceMap;
};




#endif // RESOURCES_H