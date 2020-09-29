#ifndef PARTY_H
#define PARTY_H



#include "Parser.h"



namespace Vic2
{

class Party: commonItems::parser
{
  public:
	Party() = default;
	Party(const Party&) = default;
	Party& operator=(const Party&) = default;
	Party(Party&&) = default;
	Party& operator=(Party&&) = default;
	explicit Party(std::istream& theStream);

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
