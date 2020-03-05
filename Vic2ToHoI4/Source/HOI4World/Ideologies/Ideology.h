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

	void output(std::ostream& file) const;

	[[nodiscard]] std::vector<std::string> getTypes() const { return types; }

  private:
	void outputTypes(std::ostream& file) const;
	void outputDynamicFactionNames(std::ostream& file) const;
	void outputTheColor(std::ostream& file) const;
	void outputRules(std::ostream& file) const;
	void outputOnWorldTension(std::ostream& file) const;
	void outputModifiers(std::ostream& file) const;
	void outputFactionModifiers(std::ostream& file) const;
	void outputCans(std::ostream& file) const;
	void outputAI(std::ostream& file) const;

	std::string ideologyName;
	std::vector<std::string> types;
	std::vector<std::string> dynamicFactionNames;
	std::unique_ptr<ConverterColor::Color> theColor;
	std::map<std::string, std::string> rules;
	float warImpactOnWorldTension = 0.0;
	float factionImpactOnWorldTension = 0.0;
	std::map<std::string, std::string> modifiers;
	std::map<std::string, float> factionModifiers;
	std::map<std::string, std::string> cans;
	std::string AI;
};

} // namespace HoI4



#endif // IDEOLOGY_H