#ifndef VIC2_POP_H_
#define VIC2_POP_H_



#include <map>
#include <string>



namespace Vic2
{


class Pop
{
  public:
	class Factory;
	Pop() = default;

	[[nodiscard]] int getSize() const { return size; }
	[[nodiscard]] std::string getType() const { return type; }
	[[nodiscard]] std::string getCulture() const { return culture; }
	[[nodiscard]] double getLiteracy() const { return literacy; }
	[[nodiscard]] double getMilitancy() const { return militancy; }
	[[nodiscard]] std::map<std::string, float> getIssues() const { return popIssues; }

	[[nodiscard]] float getIssue(const std::string& issueName) const;
	[[nodiscard]] int getID() const { return id; }

  private:
	int size = 0;
	std::string type;
	std::string culture = "no_culture";
	std::string religion;
	double literacy = 0.0;
	double consciousness = 0.0;
	double militancy = 0.0;
	int id = 0;
	std::map<std::string, float> popIssues;
};

} // namespace Vic2



#endif // VIC2_POP_H_