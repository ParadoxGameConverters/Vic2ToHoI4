#ifndef HOI4_ARMY_H
#define HOI4_ARMY_H



#include "src/HOI4World/Military/DivisionType.h"
#include "src/HOI4World/MilitaryMappings/MilitaryMappings.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/HOI4World/Technologies.h"
#include "src/V2World/Military/Army.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{


typedef struct SizedRegiment
{
	double unitSize = 0.0;
	double experience = 0.0;
	double strength = 0.0;
} SizedRegiment;


class Army
{
  public:
	Army() = default;

	void addSourceArmies(const std::vector<Vic2::Army>& _sourceArmies) { sourceArmies = _sourceArmies; }

	void convertArmies(const militaryMappings& theMilitaryMappings,
		 int backupLocation,
		 double forceMultiplier,
		 const technologies& countryTechnologies,
		 const States& theStates,
		 const Mappers::ProvinceMapper& provinceMapper);


	friend std::ostream& operator<<(std::ostream& output, const Army& theArmy);

	[[nodiscard]] const auto& getDivisionTypesAndAmounts() const { return divisionTypesAndAmounts; }
	[[nodiscard]] const auto& getLeftoverEquipment() const { return leftoverEquipment; }
	[[nodiscard]] const auto& getDivisionLocations() const { return divisionLocations; }

  private:
	static std::optional<int> getLocation(std::optional<int> vic2Location,
		 const Mappers::ProvinceMapper& provinceMapper);

	void convertArmyDivisions(const militaryMappings& theMilitaryMappings,
		 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
		 const technologies& countryTechnologies,
		 int location);

	void addAvailableBattalionsAndCompanies(
		 std::map<std::string, std::vector<SizedRegiment>>& availableBattalionsAndCompanies,
		 const Vic2::Army& sourceArmy,
		 const militaryMappings& theMilitaryMappings,
		 const double forceMultiplier);

	bool missingRequiredTechnologies(const DivisionTemplateType& divisionTemplate,
		 const technologies& countryTechnologies);

	void collectLeftoverEquipment(std::map<std::string, std::vector<SizedRegiment>>& battalionsAndCompanies);

	std::vector<Vic2::Army> sourceArmies;
	std::vector<DivisionType> divisions;

	std::map<std::string, int> divisionTypesAndAmounts;
	std::map<std::string, unsigned int> leftoverEquipment;

	std::set<int> divisionLocations;
};

} // namespace HoI4



#endif // HOI4_ARMY_H