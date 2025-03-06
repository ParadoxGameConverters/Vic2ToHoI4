#ifndef HOI4_WORLD_CHARACTERS_ADVISOR_DATA_H
#define HOI4_WORLD_CHARACTERS_ADVISOR_DATA_H



#include <map>
#include <optional>
#include <string>
#include <vector>



namespace HoI4
{

class AdvisorData
{
  public:
	AdvisorData(std::string slot,
		 std::string idea_token,
		 std::optional<std::string> ledger,
		 std::optional<std::string> available,
		 std::optional<std::string> allowed,
		 std::optional<std::string> visible,
		 std::optional<std::string> research_bonus,
		 std::vector<std::string> traits,
		 std::optional<float> cost,
		 std::optional<std::string> do_effect,
		 std::optional<std::string> ai_will_do):
		 slot_(std::move(slot)), idea_token_(std::move(idea_token)), ledger_(std::move(ledger)),
		 available_(std::move(available)), allowed_(std::move(allowed)), visible_(std::move(visible)),
		 research_bonus_(std::move(research_bonus)), traits_(std::move(traits)), cost_(std::move(cost)),
		 do_effect_(std::move(do_effect)), ai_will_do_(std::move(ai_will_do))
	{
	}

	[[nodiscard]] const auto& getSlot() const { return slot_; }
	[[nodiscard]] const auto& getIdeaToken() const { return idea_token_; }
	[[nodiscard]] const auto& getLedger() const { return ledger_; }
	[[nodiscard]] const auto& getAvailable() const { return available_; }
	[[nodiscard]] const auto& getAllowed() const { return allowed_; }
	[[nodiscard]] const auto& getVisible() const { return visible_; }
	[[nodiscard]] const auto& getResearchBonus() const { return research_bonus_; }
	[[nodiscard]] const auto& getTraits() const { return traits_; }
	[[nodiscard]] const auto& getCost() const { return cost_; }
	[[nodiscard]] const auto& getDoEffect() const { return do_effect_; }
	[[nodiscard]] const auto& getAiWillDo() const { return ai_will_do_; }

	bool operator==(const AdvisorData& rhs) const = default;

  private:
	std::string slot_;
	std::string idea_token_;
	std::optional<std::string> ledger_;
	std::optional<std::string> available_;
	std::optional<std::string> allowed_;
	std::optional<std::string> visible_;
	std::optional<std::string> research_bonus_;
	std::vector<std::string> traits_;
	std::optional<float> cost_;
	std::optional<std::string> do_effect_;
	std::optional<std::string> ai_will_do_;
};

} // namespace HoI4



#endif // HOI4_WORLD_CHARACTERS_ADVISOR_DATA_H