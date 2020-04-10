#ifndef VIC2_LOCALISATIONS_H
#define VIC2_LOCALISATIONS_H



#include <map>
#include <optional>
#include <string>
#include <unordered_map>



namespace Vic2
{

class Localisations
{
  public:
	Localisations() noexcept;

	const std::optional<std::string> getTextInLanguage(const std::string& key, const std::string& language) const;
	const std::map<std::string, std::string> getTextInEachLanguage(const std::string& key) const;
	void updateDomainCountry(const std::string& tag, const std::string& dominionName);

  private:
	void ReadFromAllFilesInFolder(const std::string& folderPath);
	void ReadFromFile(const std::string& fileName);
	void processLine(const std::string& line);
	std::string getNextLocalisation(const std::string& line, int& division);

	typedef std::map<std::string, std::string> LanguageToLocalisationMap;
	typedef std::unordered_map<std::string, LanguageToLocalisationMap> KeyToLocalisationsMap;
	KeyToLocalisationsMap localisations;

	std::map<std::string, std::string> localisationToKeyMap;
};

} // namespace Vic2



#endif // VIC2_LOCALISATIONS_H