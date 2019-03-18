/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#ifndef ALL_MILITARY_MAPPINGS
#define ALL_MILITARY_MAPPINGS



#include "MilitaryMappings.h"
#include "newParser.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{


class allMilitaryMappings: commonItems::parser
{
	public:
		allMilitaryMappings(std::istream& theStream);
		~allMilitaryMappings() = default;
		allMilitaryMappings(const allMilitaryMappings&) = default;
		allMilitaryMappings(allMilitaryMappings&&) = default;
		allMilitaryMappings& operator=(const allMilitaryMappings&) = default;
		allMilitaryMappings& operator=(allMilitaryMappings&&) = default;


		militaryMappings getMilitaryMappings(const std::vector<std::string>& mods) const;

	private:
		std::map<std::string, militaryMappings> theMappings;
};


class militaryMappingsFile: commonItems::parser
{
	public:
		militaryMappingsFile();
		~militaryMappingsFile() = default;
		militaryMappingsFile(const militaryMappingsFile&) = default;
		militaryMappingsFile(militaryMappingsFile&&) = default;
		militaryMappingsFile& operator=(const militaryMappingsFile&) = default;
		militaryMappingsFile& operator=(militaryMappingsFile&&) = default;

		auto takeAllMilitaryMappings() { return std::move(theMilitaryMappings); }

	private:
		std::unique_ptr<allMilitaryMappings> theMilitaryMappings;
};


}



#endif // ALL_MILITARY_MAPPINGS