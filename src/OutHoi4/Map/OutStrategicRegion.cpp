#include "src/OutHoi4/Map/OutStrategicRegion.h"
#include <fstream>



void HoI4::outputStrategicRegion(const StrategicRegion& strategicRegion, const std::string& path)
{
	std::ofstream out(path + strategicRegion.getFilename());
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + path + strategicRegion.getFilename());
	}

	out << "\n";
	out << "strategic_region={\n";
	out << "\tid=" << strategicRegion.getID() << "\n";
	out << "\tname=\"" << strategicRegion.getName() << "\"\n";
	out << "\tprovinces={\n";
	out << "\t\t";
	for (const auto& province: strategicRegion.getNewProvinces())
	{
		out << province << " ";
	}
	out << "\n";
	out << "\t}\n";
	if (strategicRegion.hasStaticModifiers())
	{
		out << "\tstatic_modifiers={\n";
		for (const auto& modifier: strategicRegion.getStaticModifiers())
		{
			out << "\t\t" << modifier.first << "=" << modifier.second << "\n";
		}
		out << "\n";
		out << "\t}\n";
	}
	auto navalTerrain = strategicRegion.getNavalTerrain();
	if (navalTerrain)
	{
		out << "\tnaval_terrain=" << *navalTerrain << "\n";
	}
	out << "\tweather" << strategicRegion.getWeather() << "\n";
	out << "}";

	out.close();
}