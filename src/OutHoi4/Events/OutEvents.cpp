#include "src/OutHoi4/Events/OutEvents.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>
#include <ranges>


void outputActualEvents(const std::filesystem::path& eventsFileName,
	 const std::string& eventNamespace,
	 const std::vector<HoI4::Event>& events,
	 const std::filesystem::path& outputName);
void outputWarJustificationEvents(const std::vector<HoI4::Event>& warJustificationEvents,
	 const std::filesystem::path& outputName);
void outputStabilityEvents(const std::map<std::string, HoI4::Event>& stabilityEvents,
	 const std::map<std::string, HoI4::Event>& strikesEvents,
	 const std::map<std::string, HoI4::Event>& mutinyEvents,
	 const std::filesystem::path& outputName);
void outputGovernmentInExileDecision(const HoI4::Event& governmentInExileEvent,
	 const std::filesystem::path& outputName);



void HoI4::outputEvents(const Events& theEvents, const std::filesystem::path& outputName)
{
	const auto eventPath = "output" / outputName / "events";
	if (!commonItems::DoesFolderExist(eventPath) && !std::filesystem::create_directories(eventPath))
	{
		throw std::runtime_error("Could not create " + eventPath.string());
	}

	outputActualEvents("NF_events.txt", "NFEvents", theEvents.getNationalFocusEvents(), outputName);
	outputActualEvents("newsEvents.txt", "news", theEvents.getNewsEvents(), outputName);
	outputActualEvents("converterPoliticalEvents.txt", "conv.political", theEvents.getPoliticalEvents(), outputName);
	outputWarJustificationEvents(theEvents.getWarJustificationEvents(), outputName);
	outputActualEvents("ElectionEvents.txt", "election", theEvents.getElectionsEvents(), outputName);
	outputStabilityEvents(theEvents.getStabilityEvents(),
		 theEvents.getStrikesEvents(),
		 theEvents.getMutinyEvents(),
		 outputName);
	outputActualEvents("Generic.txt", "generic", theEvents.getGenericEvents(), outputName);
	outputGovernmentInExileDecision(theEvents.getGovernmentInExileEvent(), outputName);
	outputActualEvents("CapitulationEvents.txt", "country_capitulated", theEvents.getCapitulationEvents(), outputName);
	outputActualEvents("MTG_naval_treaty_events.txt",
		 "MTG_naval_treaty",
		 theEvents.getMtgNavalTreatyEvents(),
		 outputName);
	outputActualEvents("LAR_occupation.txt", "occupied_countries", theEvents.getLarOccupationEvents(), outputName);
}


void outputActualEvents(const std::filesystem::path& eventsFileName,
	 const std::string& eventNamespace,
	 const std::vector<HoI4::Event>& events,
	 const std::filesystem::path& outputName)
{
	const std::filesystem::path filename = "output" / outputName / "events" / eventsFileName;
	std::ofstream outEvents(filename);
	if (!outEvents.is_open())
	{
		throw std::runtime_error("Could not create " + filename.string());
	}

	outEvents << "\xEF\xBB\xBF";
	outEvents << "add_namespace = " + eventNamespace + "\n";
	for (const auto& theEvent: events)
	{
		outEvents << "\n";
		outEvents << theEvent;
	}

	outEvents.close();
}


void outputWarJustificationEvents(const std::vector<HoI4::Event>& warJustificationEvents,
	 const std::filesystem::path& outputName)
{
	const std::filesystem::path filename = "output" / outputName / "events/WarJustification.txt";
	std::ofstream outWarJustificationEvents(filename, std::ios_base::app);
	if (!outWarJustificationEvents.is_open())
	{
		throw std::runtime_error("Could not open " + filename.string());
	}

	for (const auto& theEvent: warJustificationEvents)
	{
		outWarJustificationEvents << "\n";
		outWarJustificationEvents << theEvent;
	}

	outWarJustificationEvents.close();
}


void outputStabilityEvents(const std::map<std::string, HoI4::Event>& stabilityEvents,
	 const std::map<std::string, HoI4::Event>& strikesEvents,
	 const std::map<std::string, HoI4::Event>& mutinyEvents,
	 const std::filesystem::path& outputName)
{
	const std::filesystem::path filename = "output" / outputName / "events/stability_events.txt";
	std::ofstream outStabilityEvents(filename);
	if (!outStabilityEvents.is_open())
	{
		throw std::runtime_error("Could not open " + filename.string());
	}

	outStabilityEvents << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy
	outStabilityEvents << "###########################\n";
	outStabilityEvents << "#stability events\n";
	outStabilityEvents << "###########################\n";
	outStabilityEvents << "\n";
	outStabilityEvents << "add_namespace = stability\n";
	outStabilityEvents << "\n";

	for (const auto& theEvent: stabilityEvents | std::views::values)
	{
		outStabilityEvents << "\n";
		outStabilityEvents << theEvent;
	}

	outStabilityEvents << "add_namespace = strikes_event\n";
	for (const auto& theEvent: strikesEvents | std::views::values)
	{
		outStabilityEvents << "\n";
		outStabilityEvents << theEvent;
	}

	outStabilityEvents << "add_namespace = mutiny_event\n";
	for (const auto& theEvent: mutinyEvents | std::views::values)
	{
		outStabilityEvents << "\n";
		outStabilityEvents << theEvent;
	}

	outStabilityEvents.close();
}


void outputGovernmentInExileDecision(const HoI4::Event& governmentInExileEvent, const std::filesystem::path& outputName)
{
	const std::filesystem::path filename = "output" / outputName / "events/MTG_generic.txt";
	std::ofstream outEvents(filename, std::ofstream::app);
	if (!outEvents.is_open())
	{
		throw std::runtime_error("Could not add to " + filename.string());
	}

	outEvents << governmentInExileEvent;
	outEvents.close();
}