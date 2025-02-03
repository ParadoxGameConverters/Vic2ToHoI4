#include "src/OutHoi4/Interface/OutMonarchsInterface.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>



void HoI4::outMonarchInterface(const std::filesystem::path& outputFolder,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{

	std::filesystem::create_directories("output" / outputFolder / "interface");
	std::ofstream monarchsFile("output" / outputFolder / "interface/monarchs.gfx");

	monarchsFile << "spriteTypes = {\n";

	for (const auto& [tag, country]: countries)
	{
		monarchsFile << "\tspriteType = {\n";
		monarchsFile << "\t\tname = \"GFX_idea_" << tag << "_monarch\"\n";
		monarchsFile << "\t\ttexturefile = \"" << country->getMonarchIdeaTexture() << "\"\n";
		monarchsFile << "\t}\n";
	}

	monarchsFile << "}\n ";

	monarchsFile.close();
}
