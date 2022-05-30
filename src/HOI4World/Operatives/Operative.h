#ifndef OPERATIVE_H
#define OPERATIVE_H



#include <string>



namespace HoI4
{

class Operative
{
  public:
	Operative(std::string name, std::string portrait, bool female, std::string nationality):
		 name_(std::move(name)), portrait_(std::move(portrait)), female_(female), nationality_(std::move(nationality))
	{
	}

	[[nodiscard]] const auto& getName() const { return name_; }
	[[nodiscard]] const auto& getPortrait() const { return portrait_; }
	[[nodiscard]] const auto& isFemale() const { return female_; }
	[[nodiscard]] const auto& getNationality() const { return nationality_; }

	friend std::ostream& operator<<(std::ostream& out, const Operative& operative);

  private:
	std::string name_;
	std::string portrait_;
	bool female_ = false;
	std::string nationality_;
};

} // namespace HoI4



#endif // OPERATIVE_H