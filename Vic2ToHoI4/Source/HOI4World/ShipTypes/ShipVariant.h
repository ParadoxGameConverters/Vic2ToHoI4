#ifndef SHIP_VARIANT_H
#define SHIP_VARIANT_H



#include "newParser.h"
#include "ShipModules.h"
#include "../Technologies.h"
#include <memory>
#include <set>
#include <string>



namespace HoI4
{
	
class shipVariant: commonItems::parser
{
	public:
		explicit shipVariant(std::istream& theStream);

		shipVariant() = default;
		~shipVariant() = default;
		shipVariant(const shipVariant& source);
		shipVariant& operator=(const shipVariant&);
		shipVariant(shipVariant&&) = default;
		shipVariant& operator=(shipVariant&&) = default;

		void setOwningCountryTag(const std::string& tag);

		[[nodiscard]] bool isValidVariant(const technologies& ownedTechs) const;

		[[nodiscard]] std::string getName() const { return name; }

		friend std::ostream& operator << (std::ostream& output, shipVariant& theVariant);

	private:
		std::string name;
		std::string type;
		std::string owningCountryTag;
		std::string nameGroup;
		std::unique_ptr<shipModules> modules;
		bool obsolete = false;

		std::string ownerTag;

		std::set<std::string> requiredTechnologies;
		std::set<std::string> blockingTechnologies;
};

}



#endif // SHIP_VARIANT_H