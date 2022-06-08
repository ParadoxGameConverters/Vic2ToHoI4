#ifndef OPERATIVE_NAMES_H
#define OPERATIVE_NAMES_H



#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/OperativeNames/OperativeNamesSet.h"
#include <map>
#include <string>



namespace HoI4
{

class OperativeNames
{
  public:
	class Factory;
	[[nodiscard]] const auto& getOperativeNamesSets() const { return operativeNamesSets; }

	void addCountriesToNameSets(const std::map<std::string, std::shared_ptr<Country>>& countries);

  private:
	std::map<std::string, OperativeNamesSet> operativeNamesSets;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_H