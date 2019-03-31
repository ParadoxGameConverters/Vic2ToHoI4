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



#ifndef SHIP_VARIANT_H
#define SHIP_VARIANT_H



#include "newParser.h"
#include "ShipModules.h"
#include "../Technologies.h"
#include <memory>
#include <set>
#include <string>



namespace HoI4
{
	
class shipVariant: commonItems::parser
{
	public:
		shipVariant(std::istream& theStream);

		shipVariant() = delete;
		~shipVariant() = default;
		shipVariant(const shipVariant& source);
		shipVariant(shipVariant&&) = default;
		shipVariant& operator=(const shipVariant&) = default;
		shipVariant& operator=(shipVariant&&) = default;

		void setOwningCountryTag(const std::string& tag);

		bool isValidVariant(const technologies& ownedTechs) const;

		friend std::ostream& operator << (std::ostream& output, shipVariant& theVariant);

	private:
		std::string name;
		std::string type;
		std::string owningCountryTag;
		std::string nameGroup;
		std::unique_ptr<shipModules> modules;
		bool obsolete = false;

		std::string ownerTag;

		std::set<std::string> requiredTechnologies;
		std::set<std::string> blockingTechnologies;
};

}



#endif // SHIP_VARIANT_H