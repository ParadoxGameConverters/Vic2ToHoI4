#ifndef HOI4_ARMY_H
#define HOI4_ARMY_H



#include "DivisionType.h"
#include "HOI4World/MilitaryMappings/MilitaryMappings.h"
#include "HOI4World/States/HoI4States.h"
#include "HOI4World/Technologies.h"
#include "V2World/Military/Army.h"
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

	std::map<std::string, int> getRequiredEquipment();

	friend std::ostream& operator<<(std::ostream& output, const Army& theArmy);

	[[nodiscard]] const auto& getLeftoverEquipment() const { return leftoverEquipment; }
	[[nodiscard]] const auto& getDivisionLocations() const { return divisionLocations; }

  private:
	static std::optional<int> getLocation(std::optional<int> vic2Location,
		 const Mappers::ProvinceMapper& provinceMapper);

	void convertArmyDivisions(const militaryMappings& theMilitaryMappings,
		 std::map<std::string, std::vector<SizedRegiment>>& BattalionsAndCompanies,
		 const technologies& countryTechnologies,
		 int location);

	bool missingRequiredTechnologies(const DivisionTemplateType& divisionTemplate,
		 const technologies& countryTechnologies);

	void collectLeftoverEquipment(std::map<std::string, std::vector<SizedRegiment>>& battalionsAndCompanies);

	std::vector<Vic2::Army> sourceArmies;
	std::vector<DivisionType> divisions;

	std::map<std::string, unsigned int> leftoverEquipment;

	std::set<int> divisionLocations;
};

} // namespace HoI4



#endif // HOI4_ARMY_H