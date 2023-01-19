#include "src/OutHoi4/Leaders/OutAdvisor.h"



void HoI4::outputAdvisor(std::ostream& output, const Advisor& theAdvisor)
{
	output << "every_possible_country = {\n";
	output << "\tlimit = {\n";
	output << "\t\tis_dynamic_country = no\n";
	if (!theAdvisor.getTraits().empty())
	{
		output << "\t\tNOT = {\n";
		output << "\t\t\thas_allowed_idea_with_traits = { idea = " << theAdvisor.getTraits()[0]
				 << " characters = yes }\n";
		output << "\t\t}\n";
		output << "\t}\n";
	}
	output << "\tgenerate_character = {\n";
	output << "\t\ttoken_base = generic_" << theAdvisor.getIdeology() << "_advisor # token will be TAG_token_base\n";
	output << "\t\tadvisor = {\n";
	output << "\t\t\tslot = political_advisor\n";
	if (!theAdvisor.getTraits().empty())
	{
		output << "\t\t\ttraits = { ";
		for (const auto& trait: theAdvisor.getTraits())
		{
			output << trait << ' ';
		}
		output << "}\n";
	}
	output << "\t\t\tavailable = {\n";
	output << "\t\t\t\tif = {\n";
	output << "\t\t\t\t\tlimit = { has_dlc = \"Man the Guns\" }\t\n";
	output << "\t\t\t\t\tNOT = { has_autonomy_state = autonomy_supervised_state }\n";
	output << "\t\t\t\t}\n";
	output << "\t\t\t}\n";
	output << "\t\t\tai_will_do = {\n";
	output << "\t\t\t\tfactor = 0\n";
	output << "\t\t\t}\n";
	output << "\t\t}\n";
	output << "\t\tportraits = { \n";
	output << "\t\t\tarmy = { small = " << theAdvisor.getPicture() << " }\n";
	output << "\t\t}\n";
	output << "\t}\n";
	output << "}\n";
}