#ifndef AGREEMENT_H
#define AGREEMENT_H



#include "Date.h"
#include "../../V2World/Agreement.h"



namespace HoI4
{

class Agreement
{
	public:
		Agreement(std::string _country1, std::string _country2, const Vic2::Agreement& oldAgreement):
			type(oldAgreement.getType()),
			country1(std::move(_country1)),
			country2(std::move(_country2)),
			relationshipValue(0),
			startDate(oldAgreement.getDate())
		{}

		Agreement(
			std::string _country1,
			std::string _country2,
			std::string _type,
			const int _relationshipValue,
			const date& _startDate
		):
			type(std::move(_type)),
			country1(std::move(_country1)),
			country2(std::move(_country2)),
			relationshipValue(_relationshipValue),
			startDate(_startDate)
		{}

		bool operator==(const Agreement& rhs) const = default;

		friend std::ostream& operator<<(std::ostream& output, const Agreement& agreement);

		[[nodiscard]] std::string getType() const { return type; }

	private:
		std::string type;
		std::string country1;
		std::string country2;
		int relationshipValue;
		date startDate;
};

}



#endif // AGREEMENT_H