#include <map>
#include <set>
#include <string>

#ifndef SCENARIO_UTILITIES_H
#define SCENARIO_UTILITIES_H


struct IdeologySituation
{
	IdeologySituation(const std::string& ideology, const int support, const bool is_gov = false):
		 ideology_(ideology), support_(support), is_gov_(is_gov){};

	std::string ideology_;
	int support_;
	bool is_gov_;

	// In a sorted sense, the governing ideology should always be first, then the rest sorted by support
	bool operator>(const IdeologySituation& rhs) const;
};

typedef std::set<IdeologySituation, std::greater<IdeologySituation>> IdeologicalSituationSet;

const IdeologicalSituationSet GetIdeologicalSituation(const std::map<std::string, int>& ideology_support,
	 const std::string& gov_ideology);

const std::stringstream GetStreamFromFile(const std::string& input_file);

const std::string GetFileBufferStr(const std::string& input_file,
	 const std::string& folder,
	 const std::string& path = "Configurables/Scenarios");

// If private functions/static data members are later needed convert this to a static class with constructor deleted

#endif // SCENARIO_UTILITIES_H