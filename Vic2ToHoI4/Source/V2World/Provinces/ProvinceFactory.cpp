#include "ProvinceFactory.h"
#include "ParserHelpers.h"



 Vic2::Province::Factory::Factory(Vic2::Pop::Factory& popFactory): popFactory(popFactory)
{
	 registerKeyword("owner", [this](const std::string& unused, std::istream& theStream) {
		 commonItems::singleString ownerSingleString(theStream);
		province->owner = ownerSingleString.getString();
	 });
	 registerKeyword("core", [this](const std::string& unused, std::istream& theStream) {
		 commonItems::singleString coreString(theStream);
		 auto newCoreString = coreString.getString();
		 province->cores.insert(newCoreString);
	 });
	 registerKeyword("controller", [this](const std::string& unused, std::istream& theStream) {
		 commonItems::singleString controllerSingleString(theStream);
		 province->controller = controllerSingleString.getString();
	 });
	 registerKeyword("naval_base", [this](const std::string& unused, std::istream& theStream) {
		 commonItems::doubleList navalBaseSizeList(theStream);
		 province->navalBaseLevel = static_cast<int>(navalBaseSizeList.getDoubles()[0]);
	 });
	 registerKeyword("railroad", [this](const std::string& unused, std::istream& theStream) {
		 commonItems::doubleList railSizeList(theStream);
		 province->railLevel = static_cast<int>(railSizeList.getDoubles()[0]);
	 });
	 registerRegex(
		  "aristocrats|artisans|bureaucrats|capitalists|clergymen|craftsmen|clerks|farmers|soldiers|officers|labourers|"
		  "slaves|serfs",
		  [this, &popFactory](const std::string& popType, std::istream& theStream) {
			  province->pops.push_back(*popFactory.getPop(popType, theStream));
		  });
	 registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
 }


std::unique_ptr<Vic2::Province> Vic2::Province::Factory::getProvince(const std::string& numberString,
	 std::istream& theStream)
{
	province = std::make_unique<Province>();
	province->number = stoi(numberString);

 	parseStream(theStream);

 	return std::move(province);
}