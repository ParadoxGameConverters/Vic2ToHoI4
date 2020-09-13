#ifndef VIC2_RELATIONS_H_
#define VIC2_RELATIONS_H_



#include "Date.h"
#include "Parser.h"



namespace Vic2
{

class Relations: commonItems::parser
{
  public:
	explicit Relations(const std::string& theTag, std::istream& theStream);

	std::string getTag() const { return tag; }
	int getRelations() const { return value; }
	int getLevel() const { return level; }

	bool hasMilitaryAccess() const { return militaryAccess; }
	const date getDiplomatLastSent() const { return lastSentDiplomat; }
	const date getLastWar() const { return lastWar; }
	const date getTruceUntil() const { return truceUntil; }
	int getInfluenceValue() const { return influenceValue; }

  private:
	Relations(const Relations&) = delete;
	Relations& operator=(const Relations&) = delete;

	std::string tag = "";
	int value = 0;
	int level = 2;

	bool militaryAccess = false;
	date lastSentDiplomat;
	date lastWar;
	date truceUntil;
	int influenceValue = 0;
};

} // namespace Vic2



#endif // VIC2_RELATIONS_H_