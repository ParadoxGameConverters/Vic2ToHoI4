#include "Ideology.h"
#include "../../Color.h"
#include "IdeologyModifiers.h"
#include "ParserHelpers.h"
#include <iomanip>



HoI4::Ideology::Ideology(const std::string& _ideologyName, std::istream& theStream): ideologyName(_ideologyName)
{
	registerKeyword("types", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringsOfItemNames typesStrings(theStream);
		types = typesStrings.getStrings();
	});
	registerKeyword("dynamic_faction_names", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList namesStrings(theStream);
		dynamicFactionNames = namesStrings.getStrings();
	});
	registerKeyword("color", [this](const std::string& unused, std::istream& theStream) {
		theColor = std::make_unique<ConverterColor::Color>(theStream);
	});
	registerKeyword("war_impact_on_world_tension", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble impactNum(theStream);
		warImpactOnWorldTension = static_cast<float>(impactNum.getDouble());
	});
	registerKeyword("faction_impact_on_world_tension", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble impactNum(theStream);
		factionImpactOnWorldTension = static_cast<float>(impactNum.getDouble());
	});
	registerKeyword("rules", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto brace = getNextTokenWithoutMatching(theStream);
		auto key = getNextTokenWithoutMatching(theStream);
		while (key && (*key != "}"))
		{
			commonItems::singleString leaf(theStream);
			rules.insert(std::make_pair(*key, leaf.getString()));
			key = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword("modifiers", [this](const std::string& unused, std::istream& theStream) {
		IdeologyModifiers importedModifiers(theStream);
		modifiers = importedModifiers.takeModifiers();
	});
	registerKeyword("faction_modifiers", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto brace = getNextTokenWithoutMatching(theStream);
		auto key = getNextTokenWithoutMatching(theStream);
		while (key != "}")
		{
			commonItems::singleDouble leaf(theStream);
			factionModifiers.insert(std::make_pair(*key, static_cast<float>(leaf.getDouble())));
			key = getNextTokenWithoutMatching(theStream);
		}
	});
	registerRegex("ai_[a-z]+", [this](const std::string& aiString, std::istream& theStream) {
		AI = aiString;
		commonItems::ignoreItem(aiString, theStream);
	});
	registerRegex("can_[a-z_]+", [this](const std::string& canString, std::istream& theStream) {
		const commonItems::singleString yesNo(theStream);
		cans.insert(std::make_pair(canString, yesNo.getString()));
	});
	registerRegex("[a-zA-Z0-9]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


void HoI4::Ideology::output(std::ostream& file) const
{
	file << "\t" << ideologyName << " = {\n";
	file << "\t\n";
	outputTypes(file);
	outputDynamicFactionNames(file);
	outputTheColor(file);
	outputRules(file);
	outputOnWorldTension(file);
	outputModifiers(file);
	outputFactionModifiers(file);
	outputCans(file);
	outputAI(file);
	file << "\t}\n";
	file << "\n\n\n";
}


void HoI4::Ideology::outputTypes(std::ostream& file) const
{
	file << "\t\ttypes = {\n";
	file << "\t";
	for (const auto& type: types)
	{
		file << "\t\t\n";
		file << "\t\t\t" << type << " = {\n";
		file << "\t\t\t}\n";
	}
	file << "\t\t}\n";
	file << "\t\t\n";
}


void HoI4::Ideology::outputDynamicFactionNames(std::ostream& file) const
{
	file << "\t\tdynamic_faction_names = {\n";
	for (const auto& dynamicFactionName: dynamicFactionNames)
	{
		file << "\t\t\t\"" << dynamicFactionName << "\"\n";
	}
	file << "\t\t}\n";
	file << "\t\t\n";
}


void HoI4::Ideology::outputTheColor(std::ostream& file) const
{
	file << "\t\tcolor = { " << *theColor << " }\n";
	file << "\t\t\n";
}


void HoI4::Ideology::outputRules(std::ostream& file) const
{
	file << "\t\trules = {\n";
	for (const auto& rule: rules)
	{
		file << "\t\t\t" << rule.first << " = " << rule.second << "\n";
	}
	file << "\t\t}\n";
	file << "\t\t\n";
}


void HoI4::Ideology::outputOnWorldTension(std::ostream& file) const
{
	file << "\t\twar_impact_on_world_tension = " << warImpactOnWorldTension << "\n";
	file << "\t\tfaction_impact_on_world_tension = " << factionImpactOnWorldTension << "\n";
	file << "\t\t\n";
}


void HoI4::Ideology::outputModifiers(std::ostream& file) const
{
	file << "\t\tmodifiers = {\n";
	for (const auto& modifier: modifiers)
	{
		file << "\t\t\t" << modifier.first << " " << modifier.second << "\n";
	}
	file << "\t\t}\n";
	file << "\t\t\n";
}


void HoI4::Ideology::outputFactionModifiers(std::ostream& file) const
{
	file << "\t\tfaction_modifiers = {\n";
	for (const auto& factionModifier: factionModifiers)
	{
		file << "\t\t\t" << factionModifier.first << " = " << factionModifier.second << "\n";
	}
	file << "\t\t}\n";
}


void HoI4::Ideology::outputCans(std::ostream& file) const
{
	if (cans.size() > 0)
	{
		file << "\n";
	}
	for (const auto& can: cans)
	{
		file << "\t\t" << can.first << " = " << can.second << "\n";
	}
	if (cans.size() > 0)
	{
		file << "\n";
	}
}


void HoI4::Ideology::outputAI(std::ostream& file) const
{
	file << "\t\t" << AI << " = yes\n";
}