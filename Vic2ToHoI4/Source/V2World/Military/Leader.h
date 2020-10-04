#ifndef VIC2_LEADER_H_
#define VIC2_LEADER_H_



#include <string>



namespace Vic2
{

class Leader
{
  public:
	class Factory;

	std::string getName() const { return name; }
	std::string getType() const { return type; }
	double getPrestige() const { return prestige; }
	std::string getPersonality() const { return personality; }
	std::string getBackground() const { return background; }

  private:
	std::string name = "";
	std::string type = "";
	std::string personality = "";
	std::string background = "";
	double prestige = 0.0;
};

} // namespace Vic2



#endif // VIC2_LEADER_H_