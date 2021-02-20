#ifndef PARTY_MAPPER_H
#define PARTY_MAPPER_H




#include "PartyMapping.h"
#include <vector>
#include <set>
#include <string>



namespace Mappers
{

class PartyMapper
{
public:
	class Factory;

	std::string getSupportedIdeology(const std::string& rulingIdeology,
		 const std::string& Vic2Ideology,
		 const std::set<std::string>& majorIdeologies) const;

private:
	std::vector<PartyMapping> partyMap;
};
	
}


#endif // PARTY_MAPPER_H