#include "MergeRules.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



class MergeRule: commonItems::parser
{
  public:
	explicit MergeRule(std::istream& theStream);

	bool isEnabled() const { return enabled; }
	std::string getMaster() const { return master; }
	std::vector<std::string> getSlaves() const { return slaves; }

  private:
	bool enabled = false;
	std::string master = "";
	std::vector<std::string> slaves;
};


MergeRules::MergeRules() noexcept
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ruleName, std::istream& theStream) {
		MergeRule theRule(theStream);
		if (theRule.isEnabled())
		{
			rules.insert(make_pair(theRule.getMaster(), theRule.getSlaves()));
		}
	});

	parseFile("merge_nations.txt");
}


MergeRule::MergeRule(std::istream& theStream)
{
	registerKeyword("merge", [this](std::istream& theStream) {
		commonItems::singleString enabledString(theStream);
		enabled = (enabledString.getString() == "yes");
	});
	registerKeyword("master", [this](std::istream& theStream) {
		commonItems::singleString masterString(theStream);
		master = masterString.getString();
	});
	registerKeyword("slave", [this](std::istream& theStream) {
		commonItems::singleString slaveString(theStream);
		slaves.push_back(slaveString.getString());
	});

	parseStream(theStream);
}