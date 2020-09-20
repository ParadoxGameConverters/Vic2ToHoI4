#ifndef OPERATION_H
#define OPERATION_H



#include <optional>
#include <string>
#include <vector>



namespace HoI4
{

class Operation
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getIcon() const { return icon; }
	[[nodiscard]] const auto& getPriority() const { return priority; }
	[[nodiscard]] const auto& getPreventCapturedOperativeToDie() const { return preventCapturedOperativeToDie; }
	[[nodiscard]] const auto& getDays() const { return days; }
	[[nodiscard]] const auto& getNetworkStrength() const { return networkStrength; }
	[[nodiscard]] const auto& getOperatives() const { return operatives; }
	[[nodiscard]] const auto& getVisible() const { return visible; }
	[[nodiscard]] const auto& getScaleCostIndependentOfTarget() const { return scaleCostIndependentOfTarget; }
	[[nodiscard]] const auto& getRequirements() const { return requirements; }
	[[nodiscard]] const auto& getSelectionTargetState() const { return selectionTargetState; }
	[[nodiscard]] const auto& getSelectionTarget() const { return selectionTarget; }
	[[nodiscard]] const auto& getAllowed() const { return allowed; }
	[[nodiscard]] const auto& getAvailable() const { return available; }
	[[nodiscard]] const auto& getAwardedTokens() const { return awardedTokens; }
	[[nodiscard]] const auto& getEquipment() const { return equipment; }
	[[nodiscard]] const auto& getRequiredTokens() const { return requiredTokens; }
	[[nodiscard]] const auto& getOnStart() const { return onStart; }
	[[nodiscard]] const auto& getWillLeadToWarWith() const { return willLeadToWarWith; }
	[[nodiscard]] const auto& getRiskChance() const { return riskChance; }
	[[nodiscard]] const auto& getOutcomeExtraChance() const { return outcomeExtraChance; }
	[[nodiscard]] const auto& getRiskModifiers() const { return riskModifiers; }
	[[nodiscard]] const auto& getOutcomeModifiers() const { return outcomeModifiers; }
	[[nodiscard]] const auto& getCostModifiers() const { return costModifiers; }
	[[nodiscard]] const auto& getExperience() const { return experience; }
	[[nodiscard]] const auto& getCostMultiplier() const { return costMultiplier; }
	[[nodiscard]] const auto& getOutcomeExecute() const { return outcomeExecute; }
	[[nodiscard]] const auto& getOutcomeExtraExecute() const { return outcomeExtraExecute; }
	[[nodiscard]] const auto& getOutcomePotential() const { return outcomePotential; }
	[[nodiscard]] const auto& getTargetWeight() const { return targetWeight; }
	[[nodiscard]] const auto& getPhases() const { return phases; }

	void setVisible(std::string newVisible) { visible = std::move(newVisible); }
	void setAvailable(std::string newAvailable) { available = std::move(newAvailable); }

  private:
	std::string name;
	std::string icon;
	int priority = 0;
	bool preventCapturedOperativeToDie = false;

	int days = 0;
	int networkStrength = 0;
	int operatives = 0;

	std::string visible;
	bool scaleCostIndependentOfTarget = false;
	std::optional<std::string> requirements;
	std::optional<std::string> selectionTargetState;
	std::optional<std::string> selectionTarget;
	std::optional<std::string> allowed;
	std::optional<std::string> available;
	std::optional<std::string> awardedTokens;
	std::string equipment;
	std::optional<std::string> requiredTokens;

	std::optional<std::string> onStart;
	bool willLeadToWarWith = false;
	float riskChance = 0.0f;
	std::optional<float> outcomeExtraChance;
	std::optional<std::string> riskModifiers;
	std::optional<std::string> outcomeModifiers;
	std::optional<std::string> costModifiers;
	std::optional<float> experience;
	std::optional<float> costMultiplier;

	std::string outcomeExecute;
	std::optional<std::string> outcomeExtraExecute;
	std::string outcomePotential;
	std::optional<std::string> targetWeight;
	std::vector<std::string> phases;
};

} // namespace HoI4



#endif // OPERATION_H