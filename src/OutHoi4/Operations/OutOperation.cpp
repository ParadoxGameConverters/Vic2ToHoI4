#include "OutOperation.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Operation& operation)
{
	out << operation.getName() << " = { ### " << operation.getPriority() << " " << operation.getOperatives() << "/"
		 << operation.getNetworkStrength() << "\n";
	out << "\ticon = " << operation.getIcon() << "\n";
	out << "\tmap_icon = " << operation.getIcon() << "_map\n";
	out << "\tname = " << operation.getName() << "\n";
	out << "\tdesc = " << operation.getName() << "_desc\n";
	out << "\tpriority = " << operation.getPriority() << "\n";
	if (operation.getPreventCapturedOperativeToDie())
	{
		out << "\tprevent_captured_operative_to_die = yes\n";
	}
	out << "\n";
	out << "\tdays = " << operation.getDays() << "\n";
	out << "\tnetwork_strength = " << operation.getNetworkStrength() << "\n";
	out << "\toperatives = " << operation.getOperatives() << "\n";
	out << "\n";
	out << "\tvisible " << operation.getVisible() << "\n";
	if (operation.getScaleCostIndependentOfTarget())
	{
		out << "\n";
		out << "\tscale_cost_independent_of_target = yes\n";
	}
	if (operation.getRequirements())
	{
		out << "\n";
		out << "\trequirements " << *operation.getRequirements() << "\n";
	}
	if (operation.getSelectionTargetState())
	{
		out << "\n";
		out << "\tselection_target_state " << *operation.getSelectionTargetState() << "\n";
	}
	if (operation.getSelectionTarget())
	{
		out << "\n";
		out << "\tselection_target " << *operation.getSelectionTarget() << "\n";
	}
	if (operation.getAllowed())
	{
		out << "\n";
		out << "\tallowed " << *operation.getAllowed() << "\n";
	}
	if (operation.getAvailable())
	{
		out << "\n";
		out << "\tavailable " << *operation.getAvailable() << "\n";
	}
	out << "\n";
	if (operation.getAwardedTokens())
	{
		out << "\tawarded_tokens " << *operation.getAwardedTokens() << "\n";
		out << "\n";
	}
	out << "\tequipment " << operation.getEquipment() << "\n";
	if (operation.getRequiredTokens())
	{
		out << "\n";
		out << "\trequired_tokens " << *operation.getRequiredTokens() << "\n";
		out << "\n";
	}
	if (operation.getOnStart())
	{
		out << "\n";
		out << "\ton_start " << *operation.getOnStart() << "\n";
	}
	if (operation.getWillLeadToWarWith())
	{
		out << "\n";
		out << "\twill_lead_to_war_with = yes\n";
	}
	out << "\trisk_chance = " << operation.getRiskChance() << "\n";
	if (operation.getOutcomeExtraChance())
	{
		out << "\toutcome_extra_chance = " << *operation.getOutcomeExtraChance() << "\n";
	}
	if (operation.getRiskModifiers())
	{
		out << "\trisk_modifiers " << *operation.getRiskModifiers() << "\n";
	}
	if (operation.getOutcomeModifiers())
	{
		out << "\toutcome_modifiers " << *operation.getOutcomeModifiers() << "\n";
	}
	if (operation.getCostModifiers())
	{
		out << "\tcost_modifiers " << *operation.getCostModifiers() << "\n";
	}
	if (operation.getExperience())
	{
		out << "\texperience = " << *operation.getExperience() << "\n";
	}
	if (operation.getCostMultiplier())
	{
		out << "\tcost_multiplier = " << *operation.getCostMultiplier() << "\n";
	}
	out << "\n";
	out << "\toutcome_execute " << operation.getOutcomeExecute() << "\n";
	if (operation.getOutcomeExtraExecute())
	{
		out << "\toutcome_extra_execute " << *operation.getOutcomeExtraExecute() << "\n";
	}
	out << "\n";
	out << "\toutcome_potential " << operation.getOutcomePotential() << "\n";
	out << "\n";
	if (operation.getTargetWeight())
	{
		out << "\ttarget_weight " << *operation.getTargetWeight() << "\n";
		out << "\n";
	}
	for (const auto& phase: operation.getPhases())
	{
		out << "\tphases " << phase << "\n";
	}

	out << "}\n";
	out << "\n";

	return out;
}