#ifndef VIC2_WORLD_H_
#define VIC2_WORLD_H_



#include "Configuration.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Parser.h"
#include "V2World/Countries/Country.h"
#include "V2World/Diplomacy/Diplomacy.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Mods/Mod.h"
#include "V2World/Provinces/Province.h"
#include "V2World/States/StateDefinitions.h"
#include "V2World/Wars/War.h"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class World
{
  public:
	class Factory;

	World() = default;

	[[nodiscard]] std::optional<const std::shared_ptr<Province>> getProvince(int provNum) const;

	[[nodiscard]] const auto& getCountries() const { return countries; }
	[[nodiscard]] const auto& getDiplomacy() const { return diplomacy; }
	[[nodiscard]] std::vector<std::string> getGreatPowers() const { return greatPowers; }
	[[nodiscard]] auto getProvinces() const { return provinces; }
	[[nodiscard]] const auto& getStateDefinitions() const { return *theStateDefinitions; }
	[[nodiscard]] const auto& getLocalisations() const { return *theLocalisations; }

  private:
	std::map<int, std::shared_ptr<Province>> provinces;
	std::map<std::string, std::unique_ptr<Country>> countries;
	std::unique_ptr<Diplomacy> diplomacy;
	std::vector<std::string> greatPowers;

	std::unique_ptr<StateDefinitions> theStateDefinitions;
	std::unique_ptr<Localisations> theLocalisations;
};


} // namespace Vic2



#endif // VIC2_WORLD_H_