#ifndef HOI4_COUNTRY_OUTPUTTER
#define HOI4_COUNTRY_OUTPUTTER



#include <ostream>
#include <set>
#include <vector>



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
void outputToUnitNamesFiles(const Country& theCountry);
void outputIdeaGraphics(
	std::ostream& ideasFile,
	graphicsMapper& graphics,
	const Country& theCountry
);
void outputCountry(
	const std::set<Advisor>& ideologicalMinisters,
	const std::vector<DivisionTemplateType>& divisionTemplates,
	namesMapper& theNames,
	graphicsMapper& theGraphics,
	const Country& theCountry
);

void reportIndustry(std::ostream& out, const Country& theCountry);

}



#endif // HOI4_COUNTRY_OUTPUTTER