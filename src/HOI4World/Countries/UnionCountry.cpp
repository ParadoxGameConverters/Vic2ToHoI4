#include "src/HOI4World/Countries/UnionCountry.h"



HoI4::UnionCountry::UnionCountry(const Vic2::Country& source_country, const Vic2::CultureGroups& culture_groups)
{
	const auto& source_tag = source_country.getTag();
	tag_ = source_tag + "_union";

	for (const auto& culture: culture_groups.GetUnionCultures(source_tag))
	{
		cultures_.insert(culture);
	}

	if (const auto& color = source_country.getColor(); color)
	{
		color_ = *color;
	}
}