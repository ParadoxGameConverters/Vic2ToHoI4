#include "OutSounds.h"
#include "external/common_items/OSCompatibilityLayer.h"

#include <fstream>
#include <vector>


void HoI4::outputSounds(const std::string& outputName, const std::vector<SoundEffect>& soundEffects)
{
	std::ofstream output("output/" + outputName + "/sounds/vo_conv.asset", std::ios::app);
	if (!output.is_open())
	{
		throw std::runtime_error("Could not create output/" + outputName + "/sounds/vo_conv.asset");
	}

	output << "category = {\n";
	output << "\tname = \"Voices\"\n";
	output << "\tsoundeffects = {\n ";
	for (const auto& soundEffect: soundEffects)
	{
		output << "\t\t" << soundEffect.getName() << "\n";
	}
	output << "\t}\n";
	output << "}\n";
	output << "\n";
	output << "\n";

	for (const auto& soundEffect: soundEffects)
	{
		output << "soundeffect = {\n";
		output << "\tname = " << soundEffect.getName() << "\n";
		output << "\tsounds = {\n";
		for (const auto& sound: soundEffect.getSounds())
		{
			output << "\t\tsound = " << sound << "\n";
		}
		output << "\t}\n";
		output << "\tmax_audible = 1\n";
		output << "\tmax_audible_behaviour = fail\n";
		output << "\tvolume = 0.45\n";
		output << "\tvolume_random_offset = { 0.0 -0.15 }\n";
		output << "\tplaybackrate_random_offset = { 0.0 -0.15 }\n";
		output << "}\n";
		output << "\n";
	}
}
