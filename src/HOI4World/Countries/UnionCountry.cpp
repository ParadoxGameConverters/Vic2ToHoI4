#include "src/HOI4World/Countries/UnionCountry.h"



HoI4::UnionCountry::UnionCountry(const Vic2::Country& source_country,
	 const Vic2::CultureGroups& culture_groups,
	 const Mappers::CountryMapper& country_mapper)
{
	const auto& source_tag = source_country.getTag();
	if (const auto& destination_tag = country_mapper.getHoI4Tag(source_tag); destination_tag)
	{
		tag_ = *destination_tag + "_union";
	}
	else
	{
		tag_ = source_tag + "_union";
	}

	for (const auto& culture: culture_groups.GetUnionCultures(source_tag))
	{
		cultures_.insert(culture);
	}

	if (const auto& color = source_country.getColor(); color)
	{
		color_ = *color;
	}
}
