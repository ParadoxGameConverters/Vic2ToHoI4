#ifndef HOI4_DEFAULT_STATES_H
#define HOI4_DEFAULT_STATES_H


#include "external/common_items/ConvenientParser.h"
#include <set>
#include <string>



namespace HoI4
{

class DefaultState: commonItems::parser
{
  public:
	explicit DefaultState(std::istream& theStream);

	bool isImpassable() const { return impassable; }
	const std::string& getOwner() const { return ownerTag; }
	const std::set<int>& getProvinces() const { return provinces; }
	int getCivFactories() const { return civFactories; }
	int getMilFactories() const { return milFactories; }
	int getDockyards() const { return dockyards; }
	[[nodiscard]] const std::map<std::string, double>& GetResources() const { return resources_; }

  private:
	bool impassable = false;
	std::string ownerTag;
	std::set<int> provinces;
	int civFactories = 0;
	int milFactories = 0;
	int dockyards = 0;
	std::map<std::string, double> resources_;
};

} // namespace HoI4



#endif // HOI4_DEFAULT_STATES_H