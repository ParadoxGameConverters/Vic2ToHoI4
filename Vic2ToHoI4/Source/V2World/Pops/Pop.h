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

	[[nodiscard]] std::string getType() const { return type; }
	[[nodiscard]] std::string getCulture() const { return culture; }
	[[nodiscard]] int getSize() const { return size; }
	[[nodiscard]] double getLiteracy() const { return literacy; }
	[[nodiscard]] double getMilitancy() const { return militancy; }

	[[nodiscard]] float getIssueSupport(const std::string& issueName) const;

  private:
	std::string type;
	std::string culture = "no_culture";
	int size = 0;
	double literacy = 0.0;
	double militancy = 0.0;

	std::map<std::string, float> popIssues;
};

} // namespace Vic2



#endif // VIC2_POP_H_