#ifndef CASUS_BELLIS
#define CASUS_BELLIS



#include <string>
#include <unordered_map>


namespace Mappers
{

class CasusBellis
{
  public:
	CasusBellis(std::unordered_map<std::string, std::string> casusBelliToWarGoalMap):
		 casusBelliToWarGoalMap_(std::move(casusBelliToWarGoalMap))
	{
	}

	[[nodiscard]] std::string getWarGoalFromCasusBelli(const std::string& casusBelli) const;

  private:
	std::unordered_map<std::string, std::string> casusBelliToWarGoalMap_;
};

} // namespace Mappers



#endif // CASUS_BELLIS