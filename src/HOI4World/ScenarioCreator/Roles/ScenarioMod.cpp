#include "src/HOI4World/ScenarioCreator/Roles/ScenarioMod.h"
#include "external/common_items/Log.h"

void ScenarioMod::AddDecisionInCategory(HoI4::decision decision, const std::string category)
{
	decisions_.at(category).addDecision(decision);
}

void ScenarioMod::AddDecisionsInCategory(HoI4::DecisionsInCategory decisions, const std::string category)
{
	decisions_.emplace(category, decisions);
}

void ScenarioMod::AddDecisionCategory(const HoI4::DecisionsCategory& decision_category)
{
	decision_categories_->addCategory(decision_category);
}

void ScenarioMod::AddEvent(const HoI4::Event& hoi4_event)
{
	events_.push_back(hoi4_event);
}

std::vector<std::stringstream> ScenarioMod::ParsableStreamsFromTemplate(
	 const std::vector<std::string>& template_strings,
	 const std::map<std::string, std::vector<std::string>>& delimiter_to_insertions)
{
	std::vector<std::stringstream> the_streams;

	for (auto buffer: template_strings)
	{
		for (const auto& instruction: delimiter_to_insertions)
		{
			auto& delimiter = instruction.first;
			auto& insertions = instruction.second;

			if (auto insert_position = buffer.find(delimiter); insert_position != std::string::npos)
			{
				insert_position += delimiter.size();

				for (auto& insertion: insertions)
				{
					buffer.insert(insert_position, insertion);
				}
				buffer = std::regex_replace(buffer, std::regex(delimiter), "");

				std::stringstream input_stream;
				input_stream << buffer;

				the_streams.push_back(std::move(input_stream));
			}
			else
			{
				Log(LogLevel::Warning) << "Couldn't find delimiter : " << delimiter << " in buffer " << buffer.substr(0, 16)
											  << "...";
			}
		}
	}

	return the_streams;
}
