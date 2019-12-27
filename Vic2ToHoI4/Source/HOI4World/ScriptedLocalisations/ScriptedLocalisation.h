#ifndef SCRIPTED_LOCALISATION_H
#define SCRIPTED_LOCALISATION_H



#include <string>
#include <vector>



namespace HoI4
{
	
class ScriptedLocalisation
{
	public:
		void setName(const std::string& _name) { name = _name; }
		void addText(const std::string& text) { texts.push_back(text); }

		std::string getName() const { return name; }
		std::vector<std::string> getTexts() const { return texts; }
	
	private:
		std::string name;
		std::vector<std::string> texts;
};

}



#endif // SCRIPTED_LOCALISATION_H