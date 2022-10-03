#ifndef TANK_DESIGN_H
#define TANK_DESIGN_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
//#include "src/HOI4World/PlaneDesigns/PlaneUpgrades.h"
#include "src/HOI4World/Technologies.h"



namespace HoI4
{

class PlaneDesign: commonItems::parser
{
  public:
	explicit PlaneDesign(std::istream& theStream);

	PlaneDesign() = default;
	~PlaneDesign() = default;
	PlaneDesign(const PlaneDesign& source):
		 parser(source), name(source.name), type(source.type), modules(std::make_unique<PlaneModules>(*source.modules)),
		 icon(source.icon), obsolete(source.obsolete), requiredTechnologies(source.requiredTechnologies),
		 blockingTechnologies(source.blockingTechnologies)
	{
	}
	PlaneDesign& operator=(const PlaneDesign& rhs);
	PlaneDesign(PlaneDesign&&) = default;
	PlaneDesign& operator=(PlaneDesign&&) = default;

	[[nodiscard]] bool isValidDesign(const technologies& ownedTechs) const;

	[[nodiscard]] std::string getName() const { return name; }

	friend std::ostream& operator<<(std::ostream& output, const PlaneDesign& theDesign);

  private:
	std::string name;
	std::string type;
	std::unique_ptr<PlaneModules> modules;
	std::optional<std::string> icon;
	bool obsolete = false;

	std::set<std::string> requiredTechnologies;
	std::set<std::string> blockingTechnologies;
};

} // namespace HoI4



#endif // TANK_DESIGN_H