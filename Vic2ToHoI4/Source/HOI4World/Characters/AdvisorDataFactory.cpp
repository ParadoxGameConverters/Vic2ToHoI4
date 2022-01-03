#include "AdvisorDataFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::AdvisorDataFactory::AdvisorDataFactory()
{
	registerKeyword("slot", [this](std::istream& input) {
		slot_ = commonItems::getString(input);
	});
	registerKeyword("idea_token", [this](std::istream& input) {
		idea_token_ = commonItems::getString(input);
	});
	registerKeyword("ledger", [this](std::istream& input) {
		ledger_ = commonItems::getString(input);
	});
	registerKeyword("available", [this](std::istream& input) {
		getNextTokenWithoutMatching(input); // remove equals
		available_ = commonItems::stringOfItem(input).getString();
	});
	registerKeyword("allowed", [this](std::istream& input) {
		getNextTokenWithoutMatching(input); // remove equals
		allowed_ = commonItems::stringOfItem(input).getString();
	});
	registerKeyword("visible", [this](std::istream& input) {
		getNextTokenWithoutMatching(input); // remove equals
		visible_ = commonItems::stringOfItem(input).getString();
	});
	registerKeyword("research_bonus", [this](std::istream& input) {
		getNextTokenWithoutMatching(input); // remove equals
		research_bonus_ = commonItems::stringOfItem(input).getString();
	});
	registerKeyword("traits", [this](std::istream& input) {
		traits_ = commonItems::getStrings(input);
	});
	registerKeyword("cost", [this](std::istream& input) {
		cost_ = static_cast<float>(commonItems::getDouble(input));
	});
	registerKeyword("do_effect", [this](std::istream& input) {
		getNextTokenWithoutMatching(input); // remove equals
		do_effect_ = commonItems::stringOfItem(input).getString();
	});
	registerKeyword("ai_will_do", [this](std::istream& input) {
		getNextTokenWithoutMatching(input); // remove equals
		ai_will_do_ = commonItems::stringOfItem(input).getString();
	});
}


HoI4::AdvisorData HoI4::AdvisorDataFactory::importAdvisorData(std::istream& input)
{
	slot_.clear();
	idea_token_.clear();
	ledger_.reset();
	available_.reset();
	allowed_.clear();
	visible_.reset();
	research_bonus_.reset();
	traits_.clear();
	cost_.reset();
	do_effect_.reset();
	ai_will_do_.reset();

	parseStream(input);

	return AdvisorData(slot_,
		 idea_token_,
		 ledger_,
		 available_,
		 allowed_,
		 visible_,
		 research_bonus_,
		 traits_,
		 cost_,
		 do_effect_,
		 ai_will_do_);
}