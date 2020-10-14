#ifndef VIC2_LOCALISATIONS_H
#define VIC2_LOCALISATIONS_H



#include <map>
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
	class Factory;

	Localisations(KeyToLocalisationsMap _localisations, std::map<std::string, std::string> _localisationToKeyMap):
		 localisations(std::move(_localisations)), localisationToKeyMap(std::move(_localisationToKeyMap))
	{
	}

	[[nodiscard]] std::optional<std::string> getTextInLanguage(const std::string& key,
		 const std::string& language) const;
	[[nodiscard]] LanguageToLocalisationMap getTextInEachLanguage(const std::string& key) const;

	void updateDomainCountry(const std::string& tag, const std::string& domainName);

  private:
	LanguageToLocalisationMap lookupRegionLocalisations(const std::string& domainName);
	static std::string determineReplacementName(const std::string& domainName,
		 const LanguageToLocalisationMap& regionLocalisations,
		 const std::string& language);

	KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
};

} // namespace Vic2



#endif // VIC2_LOCALISATIONS_H