#ifndef VIC2_POP_H_
#define VIC2_POP_H_



#include "Parser.h"
#include <map>
#include <memory>
#include <string>



namespace Vic2
{
class Issues;

class Pop: commonItems::parser
{
  public:
	explicit Pop(const std::string& typeString, std::istream& theStream, const Issues& theIssues);

	static Pop* getByID(const int idx);

	int getSize() const { return size; }
	std::string getType() const { return type; }
	std::string getCulture() const { return culture; }
	double getLiteracy() const { return literacy; }
	double getMilitancy() const { return militancy; }
	std::map<std::string, float> getIssues() const { return popIssues; }

	float getIssue(const std::string& issueName) const;
	int getID() const { return id; }

  private:
	int size = 0;
	std::string type = "";
	std::string culture = "no_culture";
	std::string religion = "";
	double literacy = 0.0;
	double consciousness = 0.0;
	double militancy = 0.0;
	int id = 0;
	std::map<std::string, float> popIssues;

	static std::map<int, Pop*> pop_map;
};
} // namespace Vic2



#endif // VIC2_POP_H_
