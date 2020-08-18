#ifndef POP_BUILDER_H
#define POP_BUILDER_H



#include "Pop.h"
#include <memory>



namespace Vic2
{

class Pop::Builder
{
  public:
	Builder() { pop = std::make_unique<Pop>(); }
	std::unique_ptr<Pop> build() { return std::move(pop); }

	Builder& setType(std::string type)
	{
		pop->type = std::move(type);
		return *this;
	}

	Builder& setCulture(std::string culture)
	{
		pop->culture = std::move(culture);
		return *this;
	}

	Builder& setSize(int size)
	{
		pop->size = size;
		return *this;
	}

	Builder& setLiteracy(double literacy)
	{
		pop->literacy = literacy;
		return *this;
	}

	Builder& setMilitancy(double militancy)
	{
		pop->militancy = militancy;
		return *this;
	}

	Builder& setIssues(std::map<std::string, float> popIssues)
	{
		pop->popIssues = std::move(popIssues);
		return *this;
	}

  private:
	std::unique_ptr<Pop> pop;
};

} // namespace Vic2



#endif // POP_BUILDER_H