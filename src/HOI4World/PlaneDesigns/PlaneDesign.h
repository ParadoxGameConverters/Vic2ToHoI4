#ifndef PLANE_DESIGN_H
#define PLANE_DESIGN_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
#include "src/HOI4World/Technologies.h"



namespace HoI4
{

class PlaneDesign: commonItems::parser
{
  public:
	explicit PlaneDesign(std::istream& the_stream);

	PlaneDesign() = default;
	~PlaneDesign() = default;
	PlaneDesign(const PlaneDesign& source):
		 parser(source), name_(source.name_), type_(source.type_),
		 modules_(std::make_unique<PlaneModules>(*source.modules_)), icon_(source.icon_), obsolete_(source.obsolete_),
		 required_technologies_(source.required_technologies_), blocking_technologies_(source.blocking_technologies_)
	{
	}
	PlaneDesign& operator=(const PlaneDesign& rhs);
	PlaneDesign(PlaneDesign&&) = default;
	PlaneDesign& operator=(PlaneDesign&&) = default;

	[[nodiscard]] bool IsValidDesign(const technologies& owned_techs) const;

	[[nodiscard]] std::string GetName() const { return name_; }

	friend std::ostream& operator<<(std::ostream& output, const PlaneDesign& the_design);

  private:
	std::string name_;
	std::string type_;
	std::unique_ptr<PlaneModules> modules_;
	std::optional<std::string> icon_;
	bool obsolete_ = false;

	std::set<std::string> required_technologies_;
	std::set<std::string> blocking_technologies_;
};

} // namespace HoI4



#endif // PLANE_DESIGN_H