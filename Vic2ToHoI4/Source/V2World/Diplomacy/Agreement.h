#ifndef VIC2_AGREEMENT_H_
#define VIC2_AGREEMENT_H_



#include "Date.h"
#include <string>



namespace Vic2
{

class Agreement
{
  public:
	class Factory;

	std::string getType() const { return type; }
	std::string getCountry1() const { return country1; }
	std::string getCountry2() const { return country2; }
	date getDate() const { return startDate; }

  private:
	std::string type = "";
	std::string country1 = "";
	std::string country2 = "";
	date startDate;
};

} // namespace Vic2



#endif // VIC2_AGREEMENT_H_
