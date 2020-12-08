#ifndef COUNTRY_BUILDER_H
#define COUNTRY_BUILDER_H



#include "Country.h"
#include <memory>



namespace Vic2
{

class Country::Builder
{
  public:
	Builder() { country = std::make_unique<Country>(); }
	std::unique_ptr<Country> Build() { return std::move(country); }

	Builder& addNameInLanguage(const std::string& language, const std::string& name)
	{
		country->namesByLanguage.insert(std::make_pair(language, name));
		return *this;
	}

	Builder& setHuman()
	{
		country->human = true;
		return *this;
	}

	Builder& setColor(const commonItems::Color& color)
	{
		country->color = color;
		return *this;
	}

	Builder& setCapital(int capital)
	{
		country->capital = capital;
		return *this;
	}

	Builder& setRulingParty(const Party& rulingParty)
	{
		country->rulingParty = rulingParty;
		return *this;
	}

	Builder& addActiveParty(const Party& party)
	{
		country->activeParties.insert(party);
		return *this;
	}

	Builder& setUpperHouseComposition(const std::map<std::string, double>& upperHouseComposition)
	{
		country->upperHouseComposition = upperHouseComposition;
		return *this;
	}

	Builder& setLastElection(const date& lastElection)
	{
		country->lastElection = lastElection;
		return *this;
	}

	Builder& setRevanchism(double revanchism)
	{
		country->revanchism = revanchism;
		return *this;
	}

	Builder& setWarExhaustion(double warExhaustion)
	{
		country->warExhaustion = warExhaustion;
		return *this;
	}

	Builder& setAtWar(bool atWar)
	{
		country->atWar = atWar;
		return *this;
	}

	Builder& addTechOrInvention(const std::string& tech)
	{
		country->technologiesAndInventions.insert(tech);
		return *this;
	}

	Builder& addProvince(int provinceNum, std::shared_ptr<Province> province)
	{
		country->provinces.insert(std::make_pair(provinceNum, province));
		return *this;
	}

	Builder& setGovernment(const std::string& government)
	{
		country->government = government;
		return *this;
	}

  private:
	std::unique_ptr<Country> country;
};

} // namespace Vic2



#endif // COUNTRY_BUILDER_H