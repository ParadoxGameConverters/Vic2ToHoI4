#include "DecisionOutputter.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const decision& outDecision)
{
	outStream << "\n\t" << outDecision.name << " = {\n";
	if (!outDecision.icon.empty())
	{
		outStream << "\n\t\ticon = " << outDecision.icon << "\n";
	}
	if (!outDecision.isGood.empty())
	{
		outStream << "\n\t\tis_good = " << outDecision.isGood << "\n";
	}
	if (!outDecision.allowed.empty())
	{
		outStream << "\n\t\tallowed " << outDecision.allowed << "\n";
	}
	if (!outDecision.highlightStates.empty())
	{
		outStream << "\n\t\thighlight_states " << outDecision.highlightStates << "\n";
	}
	if (!outDecision.available.empty())
	{
		outStream << "\n\t\tavailable " << outDecision.available << "\n";
	}
	if (outDecision.daysMissionTimeout)
	{
		outStream << "\n\t\tdays_mission_timeout = " << *outDecision.daysMissionTimeout << "\n";
	}
	if (!outDecision.activation.empty())
	{
		outStream << "\n\t\tactivation " << outDecision.activation << "\n";
	}
	if (!outDecision.targets.empty())
	{
		outStream << "\n\t\ttargets " << outDecision.targets << "\n";
	}
	if (!outDecision.targetArray.empty())
	{
		outStream << "\n\t\ttarget_array " << outDecision.targetArray << "\n";
	}
	if (!outDecision.targetRootTrigger.empty())
	{
		outStream << "\n\t\ttarget_root_trigger " << outDecision.targetRootTrigger << "\n";
	}
	if (!outDecision.targetTrigger.empty())
	{
		outStream << "\n\t\ttarget_trigger " << outDecision.targetTrigger << "\n";
	}
	if (!outDecision.visible.empty())
	{
		outStream << "\n\t\tvisible " << outDecision.visible << "\n";
	}
	if (!outDecision.cancelTrigger.empty())
	{
		outStream << "\n\t\tcancel_trigger " << outDecision.cancelTrigger << "\n";
	}
	if (!outDecision.removeTrigger.empty())
	{
		outStream << "\n\t\tremove_trigger " << outDecision.removeTrigger << "\n";
	}
	if (!outDecision.customCostTrigger.empty())
	{
		outStream << "\n\t\tcustom_cost_trigger " << outDecision.customCostTrigger << "\n";
	}
	if (!outDecision.customCostText.empty())
	{
		outStream << "\n\t\tcustom_cost_text " << outDecision.customCostText << "\n";
	}
	if (!outDecision.fireOnlyOnce.empty())
	{
		outStream << "\n\t\tfire_only_once = " << outDecision.fireOnlyOnce << "\n";
	}
	if (!outDecision.modifier.empty())
	{
		outStream << "\n\t\tmodifier " << outDecision.modifier << "\n";
	}
	if (outDecision.daysRemove)
	{
		outStream << "\n\t\tdays_remove = " << *outDecision.daysRemove << "\n";
	}
	if (outDecision.daysReEnable)
	{
		outStream << "\t\tdays_re_enable = " << *outDecision.daysReEnable << "\n";
	}
	if (outDecision.cost)
	{
		outStream << "\n\t\tcost = " << *outDecision.cost << "\n";
	}
	if (!outDecision.completeEffect.empty())
	{
		outStream << "\n\t\tcomplete_effect " << outDecision.completeEffect << "\n";
	}
	if (!outDecision.targetedModifier.empty())
	{
		outStream << "\n\t\ttargeted_modifier " << outDecision.targetedModifier << "\n";
	}
	if (!outDecision.removeEffect.empty())
	{
		outStream << "\n\t\tremove_effect " << outDecision.removeEffect << "\n";
	}
	if (!outDecision.timeoutEffect.empty())
	{
		outStream << "\n\t\ttimeout_effect " << outDecision.timeoutEffect << "\n";
	}
	if (!outDecision.aiWillDo.empty())
	{
		outStream << "\n\t\tai_will_do " << outDecision.aiWillDo << "\n";
	}

	outStream << "\t}";

	return outStream;
}