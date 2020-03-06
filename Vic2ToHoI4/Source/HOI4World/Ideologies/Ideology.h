#ifndef IDEOLOGY_H
#define IDEOLOGY_H



#include "../../Color.h"
#include "newParser.h"
#include <map>
#include <memory>
#include <string>
#include <vector>



namespace HoI4
{

class Ideology: commonItems::parser
{
  public:
	explicit Ideology(const std::string& _ideologyName, std::istream& theStream);
	Ideology(const Ideology& other);

	[[nodiscard]] std::vector<std::string> getTypes() const { return types; }

	friend std::ostream& operator<<(std::ostream& out, const Ideology& ideology);

  private:
	std::string ideologyName;
	std::vector<std::string> types;
	std::vector<std::string> dynamicFactionNames;
	std::unique_ptr<ConverterColor::Color> theColor;
	std::map<std::string, std::string> rules;
	float warImpactOnWorldTension = 0.0;
	float factionImpactOnWorldTension = 0.0;
	std::map<std::string, std::string> modifiers;
	std::map<std::string, std::string> factionModifiers;
	std::map<std::string, std::string> cans;
	std::string AI;
};

} // namespace HoI4



#endif // IDEOLOGY_H