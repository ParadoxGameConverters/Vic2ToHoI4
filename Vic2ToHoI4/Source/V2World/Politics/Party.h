#ifndef PARTY_H
#define PARTY_H



#include <string>



namespace Vic2
{

class Party
{
  public:
	class Factory;

	[[nodiscard]] std::string getName() const { return name; }
	[[nodiscard]] std::string getIdeology() const { return ideology; }
	[[nodiscard]] std::string getWarPolicy() const { return warPolicy; }

	[[nodiscard]] bool operator==(const Party& rhs) const;
	[[nodiscard]] bool operator<(const Party& rhs) const;

  private:
	std::string name;
	std::string ideology = "conservative";
	std::string economic_policy = "interventionism";
	std::string trade_policy = "protectionism";
	std::string religious_policy = "moralism";
	std::string citizenship_policy = "residency";
	std::string warPolicy = "pro_military";
};

} // namespace Vic2



#endif // PARTY_H
