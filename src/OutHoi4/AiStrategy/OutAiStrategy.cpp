#include "src/OutHoi4/AiStrategy/OutAiStrategy.h"
#include "external/common_items/CommonFunctions.h"
#include "src/HOI4World/HoI4Country.h"



void HoI4::outputAIStrategy(const HoI4::Country& theCountry, const std::string& outputName)
{
	std::ofstream output("output/" + outputName + "/common/ai_strategy/converted_" + theCountry.getTag() + ".txt");
	if (!output.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + outputName + "/common/ai_strategy/converted_" + theCountry.getTag() + ".txt");
	}
	output << commonItems::utf8BOM; // add the BOM to make HoI4 happy

	output << "converted_war_strategies_" << theCountry.getTag() << " = {\n";
	output << "\tenable = {\n";
	output << "\t\ttag = " + theCountry.getTag() + "\n";
	output << "\t\talways = no\n";
	output << "\t}\n";
	output << "\t\n";
	for (const auto& conquerStr: theCountry.getConquerStrategies())
	{
		output << "\tai_strategy = {\n";
		output << "\t\ttype = " << conquerStr.getType() << "\n";
		output << "\t\tid = \"" << conquerStr.getID() << "\"\n";
		output << "\t\tvalue = " << conquerStr.getValue() << "\n";
		output << "\t}\n";
	}
	output << "}\n";
	output << "\n";

	output << "converted_diplo_strategies_" << theCountry.getTag() << " = {\n";
	output << "\tenable = {\n";
	output << "\t\ttag = " + theCountry.getTag() + "\n";
	output << "\t\talways = no\n";
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
