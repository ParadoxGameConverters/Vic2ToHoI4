#ifndef SCORER_H
#define SCORER_H



#include <optional>
#include <string>



namespace HoI4
{

class Scorer
{
  public:
	class Factory;
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getTargets() const { return targets; }

	std::shared_ptr<Scorer> makeCustomizedCopy(const std::string& ideology) const;

	void setName(std::string _name) { name = std::move(_name); }
	void setTargets(std::string _targets) { targets = std::move(_targets); }

  private:
	std::string name;
	std::string targets;
};

} // namespace HoI4



#endif // SCORER_H