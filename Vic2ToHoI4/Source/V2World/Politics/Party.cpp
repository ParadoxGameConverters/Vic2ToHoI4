#include "Party.h"
#include "ParserHelpers.h"



bool Vic2::operator==(const Vic2::Party& one, const Vic2::Party& other)
{
	return one.getName() == other.getName();
}


bool Vic2::operator<(const Vic2::Party& one, const Vic2::Party& other)
{
	return one.getName() < other.getName();
}