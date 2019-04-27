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



#include "ShipVariants.h"


HoI4::shipVariants::shipVariants(const std::vector<shipVariant>& possibleVariants, const technologies& ownedTechs, const std::string& countryTag)
{
	for (auto &possibleVariant: possibleVariants)
	{
		if (possibleVariant.isValidVariant(ownedTechs))
		{
			shipVariant newVariant(possibleVariant);
			newVariant.setOwningCountryTag(countryTag);
			variants.insert(make_pair(newVariant.getName(), newVariant));
		}
	}
}


std::ostream& HoI4::operator<<(std::ostream& output, const HoI4::shipVariants& theVariants)
{
	output << "### VARIANTS ###\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	for (auto variant: theVariants.variants)
	{
		output << variant.second;
	}
	output << "}\n";

	return output;
}