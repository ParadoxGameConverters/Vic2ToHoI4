#ifndef HOI4_CHARACTERS_COUNTRY_LEADER_DATA_H
#define HOI4_CHARACTERS_COUNTRY_LEADER_DATA_H



#include <string>
#include <vector>



namespace HoI4
{

class CountryLeaderData
{
  public:
	explicit CountryLeaderData(std::string ideology, std::vector<std::string> traits):
		 ideology_(std::move(ideology)), traits_(std::move(traits))
	{
	}

	[[nodiscard]] const auto& getIdeology() const { return ideology_; }
	[[nodiscard]] const auto& getTraits() const { return traits_; }

	[[nodiscard]] bool operator==(const CountryLeaderData&) const = default;

  private:
	std::string ideology_;
	std::vector<std::string> traits_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_COUNTRY_LEADER_DATA_H