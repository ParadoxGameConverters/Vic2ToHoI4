#ifndef HoI4RELATIONS_H_
#define HoI4RELATIONS_H_



#include "../../V2World/Relations.h"



namespace HoI4
{

class Relations
{
	public:
		explicit Relations(std::string newTag):
			tag(std::move(newTag)),
			value(0),
			guarantee(false),
			sphereLeader(false),
			influenceValue(0)
		{}

		Relations( std::string newTag, const Vic2::Relations& oldRelations):
			tag(std::move(newTag)),
			value(oldRelations.getRelations()),
			guarantee(oldRelations.getLevel() >= 4),
			sphereLeader(oldRelations.getLevel() >= 5),
			influenceValue(oldRelations.getInfluenceValue())
		{}

		[[nodiscard]] const auto& getTag() const { return tag; }
		[[nodiscard]] int getRelations() const { return value; }
		[[nodiscard]] bool getGuarantee() const { return guarantee; }
		[[nodiscard]] bool getSphereLeader() const { return sphereLeader; }
		[[nodiscard]] int getInfluenceValue() const { return influenceValue; }

	private:
		std::string	tag;
		int value;
		bool guarantee;
		bool sphereLeader;
		int influenceValue;
};

}



#endif // HoI4RELATIONS_H_