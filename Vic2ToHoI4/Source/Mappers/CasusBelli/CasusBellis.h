#ifndef CASUS_BELLIS
#define CASUS_BELLIS



#include <string>



namespace Mappers
{

class CasusBellis
{
  public:
	CasusBellis() = default;

	[[nodiscard]] std::string getWarGoalFromCasusBelli(const std::string& casusBelli) const;
};

} // namespace Mappers



#endif // CASUS_BELLIS