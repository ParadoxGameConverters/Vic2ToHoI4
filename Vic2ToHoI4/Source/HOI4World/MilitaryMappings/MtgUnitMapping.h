#ifndef MTG_UNIT_MAPPING_H
#define MTG_UNIT_MAPPING_H



#include "HoI4UnitType.h"
#include "Parser.h"



namespace HoI4
{

class MtgUnitMapping: commonItems::parser
{
  public:
	explicit MtgUnitMapping(std::istream& theStream);

	[[nodiscard]] auto getMapping() const { return std::make_pair(Vic2Type, HoI4Types); }

  private:
	std::string Vic2Type;
	std::vector<HoI4UnitType> HoI4Types;
};

} // namespace HoI4



#endif // MTG_UNIT_MAPPING_H