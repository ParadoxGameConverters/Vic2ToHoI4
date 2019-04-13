/*Copyright (c) 2018 The Paradox Game Converters Project

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



#include "HoI4Navy.h"



HoI4::Navy::Navy(const std::string& _name, int _location, int _base):
	name(_name),
	location(_location),
	base(_base)
{}


std::ostream& HoI4::operator << (std::ostream& output, const HoI4::Navy& instance)
{
	output << "\tfleet = {\n";
	output << "\t\tname = \"" << instance.name << "\"\n";
	output << "\t\tnaval_base = " << instance.base << "\n";
	output << "\t\ttask_force = {\n";
	output << "\t\t\tname = \"" << instance.name << "\"\n";
	output << "\t\t\tlocation = " << instance.location << "\n";
	for (auto& ship: instance.ships)
	{
		output << ship;
	}
	output << "\t\t}\n";
	output << "\t}\n";

	return output;
}