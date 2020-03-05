#ifndef HOI4_IDEOLOGY
#define HOI4_IDEOLOGY



#include "newParser.h"
#include "../../Color.h"
#include <fstream>
#include <map>
#include <string>
#include <vector>



class HoI4Ideology: commonItems::parser
{
	public:
		explicit HoI4Ideology(const std::string& ideologyName, std::istream& theStream);
		void output(std::ofstream& file) const;

		std::vector<std::string> getTypes() const { return types; }

	private:
		HoI4Ideology(const HoI4Ideology&) = delete;
		HoI4Ideology& operator=(const HoI4Ideology&) = delete;

		void outputTypes(std::ofstream& file) const;
		void outputDynamicFactionNames(std::ofstream& file) const;
		void outputTheColor(std::ofstream& file) const;
		void outputRules(std::ofstream& file) const;
		void outputOnWorldTension(std::ofstream& file) const;
		void outputModifiers(std::ofstream& file) const;
		void outputFactionModifiers(std::ofstream& file) const;
		void outputCans(std::ofstream& file) const;
		void outputAI(std::ofstream& file) const;

		std::string ideologyName;
		std::vector<std::string> types;
		std::vector<std::string> dynamicFactionNames;
		ConverterColor::Color* theColor = nullptr;
		std::map<std::string, std::string> rules;
		float warImpactOnWorldTension = 0.0;
		float factionImpactOnWorldTension = 0.0;
		std::map<std::string, std::string> modifiers;
		std::map<std::string, float> factionModifiers;
		std::map<std::string, std::string> cans;
		std::string AI;
};



#endif // HOI4_IDEOLOGY