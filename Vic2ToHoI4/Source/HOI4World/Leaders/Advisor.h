#ifndef HOI4_ADVISOR_H
#define HOI4_ADVISOR_H



#include "Parser.h"
#include <string>
#include <vector>



namespace HoI4
{

class Advisor: commonItems::parser
{
  public:
	explicit Advisor(std::string ideology, std::istream& theStream);

	[[nodiscard]] const std::vector<std::string>& getTraits() const { return traits; }
	[[nodiscard]] const std::string& getPicture() const { return picture; }
	[[nodiscard]] const std::string& getIdeology() const { return ideology; }

	bool operator<(const Advisor& rhs) const { return ideology < rhs.getIdeology(); }

  private:
	std::vector<std::string> traits;
	std::string picture = "";
	std::string ideology = "";
};

} // namespace HoI4



#endif // HOI4_ADVISOR_H