#include "OutIdeas.h"
#include "../../HOI4World/Ideas/IdeaGroup.h"
#include "../../HOI4World/Ideas/Ideas.h"
#include <algorithm>
#include <fstream>



void outputIdeologicalIdeas(const std::map<std::string, HoI4::IdeaGroup>& ideologicalIdeas,
	 const std::set<std::string>& majorIdeologies,
	 const Configuration& theConfiguration);
void outputGeneralIdeas(const std::vector<HoI4::IdeaGroup>& generalIdeas, const Configuration& theConfiguration);
void HoI4::outIdeas(const Ideas& ideas,
	 const std::set<std::string>& majorIdeologies,
	 const Configuration& theConfiguration)
{
	outputIdeologicalIdeas(ideas.getIdeologicalIdeas(), majorIdeologies, theConfiguration);
	outputGeneralIdeas(ideas.getGeneralIdeas(), theConfiguration);
}


void outputIdeologicalIdeas(const std::map<std::string, HoI4::IdeaGroup>& ideologicalIdeas,
	 const std::set<std::string>& majorIdeologies,
	 const Configuration& theConfiguration)
{
	std::ofstream ideasFile("output/" + theConfiguration.getOutputName() + "/common/ideas/convertedIdeas.txt");
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
void outputGeneralIdeas(const std::vector<HoI4::IdeaGroup>& generalIdeas, const Configuration& theConfiguration)
{
	auto manpowerFile = openIdeaFile("output/" + theConfiguration.getOutputName() + "/common/ideas/_manpower.txt");
	auto economicFile = openIdeaFile("output/" + theConfiguration.getOutputName() + "/common/ideas/_economic.txt");
	auto genericFile = openIdeaFile("output/" + theConfiguration.getOutputName() + "/common/ideas/zzz_generic.txt");

	std::for_each(generalIdeas.begin(),
		 generalIdeas.end(),
		 [&manpowerFile, &economicFile, &genericFile](auto& theGroup) {
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
		 });

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