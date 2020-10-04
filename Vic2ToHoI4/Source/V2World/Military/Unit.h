#ifndef UNIT_H
#define UNIT_H



#include "Parser.h"
#include <string>



namespace Vic2
{

class Unit: commonItems::parser
{
  public:
	class Factory;

	std::string getName() const { return name; }
	std::string getType() const { return type; }
	double getStrength() const { return strength; }
	double getOrganization() const { return organization; }
	double getExperience() const { return experience; }

  private:
	std::string name = "";
	std::string type = "";
	double strength = 0.0;
	double organization = 0.0;
	double experience = 0.0;
	int pop_id = 0;
};

} // namespace Vic2



#endif // UNIT_H