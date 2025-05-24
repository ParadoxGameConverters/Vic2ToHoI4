#include "src/OutHoi4/Characters/OutAdvisorData.h"



std::ostream& HoI4::operator<<(std::ostream& out, const AdvisorData& advisor_data)
{
	out << "\t\tadvisor={\n";
	out << "\t\t\tslot = " << advisor_data.getSlot() << "\n";
	out << "\t\t\tidea_token = " << advisor_data.getIdeaToken() << "\n";
	if (const auto& name = advisor_data.getName(); name.has_value())
	{
		out << "\t\t\tname = \"" << *name << "\"\n";
	}
	if (!advisor_data.getCanBeFired())
	{
		out << "\t\t\tcan_be_fired = no\n";
	}
	if (const auto& ledger = advisor_data.getLedger(); ledger.has_value())
	{
		out << "\t\t\tledger = " << *ledger << "\n";
	}
	if (const auto& available = advisor_data.getAvailable(); available.has_value())
	{
		out << "\t\t\tavailable = " << *available << "\n";
	}
	if (const auto& allowed = advisor_data.getAllowed(); allowed.has_value())
	{
		out << "\t\t\tallowed = " << *allowed << "\n";
	}
	if (const auto& visible = advisor_data.getVisible(); visible.has_value())
	{
		out << "\t\t\tvisible = " << *visible << "\n";
	}
	if (const auto& research_bonus = advisor_data.getResearchBonus(); research_bonus.has_value())
	{
		out << "\t\t\tresearch_bonus = " << *research_bonus << "\n";
	}
	if (!advisor_data.getTraits().empty())
	{
		out << "\t\t\ttraits = {\n";
		for (const auto& trait: advisor_data.getTraits())
		{
			out << "\t\t\t\t" << trait << "\n";
		}
		out << "\t\t\t}\n";
	}
	if (const auto& cost = advisor_data.getCost(); cost.has_value())
	{
		out << "\t\t\tcost = " << *cost << "\n";
	}
	if (const auto& do_effect = advisor_data.getDoEffect(); do_effect.has_value())
	{
		out << "\t\t\tdo_effect = " << *do_effect << "\n";
	}
	if (const auto& ai_will_do = advisor_data.getAiWillDo(); ai_will_do.has_value())
	{
		out << "\t\t\tai_will_do = " << *ai_will_do << "\n";
	}
	if (const auto& on_add = advisor_data.getOnAdd(); on_add.has_value())
	{
		out << "\t\t\ton_add = " << *on_add << "\n";
	}
	if (const auto& on_remove = advisor_data.getOnRemove(); on_remove.has_value())
	{
		out << "\t\t\ton_remove = " << *on_remove << "\n";
	}
	out << "\t\t}\n";

	return out;
}