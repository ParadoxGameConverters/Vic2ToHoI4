#include "src/OutHoi4/Landmarks/OutLandmark.h"
#include "src/HOI4World/Landmarks/Landmark.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const Landmark& outLandmark)
{
	outStream << "\t" << outLandmark.name << " = {\n";

	for (const auto& [key, value]: outLandmark.properties)
	{
		outStream << "\t\t" << key << " " << value << "\n";
	}

	outStream << "\t\tcountry_modifiers = {\n";
	outStream << "\t\t\tenable_for_controllers = { ";
	for (const auto& tag: outLandmark.getEnabledControllers())
	{
		outStream << tag << " ";
	}
	outStream << "}\n";

	if (!outLandmark.getModifiers().empty())
	{
		outStream << "\t\t\tmodifiers " << outLandmark.getModifiers() << "\n";
	}
	outStream << "\t\t}\n"; 
	outStream << "\t}\n";

	return outStream;
}