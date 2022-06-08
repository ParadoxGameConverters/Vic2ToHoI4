#include "src/HOI4World/Events/GovernmentInExileEvent.h"
#include "src/HOI4World/Events/Event.h"
#include "src/HOI4World/Events/EventHelpers.h"
#include "src/HOI4World/Events/EventOption.h"
#include "external/common_items/Log.h"


HoI4::Event HoI4::createGovernmentInExileEvent(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tCreating government in exile event";

	Event governmentInExileEvent;
	governmentInExileEvent.giveType("country_event");
	governmentInExileEvent.giveId("mtg_generic.1");
	governmentInExileEvent.giveTitle("mtg_generic.1.title");
	governmentInExileEvent.giveDescription("= mtg_generic.1.desc");
	governmentInExileEvent.givePicture("GFX_report_event_generic_parliament");
	governmentInExileEvent.setTriggeredOnly();

	EventOption option;
	option.giveName("mtg_generic.1.a");
	for (const auto& ideology: majorIdeologies)
	{
		option.giveScriptBlock(
			 "if = {\n"
			 "\t\t\tlimit = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = " +
			 ideology +
			 "\n"
			 "\t\t\t\t}\n"
			 "\t\t\t}\n"
			 "\t\t\teffect_tooltip = {\n"
			 "\t\t\t\tadd_timed_idea = {\n"
			 "\t\t\t\t\tidea = political_turmoil\n"
			 "\t\t\t\t\tdays = 365\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\tset_politics = {\n"
			 "\t\t\t\t\truling_party = " +
			 ideology +
			 "\n"
			 "\t\t\t\t\telections_allowed = " +
			 getElectionsAllowedString(ideology) +
			 "\t\t\t\t}\n"
			 "\t\t\t}\n"
			 "\t\t}");
	}
	governmentInExileEvent.giveOption(std::move(option));

	return governmentInExileEvent;
}
