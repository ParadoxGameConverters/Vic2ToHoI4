#ifndef OUT_HOI4_COUNTRY_H
#define OUT_HOI4_COUNTRY_H



#include <ostream>
#include <set>
#include <vector>



class Configuration;
class graphicsMapper;


namespace HoI4
{

class Advisor;
class Country;
class DivisionTemplateType;
class namesMapper;


void outputToCommonCountriesFile(std::ostream& countriesFile, const Country& theCountry);
void outputColors(std::ostream& out, const Country& theCountry);
void outputToNamesFiles(std::ostream& namesFile, const namesMapper& theNames, const Country& theCountry);
void outputToUnitNamesFiles(const Country& theCountry, const Configuration& theConfiguration);
void outputIdeaGraphics(std::ostream& ideasFile, const Country& theCountry);
void outputCountry(const std::set<Advisor>& ideologicalMinisters,
	 const std::vector<DivisionTemplateType>& divisionTemplates,
	 const Country& theCountry,
	 const Configuration& theConfiguration);

void reportIndustry(std::ostream& out, const Country& theCountry);

} // namespace HoI4



#endif // OUT_HOI4_COUNTRY_H