#ifndef HOI4_AGREEMENT_H_
#define HOI4_AGREEMENT_H_


#include "Date.h"
#include "../../V2World/Agreement.h"
#include <string>
using namespace std;



class HoI4Agreement
{
	public:
		HoI4Agreement(const string& _country1, const string& _country2, const Vic2::Agreement* oldAgreement);
		HoI4Agreement(const string& _country1, const string& _country2, const string& _type, int _relationshipValue, const date& _startDate);

		bool operator==(const HoI4Agreement &rhs) const
		{
			return ((type == rhs.type) && (country1 == rhs.country1) && (country2 == rhs.country2));
		}

		friend ofstream& operator << (ofstream& output, HoI4Agreement& instance);

		string getType() const { return type; }

	private:
		HoI4Agreement(const HoI4Agreement&) = delete;
		HoI4Agreement& operator=(const HoI4Agreement&) = delete;

		string type;
		string country1;
		string country2;
		int relationshipValue;
		date startDate;
};



#endif // HOI4_AGREEMENT_H_