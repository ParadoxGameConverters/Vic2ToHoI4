#include "CharacterFactory.h"
#include "CommonFunctions.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



using HoI4::Character;



Character::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& input) {
		imported_character_->name_ = commonItems::getString(input);
	});
	registerKeyword("portraits", [this](std::istream& input) {
		imported_character_->portraits_ = portraits_factory_.importPortraits(input);
	});
	registerKeyword("country_leader", [this](std::istream& input) {
		imported_character_->country_leader_data_ = country_leader_data_factory_.importCountryLeaderData(input);
	});
	registerKeyword("corps_commander", [this](const std::string& commanderType, std::istream& input) {
		imported_character_->commander_data_ = commander_data_factory_.importCommanderData(commanderType, input);
	});
	registerKeyword("field_marshal", [this](const std::string& commanderType, std::istream& input) {
		imported_character_->commander_data_ = commander_data_factory_.importCommanderData(commanderType, input);
	});
	registerKeyword("navy_leader", [this](std::istream& input) {
		imported_character_->admiral_data_ = admiral_data_factory_.importAdmiralData(input);
	});
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

	leader.portraits_.emplace_back(Portrait("civilian",
		 "large",
		 graphicsMapper.getLeaderPortrait(primaryCulture, primaryCultureGroup, governmentIdeology)));
	leader.country_leader_data_ = CountryLeaderData(leaderIdeology, {});

	return leader;
}


Character Character::Factory::createNewGeneral(const Vic2::Leader& src_general,
	 const std::string& tag,
	 Localisation& localisation)
{
	Character general;
	general.name_ = commonItems::convertWin1252ToUTF8(src_general.getName());
	general.id_ = commonItems::convertUTF8ToASCII(general.name_);
	general.id_ = determineId(general.name_, tag);
	localisation.addCharacterLocalisation(general.id_, general.name_);

	const int attack_skill =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("attack"))) + 1, 1, 7);
	const int defense_skill =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("defence"))) + 1, 1, 7);
	const int planning_skill =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("morale") * 8.0F)) + 1, 1, 5);
	const int logistics_skill =
		 std::clamp(static_cast<int>(std::round(src_general.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 5);
	const int skill = std::clamp((attack_skill + defense_skill + planning_skill + logistics_skill) / 3, 1, 5);
	general.commander_data_ = CommanderData(CommanderLevel::CorpsCommander,
		 {},
		 skill,
		 attack_skill,
		 defense_skill,
		 planning_skill,
		 logistics_skill);

	return general;
}


Character Character::Factory::createNewAdmiral(const Vic2::Leader& src_admiral,
	 const std::string& tag,
	 Localisation& localisation)
{
	Character admiral;
	admiral.name_ = commonItems::convertWin1252ToUTF8(src_admiral.getName());
	admiral.id_ = commonItems::convertUTF8ToASCII(admiral.name_);
	admiral.id_ = determineId(admiral.name_, tag);
	localisation.addCharacterLocalisation(admiral.id_, admiral.name_);

	const int attack_skill =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("attack"))) + 1, 1, 7);
	const int defense_skill =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("defence"))) + 1, 1, 7);
	const int maneuvering_skill =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("morale") * 8.0F)) + 1, 1, 7);
	const int coordination_skill =
		 std::clamp(static_cast<int>(std::round(src_admiral.getTraitEffectValue("organisation") * 25.0F)) + 1, 1, 7);
	const int skill = std::clamp((attack_skill + defense_skill + maneuvering_skill + coordination_skill) / 3, 1, 5);
	admiral.admiral_data_ = AdmiralData({}, skill, attack_skill, defense_skill, maneuvering_skill, coordination_skill);

	return admiral;
}


Character Character::Factory::importCharacter(std::string_view id, std::istream& input)
{
	imported_character_ = std::make_unique<Character>();
	imported_character_->id_ = id;
	parseStream(input);
	return *imported_character_;
}