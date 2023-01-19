#ifndef VIC2_DIPLOMACY_H_
#define VIC2_DIPLOMACY_H_



#include "src/V2World/Diplomacy/Agreement.h"
#include <vector>



namespace Vic2
{

class Diplomacy
{
  public:
	class Factory;

	[[nodiscard]] const auto& getAgreements() const { return agreements; }

  private:
	std::vector<Agreement> agreements;
};

} // namespace Vic2



#endif // V2DIPLOMACY_H_