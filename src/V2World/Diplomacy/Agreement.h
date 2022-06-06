#ifndef VIC2_AGREEMENT_H
#define VIC2_AGREEMENT_H



#include "external/common_items/Date.h"
#include <string>



namespace Vic2
{

class Agreement
{
  public:
	class Factory;

	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getCountry1() const { return country1; }
	[[nodiscard]] const auto& getCountry2() const { return country2; }
	[[nodiscard]] const auto& getDate() const { return startDate; }

  private:
	std::string type;
	std::string country1;
	std::string country2;
	date startDate;
};

} // namespace Vic2



#endif // VIC2_AGREEMENT_H_