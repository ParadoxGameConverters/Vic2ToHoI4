#ifndef FACTION_TEMPLATES_H
#define FACTION_TEMPLATES_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/Factions/FactionTemplate.h"



namespace HoI4
{

class FactionTemplates: commonItems::parser
{
  public:
	FactionTemplates();
	FactionTemplates(std::istream& theStream);

	void updateFactionTemplates(const std::set<std::string>& majorIdeologies);

	void updateFactionTemplateDemocratic(const std::set<std::string>& majorIdeologies);
	void updateFactionTemplateFascism(const std::set<std::string>& majorIdeologies);
	void updateFactionTemplateRadical(const std::set<std::string>& majorIdeologies);
	void updateFactionTemplateAbsolutist(const std::set<std::string>& majorIdeologies);
	void updateFactionTemplateNeutrality(const std::set<std::string>& majorIdeologies);

	std::shared_ptr<HoI4::FactionTemplate> getTemplate(const std::string& templateId);

	[[nodiscard]] const auto& getImportedTemplates() const { return importedTemplates; }
	[[nodiscard]] const auto& getIdeologicalTemplates() const { return ideologicalTemplates; }

  private:
	std::map<std::string, std::vector<std::shared_ptr<FactionTemplate>>> importedTemplates;
	std::vector<FactionTemplate> ideologicalTemplates;
};


} // namespace HoI4



#endif // FACTION_TEMPLATES_H