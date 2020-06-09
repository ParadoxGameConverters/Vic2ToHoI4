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

	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getCulture() const { return culture; }
	[[nodiscard]] const auto& getSize() const { return size; }
	[[nodiscard]] const auto& getLiteracy() const { return literacy; }
	[[nodiscard]] const auto& getMilitancy() const { return militancy; }

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