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



#ifndef SHIP_VARIANTS_H
#define SHIP_VARIANTS_H



#include "newParser.h"
#include "../Technologies.h"
#include "ShipVariant.h"
#include <string>
#include <vector>



namespace HoI4
{

class shipVariants
{
	public:
		shipVariants(const std::vector<shipVariant>& possibleVariants, const technologies& ownedTechs, const std::string& countryTag);

		shipVariants() = delete;
		~shipVariants() = default;
		shipVariants(const shipVariants&) = default;
		shipVariants(shipVariants&&) = default;
		shipVariants& operator=(const shipVariants&) = default;
		shipVariants& operator=(shipVariants&&) = default;

		bool hasVariant(const std::string& variantName) const { return variants.find(variantName) != variants.end(); }

		friend std::ostream& operator << (std::ostream& output, const shipVariants& theVariants);

	private:
		std::map<std::string, shipVariant> variants;
};

}



#endif // SHIP_VARIANTS_H