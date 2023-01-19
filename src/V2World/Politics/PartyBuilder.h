#ifndef PARTY_BUILDER_H
#define PARTY_BUILDER_H



#include "src/V2World/Politics/Party.h"
#include <memory>



namespace Vic2
{

class Party::Builder
{
  public:
	Builder() { party = std::make_unique<Party>(); }
	std::unique_ptr<Party> Build() { return std::move(party); }

	Builder& setName(const std::string& name)
	{
		party->name = name;
		return *this;
	}

	Builder& setIdeology(const std::string& ideology)
	{
		party->ideology = ideology;
		return *this;
	}

	Builder& setWarPolicy(const std::string& warPolicy)
	{
		party->warPolicy = warPolicy;
		return *this;
	}

  private:
	std::unique_ptr<Party> party;
};

} // namespace Vic2



#endif // PARTY_BUILDER_H