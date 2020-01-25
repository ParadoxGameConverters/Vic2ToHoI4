#include "../Configuration.h"
#include "HoI4StrategicRegion.h"
#include "Log.h"
#include "newParser.h"
#include "ParserHelpers.h"
#include <fstream>



class region: commonItems::parser
{
	public:
		explicit region(std::istream& theStream);

		auto getID() const { return ID; }
		auto getName() const { return name; }
		auto getStaticModifiers() const { return staticModifiers; }
		auto getProvinces() const { return provinces; }
		auto getNavalTerrain() const { return navalTerrain; }
		auto getWeather() const { return weather; }

	private:
		int ID = 0;
		std::string name;
		std::vector<int> provinces;
		std::map<std::string, std::string> staticModifiers;
		std::optional<std::string> navalTerrain;
		std::string weather;
};


region::region(std::istream& theStream)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt idString(theStream);
		ID = idString.getInt();
	});
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("provinces", [this](const std::string& unused, std::istream& theStream){
		commonItems::intList provinceInts(theStream);
		provinces = provinceInts.getInts();
	});
	registerKeyword("static_modifiers", [this](const std::string& unused, std::istream& theStream) {
		commonItems::assignments staticModifierStrings(theStream);
		staticModifiers = staticModifierStrings.getAssignments();
	});
	registerKeyword("naval_terrain", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString terrainString(theStream);
		navalTerrain = terrainString.getString();
	});
	registerKeyword("weather", [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem weatherString(theStream);
		weather = weatherString.getString();
	});
	//registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


HoI4StrategicRegion::HoI4StrategicRegion(const std::string& _filename):
	filename(_filename)
{
	registerKeyword(std::regex("strategic_region"), [this](const std::string& unused, std::istream& theStream){
		region theRegion(theStream);
		ID = theRegion.getID();
		name = theRegion.getName();
		oldProvinces = theRegion.getProvinces();
		navalTerrain = theRegion.getNavalTerrain();
		staticModifiers = theRegion.getStaticModifiers();
		weather = theRegion.getWeather();
	});

	parseFile(theConfiguration.getHoI4Path() + "/map/strategicregions/" + _filename);
	clearRegisteredKeywords();
}


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
	for (auto province: newProvinces)
	{
		out << province << " ";
	}
	out << "\n";
	out << "\t}\n";
	if (!staticModifiers.empty())
	{
		out << "\tstatic_modifiers={\n";
		for (const auto& modifier: staticModifiers)
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