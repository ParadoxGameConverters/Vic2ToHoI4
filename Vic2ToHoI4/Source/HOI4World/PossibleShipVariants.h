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



#ifndef POSSIBLE_SHIP_VARIANTS_H
#define POSSIBLE_SHIP_VARIANTS_H



#include "newParser.h"
#include "ShipVariant.h"
#include <vector>



namespace HoI4
{

class possibleShipVariants: commonItems::parser
{
	public:
		possibleShipVariants(std::istream& theStream);

		possibleShipVariants() = delete;
		~possibleShipVariants() = default;
		possibleShipVariants(const possibleShipVariants&) = default;
		possibleShipVariants(possibleShipVariants&&) = default;
		possibleShipVariants& operator=(const possibleShipVariants&) = default;
		possibleShipVariants& operator=(possibleShipVariants&&) = default;

		auto getPossibleVariants() const { return theVariants; }

	private:
		std::vector<shipVariant> theVariants;
};

}



#endif // POSSIBLE_SHIP_VARIANTS_H