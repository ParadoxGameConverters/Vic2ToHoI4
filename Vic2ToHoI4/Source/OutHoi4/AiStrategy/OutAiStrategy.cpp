#include "OutAiStrategy.h"
#include "../../HOI4World/HoI4Country.h"

void HoI4::outputAIStrategy(const HoI4::Country& theCountry, const Configuration& theConfiguration)
{
	std::ofstream output(
		 "output/" + theConfiguration.getOutputName() + "/common/ai_strategy/converted_" + theCountry.getTag() + ".txt");
	if (!output.is_open())
	{
		throw std::runtime_error("Could not open output/" + theConfiguration.getOutputName() +
										 "/common/ai_strategy/converted_" + theCountry.getTag() + ".txt");
	}
	output << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy

	output << "converted_war_strategies_" << theCountry.getTag() << " = {\n";
	output << "\tenable = {\n";
	output << "\t\talways = no\n";
	output << "\t}\n";
	output << "\t\n";
	for (const auto& conquerStr: theCountry.getConquerStrategies())
	{
		output << "\tai_strategy = {\n";
		output << "\t\ttype = " << conquerStr.second.getType() << "\n";
		output << "\t\tid = \"" << conquerStr.second.getID() << "\"\n";
		output << "\t\tvalue = " << conquerStr.second.getValue() << "\n";
		output << "\t}\n";
	}
	output << "}\n";
	output << "\n";

	output << "converted_diplo_strategies_" << theCountry.getTag() << " = {\n";
	output << "\tenable = {\n";
	output << "\t\ttag = " + theCountry.getTag() + "\n";
	output << "\t}\n";
	output << "\tabort = {\n";
	output << "\t\talways = no\n";
	output << "\t}\n";
	output << "\t\n";
	for (const auto& strategy: theCountry.getAIStrategies())
	{
		if (const auto& strategyType = strategy.getType(); strategyType != "conquer_prov")
		{
			output << "\tai_strategy = {\n";
			output << "\t\ttype = " << strategy.getType() << "\n";
			output << "\t\tid = \"" << strategy.getID() << "\"\n";
			output << "\t\tvalue = " << strategy.getValue() << "\n";
			output << "\t}\n";
		}
	}
	output << "}\n";
}
