#ifndef OUT_HOI4_COUNTRY_H
#define OUT_HOI4_COUNTRY_H



#include "Configuration.h"
#include "HOI4World/HoI4Country.h"
#include "HOI4World/Leaders/Advisor.h"
#include "HOI4World/Military/DivisionTemplate.h"
#include "HOI4World/Names/Names.h"
#include "Mappers/GraphicsMapper.h"
#include <ostream>
#include <set>
#include <vector>



namespace HoI4
{

void outputToCommonCountriesFile(std::ostream& countriesFile, const Country& theCountry);
void outputColors(std::ostream& out, const Country& theCountry);
void outputToNamesFiles(std::ostream& namesFile, const Names& names, const Country& theCountry);
void outputToUnitNamesFiles(const Country& theCountry, const Configuration& theConfiguration);
void outputIdeaGraphics(std::ostream& ideasFile, const Country& theCountry);
void outputPortraits(std::ostream& portraitsFile, const Country& theCountry);
void outputCountry(const std::set<Advisor>& ideologicalMinisters,
	 const std::vector<DivisionTemplateType>& divisionTemplates,
	 const Country& theCountry,
	 const Configuration& theConfiguration);

void reportIndustry(std::ostream& out, const Country& theCountry);

} // namespace HoI4



#endif // OUT_HOI4_COUNTRY_H