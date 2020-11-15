#ifndef GOVERNMENT_MAPPER_BUILDER_H
#define GOVERNMENT_MAPPER_BUILDER_H



#include "GovernmentMapper.h"
#include <memory>



class governmentMapper::Builder
{
  public:
	Builder() { theGovernmentMapper = std::make_unique<governmentMapper>(); }
	std::unique_ptr<governmentMapper> Build() { return std::move(theGovernmentMapper); }

	Builder& addGovernmentMapping(const governmentMapping& theGovernmentMapping)
	{
		theGovernmentMapper->governmentMap.push_back(theGovernmentMapping);
		return *this;
	}

	Builder& addPartyMapping(const partyMapping& thePartyMapping)
	{
		theGovernmentMapper->partyMap.push_back(thePartyMapping);
		return *this;
	}

  private:
	std::unique_ptr<governmentMapper> theGovernmentMapper;
};



#endif // GOVERNMENT_MAPPER_BUILDER_H