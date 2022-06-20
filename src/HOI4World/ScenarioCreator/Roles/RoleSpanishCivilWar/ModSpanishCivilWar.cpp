#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"
#include "src/HOI4World/ScenarioCreator/Utilities/ScenarioUtilities.h"
#include <sstream>

ModSpanishCivilWar::ModSpanishCivilWar(std::shared_ptr<HoI4::Country> country)
{
	SetName(country->getTag() + "_SpanishCivilWar");
}

void ModSpanishCivilWar::OutputRoleSpecifics(std::string output_name) const
{
	OutputExtraOnActions(output_name);
}

void ModSpanishCivilWar::OutputExtraOnActions(std::string output_name) const
{
	std::string buffer =
		 GetFileBufferStr("99_converter_on_actions.txt", "on_actions", "output/" + output_name + "/common");

	std::string delimiter = "on_new_term_election = {";
	const auto& pos = buffer.find(delimiter);
	std::string front = buffer.substr(0, pos);
	std::string back = buffer.substr(pos + delimiter.size());

	std::stringstream insertion;

	insertion << "\n\t\trandom_events = {";
	insertion << "\n\t\t\t100 = " + election_on_action_event_;
	insertion << "\n\t\t}";

	std::ofstream on_actions_file("output/" + output_name + "/common/on_actions/99_converter_on_actions.txt");
	if (!on_actions_file.is_open())
	{
		throw std::runtime_error("Could not recreate on_actions.txt");
	}

	on_actions_file << front + delimiter + insertion.str() + back;
	on_actions_file.close();
}
