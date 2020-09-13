#ifndef VIC2_DIPLOMACY_H_
#define VIC2_DIPLOMACY_H_



#include "Date.h"
#include "Parser.h"
#include "Agreement.h"
#include <memory>
#include <vector>



namespace Vic2
{

class Diplomacy: commonItems::parser
{
  public:
	Diplomacy() = default;
	explicit Diplomacy(std::istream& theStream);

	const auto& getAgreements() const { return agreements; }

  private:
	Diplomacy(const Diplomacy&) = delete;
	Diplomacy& operator=(const Diplomacy&) = delete;

	std::vector<Agreement> agreements;
};

} // namespace Vic2



#endif // V2DIPLOMACY_H_