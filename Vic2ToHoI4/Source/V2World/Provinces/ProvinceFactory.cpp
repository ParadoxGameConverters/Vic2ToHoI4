#include "ProvinceFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::Province::Factory::Factory(std::unique_ptr<Pop::Factory>&& _popFactory): popFactory(std::move(_popFactory))
{
	registerKeyword("owner", [this](const std::string& unused, std::istream& theStream) {
		province->owner = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("core", [this](const std::string& unused, std::istream& theStream) {
		province->cores.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("controller", [this](const std::string& unused, std::istream& theStream) {
		province->controller = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("naval_base", [this](const std::string& unused, std::istream& theStream) {
		province->navalBaseLevel = static_cast<int>(commonItems::doubleList{theStream}.getDoubles()[0]);
	});
	registerKeyword("railroad", [this](const std::string& unused, std::istream& theStream) {
		province->railLevel = static_cast<int>(commonItems::doubleList{theStream}.getDoubles()[0]);
	});
	registerRegex(
		 "aristocrats|artisans|bureaucrats|capitalists|clergymen|craftsmen|clerks|farmers|soldiers|officers|labourers|"
		 "slaves|serfs",
		 [this](const std::string& popType, std::istream& theStream) {
			 province->pops.push_back(*popFactory->getPop(popType, theStream));
		 });
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Province> Vic2::Province::Factory::getProvince(int number, std::istream& theStream)
{
	province = std::make_unique<Province>();
	province->number = number;

	parseStream(theStream);

	return std::move(province);
}