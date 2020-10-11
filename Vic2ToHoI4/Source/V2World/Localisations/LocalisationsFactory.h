#ifndef LOCALISATIONS_FACTORY_H
#define LOCALISATIONS_FACTORY_H



#include "Vic2Localisations.h"



namespace Vic2
{

class Localisations::Factory
{
  public:
	std::unique_ptr<Localisations> importLocalisations(const Configuration& theConfiguration);

  private:
	void ReadFromAllFilesInFolder(const std::string& folderPath);
	void ReadFromFile(const std::string& fileName);
	void processLine(const std::string& line);
	std::string getNextLocalisation(const std::string& line, size_t& division);

	KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
};

} // namespace Vic2



#endif // LOCALISATIONS_FACTORY_H