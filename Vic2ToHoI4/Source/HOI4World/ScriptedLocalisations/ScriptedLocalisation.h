#ifndef SCRIPTED_LOCALISATION_H
#define SCRIPTED_LOCALISATION_H



#include <functional>
#include <string>
#include <vector>


namespace HoI4
{

class ScriptedLocalisation
{
  public:
	class Factory;
	void setName(const std::string& _name) { name = _name; }
	void addText(const std::string& text) { texts.push_back(text); }

	void filterTexts(std::function<bool(const std::string&)> removeCondition)
	{
		texts.erase(std::remove_if(texts.begin(), texts.end(), removeCondition), texts.end());
	}

	[[nodiscard]] std::string getName() const { return name; }
	[[nodiscard]] std::vector<std::string> getTexts() const { return texts; }

  private:
	std::string name;
	std::vector<std::string> texts;
};

} // namespace HoI4



#endif // SCRIPTED_LOCALISATION_H