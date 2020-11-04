#include "CountryLeaderFactory.h"
#include "Log.h"



HoI4::CountryLeader HoI4::CountryLeader::Factory::createNewLeader(const std::string& primaryCulture,
	 const std::string& primaryCultureGroup,
	 const std::string& governmentIdeology,
	 const std::string& leaderIdeology,
	 Names* names,
	 graphicsMapper* theGraphics)
{
	CountryLeader leader;

	const auto firstName = names->getMaleName(primaryCulture);
	const auto surname = names->getSurname(primaryCulture);

	if (firstName && surname)
	{
		leader.setName(*firstName + " " + *surname);

		auto upperFirstName = *firstName;
		std::transform(upperFirstName.begin(), upperFirstName.end(), upperFirstName.begin(), toupper);
		auto upperSurname = *surname;
		std::transform(upperSurname.begin(), upperSurname.end(), upperSurname.begin(), toupper);
		leader.setDescription("POLITICS_" + upperFirstName + "_" + upperSurname + "_DESC");

		leader.setPortrait(theGraphics->getLeaderPortrait(primaryCultureGroup, governmentIdeology));
		leader.setIdeology(leaderIdeology);
	}
	else
	{
		Log(LogLevel::Warning) << "Could not set leader, as there were no names for " << primaryCulture << ".";
		leader.setName("Nomen Nescio"); // Nescio Nomen (or N.N.) literally means "I don't know the name" and is
												  // sometimes used when the name of a person is unknown
		leader.setDescription("POLITICS_NOMEN_NESCIO_DESC");
		leader.setPortrait("gfx/leaders/ENG/portrait_eng_fallen_government.dds");
		leader.setIdeology(leaderIdeology);
	}

	return leader;
}