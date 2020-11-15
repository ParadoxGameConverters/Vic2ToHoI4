#ifndef PARTY_H
#define PARTY_H



#include <string>



namespace Vic2
{

class Party
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] std::string getName() const { return name; }
	[[nodiscard]] std::string getIdeology() const { return ideology; }
	[[nodiscard]] std::string getEconomicPolicy() const { return economicPolicy; }
	[[nodiscard]] std::string getTradePolicy() const { return tradePolicy; }
	[[nodiscard]] std::string getReligiousPolicy() const { return religiousPolicy; }
	[[nodiscard]] std::string getCitizenshipPolicy() const { return citizenshipPolicy; }
	[[nodiscard]] std::string getWarPolicy() const { return warPolicy; }

	[[nodiscard]] bool operator==(const Party& rhs) const;
	[[nodiscard]] bool operator<(const Party& rhs) const;

  private:
	std::string name;
	std::string ideology = "conservative";
	std::string economicPolicy = "interventionism";
	std::string tradePolicy = "protectionism";
	std::string religiousPolicy = "moralism";
	std::string citizenshipPolicy = "residency";
	std::string warPolicy = "pro_military";
};

} // namespace Vic2



#endif // PARTY_H