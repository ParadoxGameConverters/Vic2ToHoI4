#ifndef NAMES_MAPPER_H
#define NAMES_MAPPER_H



#include "Parser.h"
#include <map>
#include <optional>
#include <random>
#include <string>
#include <vector>



class Configuration;



namespace HoI4
{

class Names: commonItems::parser
{
  public:
	Names() noexcept {};
	void init(const Configuration& theConfiguration);
	virtual ~Names() = default;

	virtual std::optional<std::vector<std::string>> getMaleNames(const std::string& culture) const;
	std::optional<std::vector<std::string>> getFemaleNames(const std::string& culture) const;
	std::optional<std::vector<std::string>> getSurnames(const std::string& culture) const;
	std::optional<std::vector<std::string>> getFemaleSurnames(const std::string& culture) const;
	std::optional<std::vector<std::string>> getCallsigns(const std::string& culture) const;

	std::optional<std::string> getMaleName(const std::string& culture);
	std::optional<std::string> getFemaleName(const std::string& culture);
	std::optional<std::string> getSurname(const std::string& culture);
	std::optional<std::string> getFemaleSurname(const std::string& culture);
	std::optional<std::string> getCallsign(const std::string& culture);

	std::optional<std::string> takeCarCompanyName(const std::string& culture);
	std::optional<std::string> takeWeaponCompanyName(const std::string& culture);
	std::optional<std::string> takeAircraftCompanyName(const std::string& culture);
	std::optional<std::string> takeNavalCompanyName(const std::string& culture);
	std::optional<std::string> takeIndustryCompanyName(const std::string& culture);
	std::optional<std::string> takeElectronicCompanyName(const std::string& culture);

	std::optional<std::string> takeIntelligenceAgencyName(const std::string& culture);

  private:
	Names(const Names&) = delete;
	Names& operator=(const Names&) = delete;

	void processVic2CulturesFile(const std::string& filename);
	void processNamesFile();
	void checkForNames();

	void addNamesToMap(std::map<std::string, std::vector<std::string>>& map,
		 const std::string& culture,
		 std::vector<std::string>& newNames);

	std::optional<std::string> takeCompanyName(std::map<std::string, std::vector<std::string>>& companyNames,
		 const std::string& culture);

	std::map<std::string, std::vector<std::string>> maleNamesMap;
	std::map<std::string, std::vector<std::string>> femaleNamesMap;
	std::map<std::string, std::vector<std::string>> surnamesMap;
	std::map<std::string, std::vector<std::string>> femaleSurnamesMap;
	std::map<std::string, std::vector<std::string>> callsignsMap;

	std::map<std::string, std::vector<std::string>> carCompanyNames;
	std::map<std::string, std::vector<std::string>> weaponCompanyNames;
	std::map<std::string, std::vector<std::string>> aircraftCompanyNames;
	std::map<std::string, std::vector<std::string>> navalCompanyNames;
	std::map<std::string, std::vector<std::string>> industryCompanyNames;
	std::map<std::string, std::vector<std::string>> electronicCompanyNames;

	std::map<std::string, std::vector<std::string>> intelligenceAgencyNames;

	std::mt19937 rng;
};

} // namespace HoI4



#endif // NAMES_MAPPER_H