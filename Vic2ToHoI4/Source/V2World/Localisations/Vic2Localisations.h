#ifndef VIC2_LOCALISATIONS_H
#define VIC2_LOCALISATIONS_H



#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>



class Configuration;



namespace Vic2
{

using LanguageToLocalisationMap = std::map<std::string, std::string>;
using KeyToLocalisationsMap = std::unordered_map<std::string, LanguageToLocalisationMap>;


class Localisations
{
  public:
	class Factory;

	Localisations(KeyToLocalisationsMap localisations, std::map<std::string, std::string> localisationToKeyMap):
		 localisations(std::move(localisations)), localisationToKeyMap(std::move(localisationToKeyMap))
	{
	}

	[[nodiscard]] std::optional<std::string> getTextInLanguage(const std::string& key,
		 const std::string& language) const;
	[[nodiscard]] std::map<std::string, std::string> getTextInEachLanguage(const std::string& key) const;
	void updateDomainCountry(const std::string& tag, const std::string& domainName);

  private:
	KeyToLocalisationsMap localisations;
	std::map<std::string, std::string> localisationToKeyMap;
};

} // namespace Vic2



#endif // VIC2_LOCALISATIONS_H