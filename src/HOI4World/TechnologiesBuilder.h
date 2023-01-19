#ifndef TECHNOLOGIES_BUILDER_H
#define TECHNOLOGIES_BUILDER_H



#include "src/HOI4World/Technologies.h"
#include <memory>



namespace HoI4
{

class technologies::Builder
{
  public:
	Builder() { theTechnologies = std::make_unique<technologies>(); }
	std::unique_ptr<technologies> Build() { return std::move(theTechnologies); }

	Builder& addTechnology(const std::string& technology)
	{
		auto [itr, inserted] = theTechnologies->technologiesByLimits.insert(std::make_pair("", std::set{technology}));
		if (!inserted)
		{
			itr->second.insert(technology);
		}
		return *this;
	}

  private:
	std::unique_ptr<technologies> theTechnologies;
};

} // namespace HoI4



#endif // TECHNOLOGIES_BUILDER_H