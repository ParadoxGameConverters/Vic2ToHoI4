#ifndef VIC2_LOCALISATIONS_H
#define VIC2_LOCALISATIONS_H



#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>


namespace Vic2
{

using LanguageToLocalisationMap = std::map<std::string, std::string>;
using KeyToLocalisationsMap = std::unordered_map<std::string, LanguageToLocalisationMap>;


class Localisations
{
  public:
	class Parser;

	Localisations(KeyToLocalisationsMap localisations, std::map<std::string, std::string> localisationToKeyMap):
		 localisations(localisations), localisationToKeyMap(std::move(localisationToKeyMap))
	{
	}

	const std::optional<std::string> getTextInLanguage(const std::string& key, const std::string& language) const;
	const std::map<std::string, std::string> getTextInEachLanguage(const std::string& key) const;
	void updateDomainCountry(const std::string& tag, const std::string& dominionName);

  private:
	KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
};


class Localisations::Parser
{
  public:
	std::unique_ptr<Localisations> importLocalisations();

  private:
	void ReadFromAllFilesInFolder(const std::string& folderPath);
	void ReadFromFile(const std::string& fileName);
	void processLine(const std::string& line);
	std::string getNextLocalisation(const std::string& line, int& division);

	KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
};

} // namespace Vic2



#endif // VIC2_LOCALISATIONS_H