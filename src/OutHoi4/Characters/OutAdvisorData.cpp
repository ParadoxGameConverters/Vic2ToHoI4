#include "OutAdvisorData.h"



std::ostream& HoI4::operator<<(std::ostream& out, const AdvisorData& advisor_data)
{
	out << "\t\tadvisor={\n";
	out << "\t\t\tslot = " << advisor_data.getSlot() << "\n";
	out << "\t\t\tidea_token = " << advisor_data.getIdeaToken() << "\n";
	if (const auto& ledger = advisor_data.getLedger(); ledger.has_value())
	{
		out << "\t\t\tledger = " << *ledger << "\n";
	}
	if (const auto& available = advisor_data.getAvailable(); available.has_value())
	{
		out << "\t\t\tavailable = " << *available << "\n";
	}
	out << "\t\t\tallowed = " << advisor_data.getAllowed() << "\n";
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
	out << "\t\t}\n";

	return out;
}