#include "OutIdeas.h"
#include "HOI4World/Ideas/IdeaGroup.h"
#include "HOI4World/Ideas/Ideas.h"
#include <fstream>



void outputIdeologicalIdeas(const std::map<std::string, HoI4::IdeaGroup>& ideologicalIdeas,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName);
void outputGeneralIdeas(const std::vector<HoI4::IdeaGroup>& generalIdeas, const std::string& outputName);
void outputMonarchIdeas(std::map<std::string, std::shared_ptr<HoI4::Country>> countries, const std::string& outputName);
void HoI4::outIdeas(const Ideas& ideas,
	 const std::set<std::string>& majorIdeologies,
	 std::map<std::string, std::shared_ptr<HoI4::Country>> countries,
	 const std::string& outputName)
{
	outputIdeologicalIdeas(ideas.getIdeologicalIdeas(), majorIdeologies, outputName);
	outputGeneralIdeas(ideas.getGeneralIdeas(), outputName);
	outputMonarchIdeas(countries, outputName);
}


void outputIdeologicalIdeas(const std::map<std::string, HoI4::IdeaGroup>& ideologicalIdeas,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName)
{
	std::ofstream ideasFile("output/" + outputName + "/common/ideas/convertedIdeas.txt");
	ideasFile << "ideas = {\n";
	ideasFile << "\tcountry = {\n";
	for (const auto& majorIdeology: majorIdeologies)
	{
		auto ideologicalIdea = ideologicalIdeas.find(majorIdeology);
		if (ideologicalIdea != ideologicalIdeas.end())
		{
			for (const auto& idea: ideologicalIdea->second.getIdeas())
			{
				ideasFile << idea;
				ideasFile << "\n";
			}
		}
	}
	ideasFile << "\t}\n";
	ideasFile << "}";
	ideasFile.close();
}


std::ofstream openIdeaFile(const std::string& fileName);
void closeIdeaFile(std::ofstream& fileStream);
void outputGeneralIdeas(const std::vector<HoI4::IdeaGroup>& generalIdeas, const std::string& outputName)
{
	auto manpowerFile = openIdeaFile("output/" + outputName + "/common/ideas/_manpower.txt");
	auto economicFile = openIdeaFile("output/" + outputName + "/common/ideas/_economic.txt");
	auto genericFile = openIdeaFile("output/" + outputName + "/common/ideas/zzz_generic.txt");

	for (const auto& theGroup: generalIdeas)
	{
		if (theGroup.getName() == "mobilization_laws")
		{
			manpowerFile << theGroup;
		}
		else if ((theGroup.getName() == "economy") || (theGroup.getName() == "trade_laws"))
		{
			economicFile << theGroup;
		}
		else
		{
			genericFile << theGroup;
		}
	}

	closeIdeaFile(manpowerFile);
	closeIdeaFile(economicFile);
	closeIdeaFile(genericFile);
}


std::ofstream openIdeaFile(const std::string& fileName)
{
	std::ofstream theFile(fileName);
	theFile << "ideas = {\n";
	return theFile;
}


void closeIdeaFile(std::ofstream& fileStream)
{
	fileStream << "}";
	fileStream.close();
}


void outputMonarchIdeas(std::map<std::string, std::shared_ptr<HoI4::Country>> countries, const std::string& outputName)
{
	std::ofstream monarchFile("output/" + outputName + "/common/ideas/_monarchs.txt");

	monarchFile << "ideas = {\n";
	monarchFile << "\tcountry = {\n";

	for (const auto& [tag, country]: countries)
	{
		if (!country->hasMonarchIdea())
		{
			continue;
		}

		monarchFile << "\t\t" << tag << "_monarch = {\n";
		monarchFile << "\t\t\tallowed = {\n";
		monarchFile << "\t\t\t\toriginal_tag = " << tag << "\n";
		monarchFile << "\t\t\t}\n";
		monarchFile << "\n";
		monarchFile << "\t\t\tallowed_civil_war = {\n";
		monarchFile << "\t\t\t\toriginal_tag = " << tag << "\n";
		monarchFile << "\t\t\t\thas_government = " << country->getGovernmentIdeology() << "\n";
		monarchFile << "\t\t\t}\n";
		monarchFile << "\n";
		monarchFile << "\t\t\tremoval_cost = -1\n";
		monarchFile << "\n";
		monarchFile << "\t\t\ttraits = { popular_figurehead }\n";
		monarchFile << "\t\t}\n";
	}

	monarchFile << "\t}\n";
	monarchFile << "}";

	monarchFile.close();
}
