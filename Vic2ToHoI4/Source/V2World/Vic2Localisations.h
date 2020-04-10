#ifndef VIC2_LOCALISATIONS_H
#define VIC2_LOCALISATIONS_H



#include <map>
#include <optional>
#include <string>
#include <unordered_map>
using namespace std;



namespace Vic2
{

class Localisations
{
  public:
	Localisations() noexcept;

	const optional<string> getTextInLanguage(const string& key, const string& language) const;
	const map<string, string> getTextInEachLanguage(const string& key) const;
	void updateDomainCountry(const string& tag, const string& dominionName);

  private:
	void ReadFromAllFilesInFolder(const string& folderPath);
	void ReadFromFile(const string& fileName);
	void processLine(const std::string& line);
	string getNextLocalisation(const std::string& line, int& division);

	Localisations(const Localisations&) = delete;
	Localisations& operator=(const Localisations&) = delete;

	typedef map<string, string> LanguageToLocalisationMap;
	typedef unordered_map<string, LanguageToLocalisationMap> KeyToLocalisationsMap;
	KeyToLocalisationsMap localisations;

	map<string, string> localisationToKeyMap;
};

} // namespace Vic2



#endif // VIC2_LOCALISATIONS_H