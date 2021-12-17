#include "CharacterFactory.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"



HoI4::Character HoI4::Character::Factory::createNewCountryLeader(const std::string& tag,
	 const std::pair<std::string, std::string>& nextMonarch,
	 const std::string& primaryCulture,
	 const std::string& primaryCultureGroup,
	 const std::string& governmentIdeology,
	 const std::string& leaderIdeology,
	 Names& names,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Localisation& localisation)
{
	Character leader;
	leader.leader_ideology_ = leaderIdeology;
	leader.portraits_.emplace_back(Portrait("civilian",
		 "large",
		 graphicsMapper.getLeaderPortrait(primaryCulture, primaryCultureGroup, governmentIdeology)));

	const auto firstName = names.getMaleName(primaryCulture);
	const auto surname = names.getSurname(primaryCulture);

	if (!firstName || !surname)
	{
		Log(LogLevel::Warning) << "Could not set leader, as there were no names for " << primaryCulture << ".";
		return leader;
	}

	leader.name_ = *firstName + " " + *surname;

	if (const auto& [regnalName, regnalNumber] = nextMonarch; !regnalName.empty())
	{
		if (!regnalNumber.empty())
		{
			leader.name_ = "King " + regnalName + " " + regnalNumber;
		}
		else
		{
			leader.name_ = "King " + *firstName;
		}
	}

	leader.id_ = commonItems::convertUTF8ToASCII(leader.name_);
	std::ranges::transform(leader.id_, leader.id_.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	std::ranges::transform(leader.id_, leader.id_.begin(), [](unsigned char c) {
		return c == ' ' ? '_' : c;
	});
	leader.id_ = tag + "_" + leader.id_;
	localisation.addCharacterLocalisation(leader.id_, leader.name_);

	return leader;
}