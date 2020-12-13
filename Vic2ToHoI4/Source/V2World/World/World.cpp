#include "World.h"
#include "Configuration.h"
#include "Date.h"
#include "Log.h"
#include "Mappers/MergeRules.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "ParserHelpers.h"
#include "V2World/Ai/Vic2AI.h"
#include "V2World/Countries/CommonCountriesDataFactory.h"
#include "V2World/Countries/CommonCountryData.h"
#include "V2World/Countries/Country.h"
#include "V2World/Countries/CountryFactory.h"
#include "V2World/Culture/CultureGroupsFactory.h"
#include "V2World/Diplomacy/DiplomacyFactory.h"
#include "V2World/Issues/Issues.h"
#include "V2World/Issues/IssuesFactory.h"
#include "V2World/Localisations/LocalisationsFactory.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Pops/PopFactory.h"
#include "V2World/Provinces/Province.h"
#include "V2World/Provinces/ProvinceFactory.h"
#include "V2World/States/State.h"
#include "V2World/States/StateDefinitionsFactory.h"
#include "V2World/States/StateLanguageCategoriesFactory.h"
#include "V2World/Wars/WarFactory.h"
#include <fstream>






std::optional<const std::shared_ptr<Vic2::Province>> Vic2::World::getProvince(const int provNum) const
{
	if (const auto provinceItr = provinces.find(provNum); provinceItr != provinces.end())
	{
		return provinceItr->second;
	}
	else
	{
		return std::nullopt;
	}
}