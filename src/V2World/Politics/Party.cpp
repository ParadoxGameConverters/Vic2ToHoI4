#include "Party.h"
#include "external/common_items/ParserHelpers.h"



bool Vic2::Party::operator==(const Party& rhs) const
{
	return name == rhs.name;
}


bool Vic2::Party::operator<(const Party& rhs) const
{
	return name < rhs.name;
}