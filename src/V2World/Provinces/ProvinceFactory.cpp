#include "src/V2World/Provinces/ProvinceFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include <ranges>



Vic2::Province::Factory::Factory(std::unique_ptr<PopFactory>&& _popFactory): popFactory(std::move(_popFactory))
{
	registerKeyword("owner", [this](std::istream& theStream) {
		province->owner = commonItems::singleString(theStream).getString();
	});
	registerKeyword("core", [this](std::istream& theStream) {
		province->cores.insert(commonItems::singleString(theStream).getString());
	});
	registerKeyword("controller", [this](std::istream& theStream) {
		province->controller = commonItems::singleString(theStream).getString();
	});
	registerKeyword("naval_base", [this](std::istream& theStream) {
		province->navalBaseLevel = static_cast<int>(commonItems::doubleList(theStream).getDoubles()[0]);
	});
	registerKeyword("railroad", [this](std::istream& theStream) {
		province->railLevel = static_cast<int>(commonItems::doubleList(theStream).getDoubles()[0]);
	});
	registerRegex(
		 "aristocrats|artisans|bureaucrats|capitalists|clergymen|craftsmen|clerks|farmers|soldiers|officers|labourers|"
		 "slaves|serfs",
		 [this](const std::string& popType, std::istream& theStream) {
			 province->pops.push_back(popFactory->getPop(popType, theStream));
		 });
	registerKeyword("flags", [this](std::istream& theStream) {
		const auto assignments = commonItems::assignments(theStream).getAssignments();
		for (const auto& flag: assignments | std::views::keys)
		{
			province->flags.insert(flag);
		}
	});
	registerKeyword("life_rating", [this](std::istream& theStream) {
		province->landProvince_ = true;
		const auto unused = commonItems::getInt(theStream);
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