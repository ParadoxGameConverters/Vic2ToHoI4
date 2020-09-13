#ifndef VIC2_AGREEMENT_H_
#define VIC2_AGREEMENT_H_



#include "Date.h"
#include "Parser.h"
#include <memory>
#include <string>



namespace Vic2
{

class Agreement: commonItems::parser
{
  public:
	explicit Agreement(const std::string& agreementType, std::istream& theStream);

	std::string getType() const { return type; }
	std::string getCountry1() const { return country1; }
	std::string getCountry2() const { return country2; }
	date getDate() const { return startDate; }

  private:
	Agreement(const Agreement&) = delete;
	Agreement& operator=(const Agreement&) = delete;

	std::string type = "";
	std::string country1 = "";
	std::string country2 = "";
	date startDate;
};

} // namespace Vic2



#endif // VIC2_AGREEMENT_H_
