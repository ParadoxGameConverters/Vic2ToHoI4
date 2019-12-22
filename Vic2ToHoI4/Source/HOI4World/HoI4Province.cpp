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



#include "HoI4Province.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <sstream>
#include <algorithm>
#include <stdio.h>
using namespace std;



HoI4Province::HoI4Province(const std::string& Owner, int State):
	filenames(),
	coastal(false),
	num(0),
	name(""),
	owner(Owner),
	cores(),
	is_land(false),
	points(0),
	metal(0.0),
	energy(0.0),
	oil(0.0),
	rare_materials(0.0),
	manpower(0.0),
	leadership(0.0),
	rawIndustry(0.0),
	state(State),
	naval_base(0),
	air_base(0),
	industry(0),
	infrastructure(0)
{
}


void HoI4Province::output() const
{
	for (auto filename: filenames)
	{
		FILE* output;
		if (fopen_s(&output, ("output/" + theConfiguration.getOutputName() + "/history/provinces/" + filename.first).c_str(), "w") != 0)
		{
			LOG(LogLevel::Error) << "Could not create province history file output/" << theConfiguration.getOutputName() << "/history/provinces/" << filename.first << " - " << Utils::GetLastErrorString();
			exit(-1);
		}
		if (!owner.empty())
		{
			fprintf_s(output, "owner = %s\n", owner.c_str());
			fprintf_s(output, "controller = %s\n", owner.c_str());
		}
		for (auto core: cores)
		{
			fprintf_s(output, "add_core = %s\n", core.c_str());
		}
		if ((points > 0) || industry > 0)
		{
			fprintf_s(output, "points = %i\n", points + (industry / 2));
		}
		if (metal > 0.0)
		{
			fprintf_s(output, "metal = %.2f\n", metal);
		}
		if (energy > 0.0)
		{
			fprintf_s(output, "energy = %.2f\n", energy);
		}
		if (rare_materials > 0.0)
		{
			fprintf_s(output, "rare_materials = %.2f\n", rare_materials);
		}
		if (oil > 0.0)
		{
			fprintf_s(output, "crude_oil = %.2f\n", oil);
		}
		if (industry > 0)
		{
			fprintf_s(output, "industry = %i\n", industry);
		}
		if (infrastructure > 0)
		{
			fprintf_s(output, "infra = %i\n", infrastructure);
		}
		if (naval_base > 0)
		{
			fprintf_s(output, "naval_base = %i\n", naval_base);
		}
		if (air_base > 0)
		{
			fprintf_s(output, "air_base = %i\n", air_base);
		}
		if (manpower > 0.0)
		{
			fprintf_s(output, "manpower = %.2f\n", manpower);
		}
		if (leadership > 0.0)
		{
			fprintf_s(output, "leadership = %.2f\n", leadership);
		}
		fclose(output);
	}
}


void HoI4Province::convertFromOldProvince(const Vic2::Province* oldProvince)
{
}


void HoI4Province::addCore(const string& newCore)
{
	// only add if unique
	if ( find(cores.begin(), cores.end(), newCore) == cores.end() )
	{
		cores.push_back(newCore);
	}
}


void HoI4Province::addFilename(const string& _filename)
{
	// only add if unique
	if (filenames.find(_filename) == filenames.end())
	{
		filenames.insert(make_pair(_filename, _filename));
	}
}


void HoI4Province::requireNavalBase(int _min)
{
	if (coastal)
	{
		naval_base = max(naval_base, _min);
	}
}

void HoI4Province::requireAirBase(int _min)
{
	air_base = max(air_base, _min);
}

void HoI4Province::requireIndustry(int _min)
{
	industry = max(industry, _min);
}


void HoI4Province::requireInfrastructure(int _min)
{
	infrastructure = max(infrastructure, _min);
}
