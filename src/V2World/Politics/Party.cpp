#include "Party.h"
#include "ParserHelpers.h"



bool Vic2::Party::operator==(const Party& rhs) const
{
	return name == rhs.name;
}


bool Vic2::Party::operator<(const Party& rhs) const
{
	return name < rhs.name;
}