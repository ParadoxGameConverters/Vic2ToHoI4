#ifndef VIC2_DIPLOMACY_H_
#define VIC2_DIPLOMACY_H_



#include "Date.h"
#include "Parser.h"
#include <memory>
#include <vector>



namespace Vic2
{

class Agreement;


class Diplomacy: commonItems::parser
{
  public:
	Diplomacy() = default;
	explicit Diplomacy(std::istream& theStream);

	const std::vector<const Agreement*>& getAgreements() const { return agreements; }

  private:
	Diplomacy(const Diplomacy&) = delete;
	Diplomacy& operator=(const Diplomacy&) = delete;

	std::vector<const Agreement*> agreements;
};

} // namespace Vic2



#endif // V2DIPLOMACY_H_