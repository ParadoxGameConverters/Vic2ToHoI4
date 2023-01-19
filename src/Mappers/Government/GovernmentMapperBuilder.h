#ifndef GOVERNMENT_MAPPER_BUILDER_H
#define GOVERNMENT_MAPPER_BUILDER_H



#include "src/Mappers/Government/GovernmentMapper.h"
#include <memory>



class Mappers::GovernmentMapper::Builder
{
  public:
	Builder() { governmentMapper = std::make_unique<GovernmentMapper>(); }
	std::unique_ptr<GovernmentMapper> Build() { return std::move(governmentMapper); }

	Builder& addGovernmentMapping(const GovernmentMapping& governmentMapping)
	{
		governmentMapper->governmentMap.push_back(governmentMapping);
		return *this;
	}

  private:
	std::unique_ptr<GovernmentMapper> governmentMapper;
};



#endif // GOVERNMENT_MAPPER_BUILDER_H