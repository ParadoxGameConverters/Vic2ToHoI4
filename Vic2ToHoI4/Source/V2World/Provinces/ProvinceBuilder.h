#ifndef VIC2_PROVINCE_BUILDER
#define VIC2_PROVINCE_BUILDER



#include "Province.h"



namespace Vic2
{

class Province::Builder
{
  public:
	Builder() { province = std::make_unique<Province>(); }
	std::unique_ptr<Province> build() { return std::move(province); }

	Builder& setNumber(int number)
	{
		province->number = number;
		return *this;
	}

	Builder& setOwner(std::string owner)
	{
		province->owner = std::move(owner);
		return *this;
	}

	Builder& setController(std::string controller)
	{
		province->controller = std::move(controller);
		return *this;
	}

	Builder& setCores(std::set<std::string> cores)
	{
		province->cores = std::move(cores);
		return *this;
	}

	Builder& setPops(std::vector<Pop> pops)
	{
		province->pops = std::move(pops);
		return *this;
	}

	Builder& setNavalBaseLevel(int navalBaseLevel)
	{
		province->navalBaseLevel = navalBaseLevel;
		return *this;
	}

	Builder& setRailLevel(int railLevel)
	{
		province->railLevel = railLevel;
		return *this;
	}

  private:
	std::unique_ptr<Province> province;
};
	
}




#endif // VIC2_PROVINCE_BUILDER