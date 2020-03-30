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



#include "Color.h"
#include "ParserHelpers.h"
#include <chrono>
#include <random>
using namespace ConverterColor;



Color::Color(const red& r, const green& g, const blue& b)
: initialized(true), c({ r.Red, g.Green, b.Blue })
{}


Color::Color(std::istream& theStream)
: initialized(false), c({ 0, 0, 0 })
{
	commonItems::intList colors(theStream);

	initialized = (colors.getInts().size() >= 3);
	for (size_t i = 0; i < 3; ++i)
	{
		auto color = colors.getInts()[i];
		c[i] = color;
	}
}


void Color::RandomlyFlunctuate(const int stdDev)
{
	// All three color components will go up or down by the some amount (according to stdDev), 
	// and then each is tweaked a bit more (with a much smaller standard deviation).
	static std::mt19937 generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	const double allChange = std::normal_distribution<double>(0.0, stdDev)(generator);	// the amount the colors all change by
	std::normal_distribution<double> distribution(0.0, stdDev / 4.0);
	for (auto& component : c)	// the component under consideration
	{
		component += static_cast<int>(allChange + distribution(generator) + 0.5);
		if (component < 0)
		{
			component = 0;
		}
		else if (component > 255)
		{
			component = 255;
		}
	}
}


void Color::GetRGB(red& r, green& g, blue& b) const
{
	r.Red = c[0];
	g.Green = c[1];
	b.Blue = c[2];
}


bool Color::operator == (const Color& right) const
{
	if (
			(c[0] == right.c[0]) &&
			(c[1] == right.c[1]) &&
			(c[2] == right.c[2])
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Color::operator != (const Color& right) const
{
	if (
			(c[0] != right.c[0]) ||
			(c[1] != right.c[1]) ||
			(c[2] != right.c[2])
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Color::operator < (const Color& right) const
{
	if (
			(c[0] < right.c[0]) ||
			(c[1] < right.c[1]) ||
			(c[2] < right.c[2])
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


Color::operator bool() const
{
	return initialized;
}