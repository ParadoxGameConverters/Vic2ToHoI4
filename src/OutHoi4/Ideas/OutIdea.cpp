#include "OutIdea.h"
#include "src/HOI4World/Ideas/Idea.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const Idea& outIdea)
{
	outStream << "\t\t" << outIdea.name << " = {\n";
	if (!outIdea.altName.empty())
	{
		outStream << "\t\t\tname = " << outIdea.altName << "\n";
	}
	if (!outIdea.ledger.empty())
	{
		outStream << "\t\t\tledger = " << outIdea.ledger << "\n";
	}
	if (outIdea.cost)
	{
		outStream << "\t\t\tcost = " << *outIdea.cost << "\n";
	}
	if (outIdea.removalCost)
	{
		outStream << "\t\t\tremoval_cost = " << *outIdea.removalCost << "\n";
	}
	if (outIdea.level)
	{
		outStream << "\t\t\tlevel = " << *outIdea.level << "\n";
	}
	if (!outIdea.allowed.empty())
	{
		outStream << "\t\t\tallowed " << outIdea.allowed << "\n";
	}
	if (!outIdea.allowedCivilWar.empty())
	{
		outStream << "\t\t\tallowed_civil_war " << outIdea.allowedCivilWar << "\n";
	}
	if (outIdea.visible)
	{
		outStream << "\t\t\tvisible " << *outIdea.visible << "\n";
	}
	if (!outIdea.cancel.empty())
	{
		outStream << "\t\t\tcancel " << outIdea.cancel << "\n";
	}
	if (!outIdea.available.empty())
	{
		outStream << "\t\t\tavailable " << outIdea.available << "\n";
	}
	if (!outIdea.aiWillDo.empty())
	{
		outStream << "\t\t\tai_will_do " << outIdea.aiWillDo << "\n";
	}
	if (!outIdea.picture.empty())
	{
		outStream << "\t\t\tpicture " << outIdea.picture << "\n";
	}
	if (!outIdea.rule.empty())
	{
		outStream << "\t\t\trule " << outIdea.rule << "\n";
	}
	if (!outIdea.modifier.empty())
	{
		outStream << "\t\t\tmodifier " << outIdea.modifier << "\n";
	}
	if (!outIdea.researchBonus.empty())
	{
		outStream << "\t\t\tresearch_bonus " << outIdea.researchBonus << "\n";
	}
	if (!outIdea.equipmentBonus.empty())
	{
		outStream << "\t\t\tequipment_bonus " << outIdea.equipmentBonus << "\n";
	}
	if (!outIdea.traits.empty())
	{
		outStream << "\t\t\ttraits " << outIdea.traits << "\n";
	}
	if (!outIdea.onAdd.empty())
	{
		outStream << "\t\t\ton_add " << outIdea.onAdd << "\n";
	}
	if (!outIdea.allowedToRemove.empty())
	{
		outStream << "\t\t\tallowed_to_remove " << outIdea.allowedToRemove << "\n";
	}
	if (outIdea.isDefault)
	{
		outStream << "\t\t\tdefault = yes\n";
	}
	if (outIdea.cancelIfInvalid)
	{
		if (*outIdea.cancelIfInvalid)
		{
			outStream << "\t\t\tcancel_if_invalid = yes\n";
		}
		else
		{
			outStream << "\t\t\tcancel_if_invalid = no\n";
		}
	}
	outStream << "\t\t}\n";

	return outStream;
}