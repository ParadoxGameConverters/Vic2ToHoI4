#include "AdjustedBranch.h"
#include "src/HOI4World/Characters/CharacterFactory.h"
#include "src/HOI4World/Characters/CharactersFactory.h"
#include "src/HOI4World/FocusTrees/FocusTreeFactory.h"
#include "src/HOI4World/HoI4Focus.h"
#include "src/HOI4World/Ideas/IdeaUpdaters.h"
#include "src/HOI4World/Ideas/IdeasFactory.h"



HoI4::AdjustedBranch::AdjustedBranch(const std::string& name):
	 name_(name), path_(std::filesystem::path("Configurables/AdjustedFocusBranches") / name)
{
	importFocuses();
	importIdeas();
	importCharacters();
}

void HoI4::AdjustedBranch::importFocuses()
{
	const auto& filePath = std::filesystem::path(path_.string() + ".txt");
	if (!std::filesystem::exists(filePath))
	{
		Log(LogLevel::Warning) << "Couldn't load " << filePath.string();
		return;
	}

	focusTree_ = HoI4FocusTree::Factory().importFocusTree(filePath);
}

void HoI4::AdjustedBranch::importIdeas()
{
	const auto& filePath = std::filesystem::path(path_.string() + "_ideas.txt");
	if (!std::filesystem::exists(filePath))
	{
		return;
	}

	ideas_ = HoI4::Ideas::Factory().importIdeas(filePath);
}

void HoI4::AdjustedBranch::importCharacters()
{
	const auto& filePath = std::filesystem::path(path_.string() + "_characters.txt");
	if (!std::filesystem::exists(filePath))
	{
		return;
	}

	HoI4::Character::Factory characterFactory;
	CharactersFactory charactersFactory(characterFactory);
	characters_ = charactersFactory.importCharacters(filePath);
}

void HoI4::AdjustedBranch::updateUKColonialFocuses(const std::set<std::string>& majorIdeologies)
{
	for (auto focus: focusTree_.getFocuses())
	{
		if (focus->id == "uk_colonial_focus")
		{
			focus->updateFocusElement(focus->available,
				 "#NOT_COMMUNISM",
				 "NOT = { has_government = communism }",
				 majorIdeologies.contains("communism"));
		}

		if (focus->id == "uk_sanction_japan_focus")
		{
			focus->updateFocusElement(focus->available,
				 "#DEMOCRATIC",
				 "has_government = democratic",
				 majorIdeologies.contains("democratic"));
		}

		if (focus->id == "ENG_war_with_japan")
		{
			focus->updateFocusElement(focus->available,
				 "#DEMOCRATIC",
				 "has_government = democratic",
				 majorIdeologies.contains("democratic"));
		}

		if (focus->id == "uk_china_focus")
		{
			focus->updateFocusElement(focus->available,
				 "#DEMOCRATIC",
				 "has_government = democratic",
				 majorIdeologies.contains("democratic"));
			focus->updateFocusElement(focus->completionReward,
				 "#NOT_DEMOCRATIC",
				 "NOT = { has_government = democratic }",
				 majorIdeologies.contains("democratic"));
			focus->updateFocusElement(focus->completionReward,
				 "#ADD_DEMOCRATIC_INFLUENCE_IDEA",
				 "add_timed_idea = { idea = democratic_influence days = 1095 }",
				 majorIdeologies.contains("democratic"));
		}

		if (focus->id == "uk_free_india_focus")
		{
			focus->updateFocusElement(focus->available,
				 "#NOT_DEMOCRATIC",
				 "NOT = { has_government = democratic }",
				 majorIdeologies.contains("democratic"));
			focus->updateFocusElement(focus->available,
				 "#DEMOCRATIC",
				 "has_government = democratic",
				 majorIdeologies.contains("democratic"));
		}
	}
}