#include "OutCountryLeaderData.h"



std::ostream& HoI4::operator<<(std::ostream& out, const CountryLeaderData& countryLeaderData)
{
	out << "\t\tcountry_leader={\n";
	out << "\t\t\tideology=" << countryLeaderData.getIdeology() << "\n";
	if (!countryLeaderData.getTraits().empty())
	{
		out << "\t\t\ttraits={ ";
		for (const auto& trait: countryLeaderData.getTraits())
		{
			out << trait << " ";
		}
		out << "}\n";
	}
	out << "\t\t\texpire=\"1965.1.1.1\"\n";
	out << "\t\t\tid=-1\n";
	out << "\t\t}\n";

	return out;
}