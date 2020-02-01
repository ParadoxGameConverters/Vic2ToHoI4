#include "OutStrategicRegion.h"
#include "Log.h"
#include <fstream>



void HoI4StrategicRegion::output(const std::string& path) const
{
	std::ofstream out(path + filename);
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not open " << path << filename;
		exit(-1);
	}

	out << "\n";
	out << "strategic_region={\n";
	out << "\tid=" << ID << "\n";
	out << "\tname=\"" << name << "\"\n";
	out << "\tprovinces={\n";
	out << "\t\t";
	for (auto province : newProvinces)
	{
		out << province << " ";
	}
	out << "\n";
	out << "\t}\n";
	if (!staticModifiers.empty())
	{
		out << "\tstatic_modifiers={\n";
		for (const auto& modifier : staticModifiers)
		{
			out << "\t\t" << modifier.first << "=" << modifier.second << "\n";
		}
		out << "\n";
		out << "\t}\n";
	}
	if (navalTerrain)
	{
		out << "\tnaval_terrain=" << *navalTerrain << "\n";
	}
	out << "\tweather" << weather << "\n";
	out << "}";

	out.close();
}