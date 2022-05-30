#ifndef CULTURE_NAMES_H
#define CULTURE_NAMES_H



#include "Parser.h"
#include <string>
#include <vector>



namespace HoI4
{

class CultureNames: commonItems::parser
{
  public:
	explicit CultureNames(std::istream& theStream);

	void convertVic2NamesToUTF8();

	[[nodiscard]] auto takeMaleNames() { return std::move(maleNames); }
	[[nodiscard]] auto takeSurnames() { return std::move(surnames); }
	[[nodiscard]] auto takeFemaleNames() { return std::move(femaleNames); }
	[[nodiscard]] auto takeFemaleSurnames() { return std::move(femaleSurnames); }
	[[nodiscard]] auto takeCallsigns() { return std::move(callsigns); }
	[[nodiscard]] auto takeIndustryCompanies() { return std::move(industryCompanies); }
	[[nodiscard]] auto takeElectronicCompanies() { return std::move(electronicCompanies); }
	[[nodiscard]] auto takeCarCompanies() { return std::move(carCompanies); }
	[[nodiscard]] auto takeNavalCompanies() { return std::move(navalCompanies); }
	[[nodiscard]] auto takeWeaponCompanies() { return std::move(weaponCompanies); }
	[[nodiscard]] auto takeAircraftCompanies() { return std::move(aircraftCompanies); }
	[[nodiscard]] auto takeIntelligenceAgencies() { return std::move(intelligenceAgencies); }

  private:
	std::vector<std::string> maleNames;
	std::vector<std::string> surnames;
	std::vector<std::string> femaleNames;
	std::vector<std::string> femaleSurnames;
	std::vector<std::string> callsigns;
	std::vector<std::string> industryCompanies;
	std::vector<std::string> electronicCompanies;
	std::vector<std::string> carCompanies;
	std::vector<std::string> navalCompanies;
	std::vector<std::string> weaponCompanies;
	std::vector<std::string> aircraftCompanies;
	std::vector<std::string> intelligenceAgencies;
};

} // namespace HoI4



#endif // CULTURE_NAMES_H