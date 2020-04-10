#ifndef VIC2_LOCALISATIONS_H
#define VIC2_LOCALISATIONS_H



#include <map>
#include <optional>
#include <string>
#include <unordered_map>
using namespace std;



class V2Localisations
{
  public:
	V2Localisations() noexcept;

	const optional<string> getTextInLanguage(const string& key, const string& language) const;
	const map<string, string> getTextInEachLanguage(const string& key) const;
	void updateDomainCountry(const string& tag, const string& dominionName);

  private:
	void ReadFromAllFilesInFolder(const string& folderPath);
	void ReadFromFile(const string& fileName);
	void processLine(const std::string& line);
	string getNextLocalisation(const std::string& line, int& division);

	V2Localisations(const V2Localisations&) = delete;
	V2Localisations& operator=(const V2Localisations&) = delete;

	typedef map<string, string> LanguageToLocalisationMap;
	typedef unordered_map<string, LanguageToLocalisationMap> KeyToLocalisationsMap;
	KeyToLocalisationsMap localisations;

	map<string, string> localisationToKeyMap;
};



#endif // VIC2_LOCALISATIONS_H