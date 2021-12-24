#include "CharacterFactory.h"
#include "CommonFunctions.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"



using HoI4::Character;



Character::Factory::Factory()
{
	
}



std::string Character::Factory::determineId(const std::string& name, const std::string& tag)
{
	auto id = commonItems::convertUTF8ToASCII(name);

	std::ranges::transform(id, id.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	id = normalizeStringPath(id);
	id = tag + "_" + id;

	if (used_ids_.contains(id))
	{
		int suffix = 1;
		while (used_ids_.contains(id + '_' + std::to_string(suffix)))
		{
			++suffix;
		}
		id = id + '_' + std::to_string(suffix);
	}
	used_ids_.insert(id);

	return id;
}


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

	leader.id_ = determineId(leader.name_, tag);
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

	general.id_ = determineId(general.name_, tag);
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

	admiral.id_ = determineId(admiral.name_, tag);
	localisation.addCharacterLocalisation(admiral.id_, admiral.name_);

	return admiral;
}


Character Character::Factory::importCharacter(std::istream& input)
{
	imported_character_ = std::make_unique<Character>();
	parseStream(input);
	return *imported_character_;
}