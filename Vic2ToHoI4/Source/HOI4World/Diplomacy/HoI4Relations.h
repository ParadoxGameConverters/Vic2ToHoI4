#ifndef HoI4RELATIONS_H_
#define HoI4RELATIONS_H_



#include "Date.h"


namespace Vic2
{

class Relations;

}



class HoI4Relations
{
	public:
		explicit HoI4Relations(const std::string& newTag);
		HoI4Relations(const std::string& newTag, const Vic2::Relations* oldRelations);

		std::string	getTag()				const { return tag; };
		int		getRelations()		const { return value; };
		bool		getGuarantee()		const { return guarantee; };
		bool		getSphereLeader()		const { return sphereLeader; };
		date		getLastWar()		const { return lastWar; };
		date		getTruceUntil()	const { return truceUntil; };
		int			getInfluenceValue()		const { return influenceValue; };
		bool		atWar()				const { return lastWar > truceUntil; };

	private:

		std::string	tag;
		int		value;
		bool		militaryAccess;
		date		lastSendDiplomat;
		date		lastWar;
		date		truceUntil;
		int			influenceValue;
		bool		guarantee;
		bool		sphereLeader;
		double		spherelingAutonomy = 0.5;
};



#endif // HoI4RELATIONS_H_