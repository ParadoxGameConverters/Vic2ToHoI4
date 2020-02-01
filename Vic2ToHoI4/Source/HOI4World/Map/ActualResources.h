#ifndef ACTUAL_RESOURCES_H
#define ACTUAL_RESOURCES_H



#include "newParser.h"



class ActualResources: commonItems::parser
{
	public:
		explicit ActualResources(std::istream& theStream);

		[[nodiscard]] auto takeResources() { return std::move(theResources); }

	private:
		std::map<std::string, double> theResources;
};



#endif // ACTUAL_RESOURCES_H