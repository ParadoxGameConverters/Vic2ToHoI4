#ifndef OUT_HOI4_COUNTRY_H
#define OUT_HOI4_COUNTRY_H



#include "src/Configuration.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/Military/DivisionTemplate.h"
#include "src/HOI4World/Names/Names.h"
#include <vector>



namespace HoI4
{

void outputToCommonCountriesFile(std::ostream& countriesFile, const Country& theCountry);
void outputColors(std::ostream& out, const Country& theCountry);
void outputToNamesFiles(std::ostream& namesFile, const Names& names, const Country& theCountry);
void outputToUnitNamesFiles(const Country& theCountry, const Configuration& theConfiguration);
void outputPortraits(std::ostream& portraitsFile, const Country& theCountry);
void outputCountry(const std::vector<DivisionTemplateType>& divisionTemplates,
	 const Country& theCountry,
	 const Configuration& theConfiguration);

void reportIndustry(std::ostream& out, const Country& theCountry);

} // namespace HoI4



#endif // OUT_HOI4_COUNTRY_H