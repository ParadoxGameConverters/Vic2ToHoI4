#include "newParser.h"



namespace mappers
{

class ProvinceMapping: commonItems::parser
{
  public:
	ProvinceMapping(std::istream& theStream);

	auto getVic2Nums() const { return Vic2Nums; }
	auto getHoI4Nums() const { return HoI4Nums; }

  private:
	std::vector<int> Vic2Nums;
	std::vector<int> HoI4Nums;
};

} // namespace mappers