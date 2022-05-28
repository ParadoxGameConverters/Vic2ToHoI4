#ifndef RELATIONS_BUILDER_H
#define RELATIONS_BUILDER_H



#include "Relations.h"
#include <memory>



namespace Vic2
{

class Relations::Builder
{
  public:
	Builder() { relations = std::make_unique<Relations>(); }
	std::unique_ptr<Relations> build() { return std::move(relations); }

	Builder& setValue(int value)
	{
		relations->value = value;
		return *this;
	}

	Builder& setLevel(opinionLevel level)
	{
		relations->level = level;
		return *this;
	}

	Builder& setMilitaryAccess(bool militaryAccess)
	{
		relations->militaryAccess = militaryAccess;
		return *this;
	}

	Builder& setLastSentDiplomat(date lastSentDiplomat)
	{
		relations->lastSentDiplomat = lastSentDiplomat;
		return *this;
	}

	Builder& setLastWar(date lastWar)
	{
		relations->lastWar = lastWar;
		return *this;
	}

	Builder& setTruceUntil(date truceUntil)
	{
		relations->truceUntil = truceUntil;
		return *this;
	}

	Builder& setInfluenceValue(int influenceValue)
	{
		relations->influenceValue = influenceValue;
		return *this;
	}

  private:
	std::unique_ptr<Relations> relations;
};

} // namespace Vic2



#endif // RELATIONS_BUILDER_H