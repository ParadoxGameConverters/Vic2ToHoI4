#include "EventsOutputter.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



void outputActualEvents(
	const std::string& eventsFileName,
	const std::string& eventNamespace,
	const std::vector<HoI4::Event>& nationalFocusEvents,
	const Configuration& theConfiguration
);
void outputWarJustificationEvents(
	const std::vector<HoI4::Event>& warJustificationEvents,
	const Configuration& theConfiguration
);
void outputStabilityEvents(
	const std::map<std::string, HoI4::Event>& stabilityEvents,
	const std::map<std::string, HoI4::Event>& strikesEvents,
	const std::map<std::string, HoI4::Event>& mutinyEvents,
	const Configuration& theConfiguration
);



void HoI4::outputEvents(const Events& theEvents, const Configuration& theConfiguration)
{
	std::string eventpath = "output/" + theConfiguration.getOutputName() + "/events";
	if (!Utils::TryCreateFolder(eventpath))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/events\"";
		exit(-1);
	}

	outputActualEvents("NF_events.txt", "NFEvents", theEvents.getNationalFocusEvents(), theConfiguration);
	outputActualEvents("newsEvents.txt", "news", theEvents.getNewsEvents(), theConfiguration);
	outputActualEvents(
		"converterPoliticalEvents.txt",
		"conv.political",
		theEvents.getPoliticalEvents(),
		theConfiguration
	);
	outputWarJustificationEvents(theEvents.getWarJustificationEvents(), theConfiguration);
	outputActualEvents("ElectionEvents.txt", "election", theEvents.getElectionsEvents(), theConfiguration);
	outputStabilityEvents(
		theEvents.getStabilityEvents(),
		theEvents.getStrikesEvents(),
		theEvents.getMutinyEvents(),
		theConfiguration
	);
}


void outputActualEvents(
	const std::string& eventsFileName,
	const std::string& eventNamespace,
	const std::vector<HoI4::Event>& events,
	const Configuration& theConfiguration
)
{
	std::ofstream outEvents("output/" + theConfiguration.getOutputName() + "/events/" + eventsFileName);
	if (!outEvents.is_open())
	{
		throw std::runtime_error("Could not create " + eventsFileName);
	}

	outEvents << "\xEF\xBB\xBF";
	outEvents << "add_namespace = " + eventNamespace + "\n";
	for (auto& theEvent: events)
	{
		outEvents << "\n";
		outEvents << theEvent;
	}

	outEvents.close();
}


void outputWarJustificationEvents(
	const std::vector<HoI4::Event>& warJustificationEvents,
	const Configuration& theConfiguration
)
{
	std::ofstream outWarJustificationEvents(
		"output/" + theConfiguration.getOutputName() + "/events/WarJustification.txt", std::ios_base::app
	);
	if (!outWarJustificationEvents.is_open())
	{
		throw std::runtime_error("Could not open WarJustification.txt");
	}

	for (auto& theEvent: warJustificationEvents)
	{
		outWarJustificationEvents << "\n";
		outWarJustificationEvents << theEvent;
	}

	outWarJustificationEvents.close();
}


void outputStabilityEvents(
	const std::map<std::string, HoI4::Event>& stabilityEvents,
	const std::map<std::string, HoI4::Event>& strikesEvents,
	const std::map<std::string, HoI4::Event>& mutinyEvents,
	const Configuration& theConfiguration
)
{
	std::ofstream outStabilityEvents("output/" + theConfiguration.getOutputName() + "/events/stability_events.txt");
	if (!outStabilityEvents.is_open())
	{
		LOG(LogLevel::Error) << "Could not open StabilityEvents.txt";
		exit(-1);
	}

	outStabilityEvents << "\xEF\xBB\xBF";    // add the BOM to make HoI4 happy

	outStabilityEvents << "###########################\n";
	outStabilityEvents << "#stability events\n";
	outStabilityEvents << "###########################\n";
	outStabilityEvents << "\n";
	outStabilityEvents << "add_namespace = stability\n";
	outStabilityEvents << "\n";

	for (auto& theEvent: stabilityEvents)
	{
		outStabilityEvents << "\n";
		outStabilityEvents << theEvent.second;
	}

	outStabilityEvents << "add_namespace = strikes_event\n";
	for (auto& theEvent: strikesEvents)
	{
		outStabilityEvents << "\n";
		outStabilityEvents << theEvent.second;
	}

	outStabilityEvents << "add_namespace = mutiny_event\n";
	for (auto& theEvent: mutinyEvents)
	{
		outStabilityEvents << "\n";
		outStabilityEvents << theEvent.second;
	}

	outStabilityEvents.close();
}
