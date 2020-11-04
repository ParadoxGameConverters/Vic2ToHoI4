#ifndef COUNTRY_LEADER_H
#define COUNTRY_LEADER_H


#include <string>



namespace HoI4
{

class CountryLeader
{
  public:
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getDescription() const { return description; }
	[[nodiscard]] const auto& getPortrait() const { return portrait; }
	[[nodiscard]] const auto& getIdeology() const { return ideology; }

	void setName(const std::string& name_) { name = name_; }
	void setDescription(const std::string& description_) { description = description_; }
	void setPortrait(const std::string& portrait_) { portrait = portrait_; }
	void setIdeology(const std::string& ideology_) { ideology = ideology_; }

  private:
	std::string name;
	std::string description;
	std::string portrait;
	std::string ideology;
};

} // namespace HoI4



#endif // COUNTRY_LEADER_H