#ifndef PARTY_H
#define PARTY_H



#include <string>



namespace Vic2
{

class Party
{
  public:
	class Factory;

	std::string getName() const { return name; }
	std::string getIdeology() const { return ideology; }
	std::string getWarPolicy() const { return warPolicy; }

  private:
	std::string name = "";
	std::string ideology = "conservative";
	std::string economic_policy = "interventionism";
	std::string trade_policy = "protectionism";
	std::string religious_policy = "moralism";
	std::string citizenship_policy = "residency";
	std::string warPolicy = "pro_military";
};

bool operator==(const Party& one, const Party& other);
bool operator<(const Party& one, const Party& other);

} // namespace Vic2



#endif // PARTY_H
