#include "HOI4Version.h"
#include "Log.h"



HoI4::Version::Version(std::string version)
{
	size_t dot = version.find_first_of('.');
	first = stoi(version.substr(0, dot));

	version = version.substr(dot + 1, version.size());
	dot = version.find_first_of('.');
	second = stoi(version.substr(0, dot));

	version = version.substr(dot + 1, version.size());
	dot = version.find_first_of('.');
	third = stoi(version.substr(0, dot));
}


bool HoI4::Version::operator >= (const HoI4::Version& rhs) const
{
	if (first > rhs.first)
	{
		return true;
	}
	else if ((first == rhs.first) && (second > rhs.second))
	{
		return true;
	}
	else if ((first == rhs.first) && (second == rhs.second) && (third > rhs.third))
	{
		return true;
	}
	else if ((first == rhs.first) && (second == rhs.second) && (third == rhs.third))
	{
		return true;
	}
	else
	{
		return false;
	}
}