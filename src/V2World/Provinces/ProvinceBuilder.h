#ifndef VIC2_PROVINCE_BUILDER
#define VIC2_PROVINCE_BUILDER



#include "Province.h"



namespace Vic2
{

class Province::Builder
{
  public:
	Builder()
	{
		numberSet = false;
		province = std::make_unique<Province>();
	}
	std::unique_ptr<Province> build()
	{
		if (!numberSet)
		{
			throw std::runtime_error("Province number not set in builder");
		}
		return std::move(province);
	}

	Builder& setNumber(const int number)
	{
		numberSet = true;
		province->number = number;
		return *this;
	}

	Builder& setIsLand()
	{
		province->landProvince_ = true;
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

	Builder& setNavalBaseLevel(const int navalBaseLevel)
	{
		province->navalBaseLevel = navalBaseLevel;
		return *this;
	}

	Builder& setRailLevel(const int railLevel)
	{
		province->railLevel = railLevel;
		return *this;
	}

  private:
	bool numberSet = false;
	std::unique_ptr<Province> province;
};

} // namespace Vic2



#endif // VIC2_PROVINCE_BUILDER