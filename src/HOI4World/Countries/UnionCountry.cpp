#include "src/HOI4World/Countries/UnionCountry.h"



HoI4::UnionCountry::UnionCountry(const Vic2::Country& source_country,
	 const Vic2::CultureGroups& culture_groups,
	 const Mappers::CountryMapper& country_mapper)
{
	old_tag_ = source_country.getTag();
	if (const auto& destination_tag = country_mapper.getHoI4Tag(old_tag_); destination_tag)
	{
		tag_ = *destination_tag + "_union";
	}
	else
	{
		tag_ = old_tag_ + "_union";
	}

	for (const auto& culture: culture_groups.GetUnionCultures(old_tag_))
	{
		cultures_.insert(culture);
	}

	if (const auto& color = source_country.getColor(); color)
	{
		color_ = *color;
	}
}
