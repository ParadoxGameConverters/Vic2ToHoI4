#ifndef SCRIPTED_TRIGGER
#define SCRIPTED_TRIGGER



#include <string>
#include <ostream>



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

}




#endif // SCRIPTED_TRIGGER