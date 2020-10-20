#ifndef VIC2_COUNTRY_H_
#define VIC2_COUNTRY_H_



#include "Color.h"
#include "Culture/CultureGroups.h"
#include "Date.h"
#include "Diplomacy/Relations.h"
#include "Diplomacy/RelationsFactory.h"
#include "Localisations/Vic2Localisations.h"
#include "Military/Army.h"
#include "Military/Leader.h"
#include "Military/LeaderFactory.h"
#include "Parser.h"
#include "Politics/Party.h"
#include "Provinces/Province.h"
#include "States/State.h"
#include "States/StateDefinitions.h"
#include "States/StateFactory.h"
#include "Technology/Inventions.h"
#include "Wars/War.h"
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{

class Country: commonItems::parser
{
  public:
	Country() = default;
	explicit Country(const std::string& theTag,
		 std::istream& theStream,
		 const Inventions& theInventions,
		 const CultureGroups& theCultureGroups,
		 const StateDefinitions& theStateDefinitions,
		 State::Factory& stateFactory,
		 Relations::Factory& relationsFactory,
		 Leader::Factory& leaderFactory,
		 Army::Factory& armyFactory);
	virtual ~Country() = default;

	void addProvince(const std::pair<const int, std::shared_ptr<Province>>& province) { provinces.insert(province); }
	void setColor(const commonItems::Color& Color) { color = Color; }
	void addCore(std::shared_ptr<Province> core) { cores.push_back(core); }
	void replaceCores(std::vector<std::shared_ptr<Province>> newCores) { cores.swap(newCores); }
	void setShipNames(const std::map<std::string, std::vector<std::string>>& newShipNames) { shipNames = newShipNames; }
	void addWar(const War& theWar) { wars.push_back(theWar); }
	void setAtWar() { atWar = true; }

	void eatCountry(Country* target, bool debug);
	void putProvincesInStates();
	void determineEmployedWorkers();
	void setLocalisationNames(Localisations& vic2Localisations);
	void setLocalisationAdjectives(const Localisations& vic2Localisations);
	void handleMissingCulture(const CultureGroups& theCultureGroups);
	void setParties(const std::vector<Party>& allParties);

	[[nodiscard]] const auto& getRelations() const { return relations; }
	auto& getStates() { return states; }
	virtual std::string getTag() const { return tag; }
	std::string getIdentifier() const;
	std::string getPrimaryCulture() const { return primaryCulture; }
	virtual std::string getPrimaryCultureGroup() const { return primaryCultureGroup; }
	std::set<std::string> getAcceptedCultures() const { return acceptedCultures; }
	bool isAnAcceptedCulture(const std::string& culture) const { return (acceptedCultures.count(culture) > 0); }
	virtual std::set<std::string> getInventions() const { return discoveredInventions; }
	virtual std::string getGovernment() const { return government; }
	std::set<std::string> getFlags() const { return flags; }
	virtual date getLastElection() const { return lastElection; }
	virtual int getCapital() const { return capital; }
	virtual std::set<std::string> getTechs() const { return techs; }
	virtual const commonItems::Color& getColor() const { return color; }
	auto getArmies() const { return armies; }
	[[nodiscard]] const auto& getLeaders() const { return leaders; }
	virtual double getRevanchism() const { return revanchism; }
	virtual double getWarExhaustion() const { return warExhaustion; }
	double getBadBoy() const { return badboy; }
	double getPrestige() const { return prestige; }
	virtual const std::map<int, std::shared_ptr<Province>>& getProvinces() const { return provinces; }
	const auto& getCores() const { return cores; }
	bool isEmpty() const { return ((cores.size() == 0) && (provinces.size() == 0)); }
	bool isCivilized() const { return civilized; }
	virtual bool isHuman() const { return human; }
	virtual std::map<std::string, double> getUpperHouseComposition() const { return upperHouseComposition; }
	std::vector<War> getWars() const { return wars; }
	virtual bool isAtWar() const { return atWar; }
	virtual const std::set<Vic2::Party>& getActiveParties() const { return activeParties; }
	virtual const Vic2::Party& getRulingParty() const { return *rulingParty; }

	virtual std::optional<std::string> getName(const std::string& language) const;
	std::optional<std::string> getAdjective(const std::string& language) const;
	double getUpperHousePercentage(const std::string& ideology) const;
	long getEmployedWorkers() const;
	bool hasCoreOnCapital() const;
	std::vector<std::string> getShipNames(const std::string& category) const;
	double getAverageMilitancy() const;
	virtual float getAverageIssueSupport(const std::string& issueName) const;

  private:
	void setLocalisationName(const std::string& language, const std::string& name);
	void setLocalisationAdjective(const std::string& language, const std::string& adjective);

	std::map<std::string, int> determineCultureSizes();
	std::string selectLargestCulture(const std::map<std::string, int>& cultureSizes);

	std::string tag = "";
	commonItems::Color color;

	std::vector<State> states;
	std::map<int, std::shared_ptr<Province>> provinces;
	std::vector<std::shared_ptr<Province>> cores;
	int capital = 0;

	std::string primaryCulture = "";
	std::string primaryCultureGroup;
	std::set<std::string> acceptedCultures;

	std::set<std::string> techs;
	std::set<std::string> discoveredInventions;

	std::map<std::string, Relations> relations;
	bool civilized = false;

	std::vector<Army> armies;
	std::vector<Leader> leaders;

	double revanchism = 0.0;
	double warExhaustion = 0.0;
	double badboy = 0.0;
	double prestige = 0.0;

	std::set<std::string> flags;

	std::string government = "";
	std::map<std::string, double> upperHouseComposition;
	unsigned int rulingPartyID = 0; // Bad value, but normal for Rebel faction.
	std::vector<unsigned int> activePartyIDs;
	std::unique_ptr<Party> rulingParty;
	std::set<Party> activeParties;
	date lastElection;

	std::string domainName = "";
	std::string domainAdjective = "";
	std::map<std::string, std::string> namesByLanguage;
	std::map<std::string, std::string> adjectivesByLanguage;
	std::map<std::string, std::vector<std::string>> shipNames;

	bool human = false;

	bool atWar = false;
	std::vector<War> wars;
};


bool operator==(const Country& one, const Country& other);

} // namespace Vic2

#endif // VIC2_COUNTRY_H_