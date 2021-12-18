#include "CharacterFactory.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"



using HoI4::Character;



Character Character::Factory::createNewCountryLeader(const std::string& tag,
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


Character Character::Factory::createNewGeneral(const Vic2::Leader& src_general,
	 const std::string& tag,
	 Localisation& localisation)
{
	Character general;
	general.is_commander_ = true;
	general.name_ = commonItems::convertWin1252ToUTF8(src_general.getName());
	general.id_ = commonItems::convertUTF8ToASCII(general.name_);
	general.commander_attack_skill_ =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("attack"))) + 1, 1, 7);
	general.commander_defense_skill_ =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("defence"))) + 1, 1, 7);
	general.commander_planning_skill_ =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("morale") * 8.0F)) + 1, 1, 5);
	general.commander_logistics_skill_ =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 5);
	general.commander_skill_ = std::clamp((general.commander_attack_skill_ + general.commander_defense_skill_ +
															general.commander_planning_skill_ + general.commander_logistics_skill_) /
															3,
		 1,
		 5);

	general.id_ = commonItems::convertUTF8ToASCII(general.name_);
	std::ranges::transform(general.id_, general.id_.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	std::ranges::transform(general.id_, general.id_.begin(), [](unsigned char c) {
		return c == ' ' ? '_' : c;
	});
	general.id_ = tag + "_" + general.id_;
	localisation.addCharacterLocalisation(general.id_, general.name_);

	return general;
}


Character Character::Factory::createNewAdmiral(const Vic2::Leader& src_admiral,
	 const std::string& tag,
	 Localisation& localisation)
{
	Character admiral;
	admiral.is_admiral_ = true;
	admiral.name_ = commonItems::convertWin1252ToUTF8(src_admiral.getName());
	admiral.id_ = commonItems::convertUTF8ToASCII(admiral.name_);
	admiral.admiral_attack_skill_ =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("attack"))) + 1, 1, 7);
	admiral.admiral_defense_skill_ =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("defence"))) + 1, 1, 7);
	admiral.admiral_maneuvering_skill_ =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("morale") * 8.0F)) + 1, 1, 7);
	admiral.admiral_coordination_skill_ =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 7);
	admiral.admiral_skill_ = std::clamp((admiral.admiral_attack_skill_ + admiral.admiral_defense_skill_ +
														 admiral.admiral_maneuvering_skill_ + admiral.admiral_coordination_skill_) /
														 3,
		 1,
		 5);

	admiral.id_ = commonItems::convertUTF8ToASCII(admiral.name_);
	std::ranges::transform(admiral.id_, admiral.id_.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	std::ranges::transform(admiral.id_, admiral.id_.begin(), [](unsigned char c) {
		return c == ' ' ? '_' : c;
	});
	admiral.id_ = tag + "_" + admiral.id_;
	localisation.addCharacterLocalisation(admiral.id_, admiral.name_);

	return admiral;
}