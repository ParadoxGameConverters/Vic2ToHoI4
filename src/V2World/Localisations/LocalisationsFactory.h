#ifndef LOCALISATIONS_FACTORY_H
#define LOCALISATIONS_FACTORY_H



#include "src/Configuration.h"
#include "Vic2Localisations.h"



namespace Vic2
{

enum class Encoding
{
	Win1250,
	Win1251,
	Win1252,
};


class Localisations::Factory
{
  public:
	std::unique_ptr<Localisations> importLocalisations(const Configuration& theConfiguration);

  private:
	void ReadFromAllFilesInFolder(const std::string& folderPath);
	void ReadFromFile(const std::string& fileName);
	void processLine(const std::string& line);
	static std::tuple<std::string, size_t> extractNextLocalisation(const std::string& line, size_t division);
	static std::string convertToUtf8(const std::string& rawLocalisation, Encoding encoding);

	KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
};

} // namespace Vic2



#endif // LOCALISATIONS_FACTORY_H