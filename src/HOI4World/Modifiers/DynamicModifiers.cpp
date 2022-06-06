#include "DynamicModifiers.h"
#include "external/common_items/Log.h"
#include "Modifier.h"



HoI4::DynamicModifiers::DynamicModifiers()
{
	clearRegisteredKeywords();
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& modifierName, std::istream& theStream) {
		Modifier modifier(modifierName, theStream);
		dynamicModifiers.insert(make_pair(modifierName, modifier));
	});
	parseFile("configurables/converterDynamicModifiers.txt");
	clearRegisteredKeywords();
}


void HoI4::DynamicModifiers::updateDynamicModifiers(const std::set<std::string>& majorIdeologies)
{
	if (const auto& revanchismItr = dynamicModifiers.find("revanchism"); revanchismItr != dynamicModifiers.end())
	{
		auto& revanchismModifier = revanchismItr->second;
		if (majorIdeologies.contains("fascism"))
		{
			std::string newString = "= {\n";
			newString += "\t\tNOT = { has_government = fascism }\n";
			newString += "\t}";

			revanchismModifier.updateEnable(newString);
			revanchismModifier.addEffect("fascism_drift", "var:revanchism");
		}
		else
		{
			dynamicModifiers.erase("revanchism_fasc");
		}
	}
}