#ifndef VIC2_COUNTRY_H_
#define VIC2_COUNTRY_H_



#include "Color.h"
#include "Date.h"
#include "Parser.h"
#include "V2World/Ai/AI.h"
#include "V2World/Culture/CultureGroups.h"
#include "V2World/Diplomacy/Relations.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Military/Army.h"
#include "V2World/Military/Leaders/Leader.h"
#include "V2World/Military/Leaders/LeaderFactory.h"
#include "V2World/Politics/Party.h"
#include "V2World/Provinces/Province.h"
#include "V2World/States/State.h"
#include "V2World/States/StateDefinitions.h"
#include "V2World/Wars/War.h"
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{

class Country
{
  public:
	class Builder;
	class Factory;

	// functions to construct the country
	void addProvince(int provinceNum, const std::shared_ptr<Province>& province)
	{
		provinces.insert(std::make_pair(provinceNum, province));
	}
	void addCore(std::shared_ptr<Province> core) { cores.push_back(std::move(core)); }
	void replaceCores(std::vector<std::shared_ptr<Province>> newCores) { cores.swap(newCores); }
	void addWar(const War& theWar) { wars.push_back(theWar); }
	void setAtWar() { atWar = true; }
	void consolidateConquerStrategies(const std::map<int, std::shared_ptr<Province>>& allProvinces)
	{
		vic2AI.consolidateConquerStrategies(allProvinces);
	}

	void eatCountry(Country& target, bool debug);
	void mergeStates(const StateDefinitions& stateDefinitions);
	void putProvincesInStates();
	void determineEmployedWorkers();
	void setLocalisationNames(Localisations& vic2Localisations);
	void setLocalisationAdjectives(const Localisations& vic2Localisations);
	void handleMissingCulture(const CultureGroups& theCultureGroups);

	// functions to look up aspects of the country
	[[nodiscard]] const auto& getTag() const { return tag; }
	[[nodiscard]] const auto& getColor() const { return color; }
	[[nodiscard]] bool isHuman() const { return human; }
	[[nodiscard]] const auto& getStates() const { return states; }
	[[nodiscard]] bool hasLand() const { return !provinces.empty(); }
	[[nodiscard]] bool isEmpty() const { return cores.empty() && provinces.empty(); }
	[[nodiscard]] const auto& getCores() const { return cores; }
	[[nodiscard]] int getCapital() const { return capital; }
	[[nodiscard]] const auto& getPrimaryCulture() const { return primaryCulture; }
	[[nodiscard]] const auto& getPrimaryCultureGroup() const { return primaryCultureGroup; }
	[[nodiscard]] const auto& getAcceptedCultures() const { return acceptedCultures; }
	[[nodiscard]] bool isAnAcceptedCulture(const std::string& culture) const
	{
		return acceptedCultures.contains(culture);
	}
	[[nodiscard]] const auto& getTechnologiesAndInventions() const { return technologiesAndInventions; }
	[[nodiscard]] const auto& getRelations() const { return relations; }
	[[nodiscard]] const auto& getAI() const { return vic2AI; }
	[[nodiscard]] bool isCivilized() const { return civilized; }
	[[nodiscard]] const auto& getArmies() const { return armies; }
	[[nodiscard]] const auto& getLeaders() const { return leaders; }
	[[nodiscard]] double getRevanchism() const { return revanchism; }
	[[nodiscard]] double getWarExhaustion() const { return warExhaustion; }
	[[nodiscard]] double getBadBoy() const { return badBoy; }
	[[nodiscard]] const auto& getFlags() const { return flags; }
	[[nodiscard]] const auto& getGovernment() const { return government; }
	[[nodiscard]] const auto& getUpperHouseComposition() const { return upperHouseComposition; }
	[[nodiscard]] const auto& getRulingParty() const { return rulingParty; }
	[[nodiscard]] const auto& getActiveParties() const { return activeParties; }
	[[nodiscard]] const auto& getLastElection() const { return lastElection; }
	[[nodiscard]] std::map<std::string, std::vector<std::string>> getAllShipNames() const { return shipNames; }
	[[nodiscard]] bool isAtWar() const { return atWar; }
	[[nodiscard]] const auto& getWars() const { return wars; }

	[[nodiscard]] auto& getModifiableArmies() { return armies; }

	[[nodiscard]] bool hasCoreOnCapital() const;
	[[nodiscard]] int32_t getEmployedWorkers() const;
	[[nodiscard]] float getAverageIssueSupport(const std::string& issueName) const;
	[[nodiscard]] std::optional<std::string> getName(const std::string& language) const;
	[[nodiscard]] std::optional<std::string> getAdjective(const std::string& language) const;
	[[nodiscard]] std::vector<std::string> getShipNames(const std::string& category) const;

  private:
	std::map<std::string, int> determineCultureSizes();
	static std::string selectLargestCulture(const std::map<std::string, int>& cultureSizes);

	void setLocalisationName(const std::string& language, const std::string& name);
	void setLocalisationAdjective(const std::string& language, const std::string& adjective);

	std::string tag;
	std::optional<commonItems::Color> color;
	bool human = false;

	std::vector<State> states;
	std::map<int, std::shared_ptr<Province>> provinces;
	std::vector<std::shared_ptr<Province>> cores;
	int capital = 0;

	std::string primaryCulture = "no_culture";
	std::string primaryCultureGroup = "no_culture";
	std::set<std::string> acceptedCultures;

	std::set<std::string> technologiesAndInventions;

	std::map<std::string, Relations> relations;
	AI vic2AI;
	bool civilized = false;

	std::vector<Army> armies;
	std::vector<Leader> leaders;

	double revanchism = 0.0;
	double warExhaustion = 0.0;
	double badBoy = 0.0;

	std::set<std::string> flags;

	std::string government;
	std::map<std::string, double> upperHouseComposition;
	std::vector<unsigned int> activePartyIDs;
	std::optional<Party> rulingParty;
	std::set<Party> activeParties;
	date lastElection;

	std::string domainName;
	std::string domainAdjective;
	std::map<std::string, std::string> namesByLanguage;
	std::map<std::string, std::string> adjectivesByLanguage;
	std::map<std::string, std::vector<std::string>> shipNames;

	bool atWar = false;
	std::vector<War> wars; // only the country that started a war owns it here
};


bool operator==(const Country& one, const Country& other);

} // namespace Vic2

#endif // VIC2_COUNTRY_H_