#ifndef SCRIPTED_TRIGGER
#define SCRIPTED_TRIGGER



#include <ostream>
#include <string>



namespace HoI4
{

class ScriptedTrigger
{
  public:
	explicit ScriptedTrigger(std::string _name): name(std::move(_name)) {}

	void setBody(const std::string& newBody) { body = newBody; }

	[[nodiscard]] std::string_view getName() const { return name; }

	friend std::ostream& operator<<(std::ostream& output, const ScriptedTrigger& scriptedTrigger);

  private:
	std::string name;
	std::string body;
};

} // namespace HoI4



#endif // SCRIPTED_TRIGGER