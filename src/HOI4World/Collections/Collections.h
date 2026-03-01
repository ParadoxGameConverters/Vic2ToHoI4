#ifndef COLLECTIONS_H
#define COLLECTIONS_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/Collections/Collection.h"



namespace HoI4
{

class Collections: commonItems::parser
{
  public:
	Collections();
	Collections(std::istream& theStream);

	void updateCollections(const std::set<std::string>& majorIdeologies);

	void updateAntiIdeologyControlledStatesMyContinentCollection(const std::string& ideology,
		 Collection& collection,
		 const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getImportedCollections() const { return importedCollections; }
	[[nodiscard]] const auto& getIdeologicalCollections() const { return ideologicalCollections; }

  private:
	std::map<std::string, std::vector<Collection>> importedCollections;
	std::vector<Collection> ideologicalCollections;
};


} // namespace HoI4



#endif // COLLECTIONS_H