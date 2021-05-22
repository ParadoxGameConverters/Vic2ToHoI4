#ifndef VIC2_POP_H_
#define VIC2_POP_H_



#include <map>
#include <string>



namespace Vic2
{


struct PopOptions
{
	std::string type;
	std::string culture = "no_culture";
	int size = 0;
	double literacy = 0.0;
	double militancy = 0.0;
	std::map<std::string, float> popIssues;
};


class Pop
{
  public:
	class Factory;

	Pop() = default;
	explicit Pop(const PopOptions& options):
		 type_(options.type), culture_(options.culture), size_(options.size), literacy_(options.literacy),
		 militancy_(options.militancy), popIssues_(options.popIssues)
	{
	}

	[[nodiscard]] const auto& getType() const { return type_; }
	[[nodiscard]] const auto& getCulture() const { return culture_; }
	[[nodiscard]] const auto& getSize() const { return size_; }
	[[nodiscard]] const auto& getLiteracy() const { return literacy_; }
	[[nodiscard]] const auto& getMilitancy() const { return militancy_; }

	[[nodiscard]] float getIssueSupport(const std::string& issueName) const;

  private:
	std::string type_;
	std::string culture_ = "no_culture";
	int size_ = 0;
	double literacy_ = 0.0;
	double militancy_ = 0.0;

	std::map<std::string, float> popIssues_;
};

} // namespace Vic2



#endif // VIC2_POP_H_